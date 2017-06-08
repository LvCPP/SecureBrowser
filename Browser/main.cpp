#include "browser.h"
#include <LoginDialog.h>
#include <Logger.h>
#include <KeyboardInspector.h>
#include <FakeWindowService.h>
#include <WindowsInspector.h>
#include <WebCameraCapture.h>
#include <WebCamController.h>
#include <PhotoMaker.h>
#include <FaceDetector.h>
#include <FaceCountObserver.h>
#include <FileSystemFrameSaver.h>

#include <QtWidgets/QApplication>

#include <windows.h>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iterator>

using namespace SecureBrowser;
using namespace BrowserLogger;
using namespace SBWindowsInspector;
using namespace CameraInspector;
using namespace SI;
using namespace SBKeyboardInspector;
using namespace Login;
using namespace Utils;

void ExitAlertDialog(LPCTSTR message);
void SetupKeyboardInspector(KeyboardInspector& ki);
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

	std::vector<std::string> input = Split(std::string(argv[1]), '$');
	if (input.at(0) != "sb://")
	{
		ExitAlertDialog(L"You can start Secure Browser only via invite link!");
		return -1;
	}

	An<WebCamController>()->RegisterForDeviceNotification();
	WaitTillAnyCameraConnected();

	std::string startup_path(argv[0]);
	std::size_t pos = startup_path.find("Startup.exe");
	std::string path = startup_path.substr(0, pos);

	An<Logger> logger;

	std::ofstream file(path + "log.txt", std::ios::out);
	logger->SetOutput(file);
	loginfo(*logger) << "Program initialized";
	
	QApplication a(argc, argv);

	LoginDialog app;
	
	loginfo(*logger) << "Start login";
	if (!app.exec())
	{
		logerror(*logger) << "User aborted logging in. Finish program.";
		Cleanup(file);
		return 0;
	}
	
	// Setting up inspectors
	KeyboardInspector ki;
	SetupKeyboardInspector(ki);
	ki.Start();
	
	WindowsInspector wi;
	wi.StartWindowsInspector();
	
	FakeWindowService fws;
	fws.Start();
	An<WebCameraCapture> cam_cap;

	const std::shared_ptr<FaceDetector> face_detector = std::make_shared<FaceDetector>();

	std::shared_ptr<IFrameSaver> shared_saver = std::make_shared<FileSystemFrameSaver>(FileSystemFrameSaver());
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetPathToSave("");

	std::shared_ptr<PhotoMaker> shared_maker = std::make_shared<PhotoMaker>(PhotoMaker());
	shared_maker->SetFrameSaver(shared_saver);

	const std::shared_ptr<FaceCountObserver> observer = std::make_shared<FaceCountObserver>(shared_maker);
	face_detector->Attach(observer);

	cam_cap->AddFrameHandler(shared_maker);
	cam_cap->AddFrameHandler(face_detector);

	face_detector->SetFrequency(std::chrono::seconds(1));

	cam_cap->Start();

	loginfo(*logger) << "Start Browser";
	Browser w;
	w.showMaximized();
	int result = a.exec();

	cam_cap->Stop();
	fws.Stop();
	wi.StopWindowsInspector();
	ki.Stop();

	loginfo(*logger) << "Program finished with code " << result;
	Cleanup(file);
	return result;
}

void ExitAlertDialog(LPCTSTR message)
{
	MessageBox(nullptr, message, L"Error", MB_ICONERROR);
}

void SetupKeyboardInspector(KeyboardInspector& ki)
{
	// TAB
	ki.IgnoreKeySequence(KEY_LALT + KEY_TAB);
	ki.IgnoreKeySequence(KEY_RALT + KEY_TAB);
	ki.IgnoreKeySequence(KEY_LALT + KEY_LSHIFT + KEY_TAB);
	ki.IgnoreKeySequence(KEY_LALT + KEY_RSHIFT + KEY_TAB);
	ki.IgnoreKeySequence(KEY_RALT + KEY_LSHIFT + KEY_TAB);
	ki.IgnoreKeySequence(KEY_RALT + KEY_RSHIFT + KEY_TAB);

	// WIN
	ki.IgnoreKeySequence(KEY_LWIN);
	ki.IgnoreKeySequence(KEY_RWIN);
	ki.IgnoreKeySequence(KEY_LWIN + KEY_R);
	ki.IgnoreKeySequence(KEY_RWIN + KEY_R);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_LWIN);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_RWIN);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_LWIN);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_RWIN);
	ki.IgnoreKeySequence(KEY_LSHIFT + KEY_LWIN);
	ki.IgnoreKeySequence(KEY_LSHIFT + KEY_RWIN);
	ki.IgnoreKeySequence(KEY_RSHIFT + KEY_LWIN);
	ki.IgnoreKeySequence(KEY_RSHIFT + KEY_RWIN);
	ki.IgnoreKeySequence(KEY_LALT + KEY_LWIN);
	ki.IgnoreKeySequence(KEY_LALT + KEY_RWIN);
	ki.IgnoreKeySequence(KEY_RALT + KEY_LWIN);
	ki.IgnoreKeySequence(KEY_RALT + KEY_RWIN);

	// APPS
	ki.IgnoreKeySequence(KEY_APPS);

	// PRINTSCREEN
	ki.IgnoreKeySequence(KEY_PRINT);
	ki.IgnoreKeySequence(KEY_PRNT_SCR);
	ki.IgnoreKeySequence(KEY_LALT + KEY_PRINT);
	ki.IgnoreKeySequence(KEY_RALT + KEY_PRINT);
	ki.IgnoreKeySequence(KEY_LALT + KEY_PRNT_SCR);
	ki.IgnoreKeySequence(KEY_RALT + KEY_PRNT_SCR);

	// COPY PASTE
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_C);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_C);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_V);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_V);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_X);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_X);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_INS);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_INS);
	ki.IgnoreKeySequence(KEY_LSHIFT + KEY_INS);
	ki.IgnoreKeySequence(KEY_RSHIFT + KEY_INS);
	ki.IgnoreKeySequence(KEY_LSHIFT + KEY_DEL);
	ki.IgnoreKeySequence(KEY_RSHIFT + KEY_DEL);

	// ESC
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_LSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_RSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_RSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_LSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LALT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RALT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LALT + KEY_LSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LALT + KEY_RSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RALT + KEY_LSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RALT + KEY_RSHIFT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_LALT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_RALT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_LALT + KEY_ESC);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_RALT + KEY_ESC);

	// F1 - F12
	ki.IgnoreKeySequence(KEY_F1);
	ki.IgnoreKeySequence(KEY_F2);
	ki.IgnoreKeySequence(KEY_F3);
	ki.IgnoreKeySequence(KEY_F4);
	ki.IgnoreKeySequence(KEY_F5);
	ki.IgnoreKeySequence(KEY_F6);
	ki.IgnoreKeySequence(KEY_F7);
	ki.IgnoreKeySequence(KEY_F8);
	ki.IgnoreKeySequence(KEY_F9);
	ki.IgnoreKeySequence(KEY_F10);
	ki.IgnoreKeySequence(KEY_F11);
	ki.IgnoreKeySequence(KEY_F12);
	ki.IgnoreKeySequence(KEY_F13);
	ki.IgnoreKeySequence(KEY_F14);
	ki.IgnoreKeySequence(KEY_F15);
	ki.IgnoreKeySequence(KEY_F16);
	ki.IgnoreKeySequence(KEY_F17);
	ki.IgnoreKeySequence(KEY_F18);
	ki.IgnoreKeySequence(KEY_F19);
	ki.IgnoreKeySequence(KEY_F20);
	ki.IgnoreKeySequence(KEY_F21);
	ki.IgnoreKeySequence(KEY_F22);
	ki.IgnoreKeySequence(KEY_F23);
	ki.IgnoreKeySequence(KEY_F24);
	ki.IgnoreKeySequence(KEY_LSHIFT + KEY_F10);
	ki.IgnoreKeySequence(KEY_RSHIFT + KEY_F10);
	ki.IgnoreKeySequence(KEY_LALT + KEY_F6);
	ki.IgnoreKeySequence(KEY_RALT + KEY_F6);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_F12);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_F12);

	//OTHERS
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_F);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_F);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_G);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_G);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_I);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_I);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_N);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_N);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_O);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_O);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_P);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_P);
	ki.IgnoreKeySequence(KEY_LCONTROL + KEY_S);
	ki.IgnoreKeySequence(KEY_RCONTROL + KEY_S);
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
