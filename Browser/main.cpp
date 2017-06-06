#include "browser.h"
#include <Logger.h>
#include <KeyboardInspector.h>
#include "FakeWindowService.h"
#include "SessionInspector.h"
#include "WebCameraCapture.h"
#include "WindowsInspector.h"
#include "PhotoMaker.h"
#include "FileSystemFrameSaver.h"
#include "FrameStorer.h"
#include "FaceDetector.h"
#include "CameraException.h"
#include "FaceCountObserver.h"
#include <LoginApp2.h>
#include <WebCamController.h>
#include <QtWidgets/QApplication>
#include <windows.h>
#include <fstream>
#include <chrono>

using namespace SecureBrowser;
using namespace BrowserLogger;
using namespace SBWindowsInspector;
using namespace CameraInspector;
using namespace SI;
using namespace SBKeyboardInspector;
using namespace Login;
using namespace Utils;

void SetupKeyboardInspector(KeyboardInspector& ki);
bool IsAlreadyRunning();
void WaitTillAnyCameraConnected();
void Cleanup(std::ofstream& file_to_close);

int main(int argc, char* argv[])
{
	WaitTillAnyCameraConnected();

	if (IsAlreadyRunning())
	{
		MessageBox(
			NULL,

			L"Program is already running!",
			L"Error",
			MB_ICONERROR
		);
		return -1;
	}

	An<Logger> logger;

	std::ofstream file("log.txt", std::ios::out);
	logger->SetOutput(file);
	loginfo(*logger) << "Program initialized";
	QApplication a(argc, argv);

	An<WebCamController>()->RegisterForDeviceNotification();
	LoginApp2 app;
	
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
	CreateMutexA(0, FALSE, "Local\\SecureBrowser");

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
			NULL,
			L"The program requires a webcam. Connect to continue",
			L"Error",
			MB_ICONSTOP | MB_RETRYCANCEL | MB_DEFBUTTON4
		);

		switch (choose)
		{
		case IDCANCEL:
			exit(-1);
		default:
			// Retry pressed
			break;
		}
	}
}

void Cleanup(std::ofstream& file_to_close)
{
	An<Logger>()->Flush();
	An<WebCamController>()->UnregisterForDeviceNotification();

	file_to_close.close();
}
