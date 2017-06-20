#include "browser.h"
#include <LoginDialog.h>
#include <Logger.h>
#include <FakeWindowService.h>
#include <WebCameraCapture.h>
#include <WebCamController.h>
#include <PhotoMaker.h>
#include <FaceDetector.h>
#include <FaceCountObserver.h>
#include <FileSystemFrameSaver.h>
#include <SessionInspector.h>
#include <Base64Decryptor.h>

#include <QtWidgets/QApplication>
#include <QSplashScreen>

#include <windows.h>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iterator>

// for checking Internet connection
#include <wininet.h>
#pragma comment(lib,"wininet.lib")

using namespace SecureBrowser;
using namespace BrowserLogger;
using namespace CameraInspector;
using namespace SI;
using namespace Login;
using namespace Utils;

void ExitAlertDialog(LPCTSTR message);
bool IsAlreadyRunning();
void WaitTillAnyCameraConnected();
std::vector<std::string> Split(const std::string& string, char delim);
void Cleanup(std::ofstream& file_to_close);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		ExitAlertDialog(L"You can start Secure Browser only via invite link!");
		return -1;
	}

	if (IsAlreadyRunning())
	{
		ExitAlertDialog(L"Program is already running!");
		return -1;
	}

	if(SessionInspector::IsInsideVBox() || SessionInspector::IsCurrentSessionRemoteable())
	{
		ExitAlertDialog(L"You can't start Secure Browser from remote session or virtual box!");
		return -1;
	}

	bool bConnect = InternetCheckConnection(L"https://softserve.academy/", FLAG_ICC_FORCE_CONNECTION, 0);
	if (!bConnect)
	{
		ExitAlertDialog(L"Internet connection doesn't exist."
			"Please check your Internet connection!");
		return -1;
	}
	
	std::vector<std::string> input = Split(std::string(argv[1]), '$');
	if (input.at(0) != "sb://")
	{
		ExitAlertDialog(L"You can start Secure Browser only via invite link!");
		return -1;
	}

	An<WebCamController>()->RegisterForDeviceNotification();
	WaitTillAnyCameraConnected();

	std::string startup_path(argv[0]);
	size_t pos = startup_path.find("Startup.exe");
	std::string path = startup_path.substr(0, pos);

	std::string login = input.at(1);
	std::string password = input.at(2);
	std::string quiz_id = input.at(3);
	std::string password_to_quiz = Base64Decryptor::Decode(input.at(4));

	QApplication app(argc, argv);
	QSplashScreen splash_screen(QPixmap(QString::fromStdString(path + "Resources\\splash.png")));
	splash_screen.setEnabled(false); // Prevent user from closing the splash
	splash_screen.show();
	app.processEvents(); // Make sure splash screen gets drawn ASAP

	An<Logger> logger;

	std::ofstream file(path + "Logs\\" + "log.txt", std::ios::out);
	logger->SetOutput(file);
	loginfo(*logger) << "Program initialized";
	
	LoginDialog login_app(login, password, quiz_id, password_to_quiz, path);
	loginfo(*logger) << "Start login";
	
	splash_screen.hide();
	if (!login_app.exec())
	{
		logerror(*logger) << "Login dialog failed. Program finished.";
		Cleanup(file);
		return 0;
	}

	splash_screen.show();

	// For sending cookies to the browser's constructor
	std::string moodle_cookies;
	login_app.GetMoodleSession(moodle_cookies);

	// For sending sesskey to the browser's constructor
	QString body;
	login_app.GetRespBody(body);

	An<WebCameraCapture> cam_cap;

	const std::shared_ptr<FaceDetector> face_detector = std::make_shared<FaceDetector>(path + "Resources\\");

	std::shared_ptr<IFrameSaver> shared_saver = std::make_shared<FileSystemFrameSaver>(FileSystemFrameSaver());
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetPathToSave(path + "Photos\\");

	std::shared_ptr<PhotoMaker> shared_maker = std::make_shared<PhotoMaker>(PhotoMaker());
	shared_maker->SetFrameSaver(shared_saver);

	const std::shared_ptr<FaceCountObserver> observer = std::make_shared<FaceCountObserver>(shared_maker);
	face_detector->Attach(observer);

	cam_cap->AddFrameHandler(shared_maker);
	cam_cap->AddFrameHandler(face_detector);

	face_detector->SetFrequency(std::chrono::seconds(1));

	cam_cap->Start();

	loginfo(*logger) << "Start Browser";

	Browser browser_app(quiz_id, password_to_quiz, moodle_cookies, body);
	browser_app.showMaximized();

	splash_screen.finish(&browser_app);
	int result = app.exec();

	cam_cap->Stop();

	logerror(*logger) << "Program finished with code " << result;
	Cleanup(file);
	return result;
}

void ExitAlertDialog(LPCTSTR message)
{
	MessageBox(nullptr, message, L"Error", MB_ICONERROR);
}

bool IsAlreadyRunning()
{
	CreateMutexA(nullptr, FALSE, "Local\\SecureBrowser");

	switch (GetLastError())
	{
	case ERROR_ALREADY_EXISTS:
		return true;	// Quit. Mutex is released automatically;
	default:			// Mutex successfully created
		return false;
	}
}

void WaitTillAnyCameraConnected()
{
	while (An<WebCamController>()->GetCamerasCount() == 0)
	{
		int choose = MessageBox(
			nullptr,
			L"The program requires a webcam. Connect to continue",
			L"Error",
			MB_ICONSTOP | MB_RETRYCANCEL | MB_DEFBUTTON4
		);

		switch (choose)
		{
		case IDCANCEL:
			An<WebCamController>()->UnregisterForDeviceNotification();
			exit(-1);
		default:
			// Retry pressed
			break;
		}
	}
}

std::vector<std::string> Split(const std::string& string, char delim)
{
	std::vector<std::string> elems;
	std::back_insert_iterator<std::vector<std::string>> inserter = std::back_inserter(elems);
	std::stringstream ss(string);
	std::string item;

	while (std::getline(ss, item, delim))
	{
		*(inserter++) = item;
	}

	return elems;
}

void Cleanup(std::ofstream& file_to_close)
{
	An<Logger>()->Flush();
	An<WebCamController>()->UnregisterForDeviceNotification();

	file_to_close.close();
}
