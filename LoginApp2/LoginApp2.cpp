#include "LoginApp2.h"

//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
//#include <iostream>
//#include <fstream>
//#include <string>

//#include "cpprest/containerstream.h"
//#include "cpprest/filestream.h"
//#include "cpprest/http_client.h"
//#include "cpprest/json.h"
//#include "cpprest/producerconsumerstream.h"
//
//#include <iostream>
//#include <sstream>
//
//using namespace ::pplx;
//using namespace utility;
//using namespace concurrency::streams;
//
//using namespace web;
//using namespace web::http;
//using namespace web::http::client;
//using namespace web::json;
//
//
//#include "HttpClient.h"
//
//using namespace BrowserHttp;
//
//
//using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
//using namespace web::http;                  // Common HTTP functionality
//using namespace web::http::client;          // HTTP client features
//using namespace concurrency::streams;       // Asynchronous streams


//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
//#include <cpprest/http_listener.h>              // HTTP server
//#include <cpprest/json.h>                       // JSON library
//#include <cpprest/uri.h>                        // URI library
//#include <cpprest/ws_client.h>                  // WebSocket client
//#include <cpprest/containerstream.h>            // Async streams backed by                    STL containers
//#include <cpprest/interopstream.h>              // Bridges for integrating  Async streams with STL and WinRT streams
//#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
//#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios
//using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
//using namespace web::http;                  // Common HTTP functionality
//using namespace web::http::client;          // HTTP client features
//using namespace concurrency::streams;       // Asynchronous streams
//using namespace web::http::experimental::listener;          // HTTP server
//using namespace web::experimental::web_sockets::client;     // WebSockets client
//using namespace web::json;                                  // JSON library
//
//using namespace pplx;
//using namespace web;
//
//#include "HttpClient.h"
//using namespace BrowserHttp;

using namespace Login;

LoginApp2::LoginApp2(QWidget *parent)
	: QWizard(parent)
{
	CreateWindow();
	CreateWizardButtonsLayout();
	SetPageSequence();
	
	//GetHttp();
}

LoginApp2::~LoginApp2()
{
}

void LoginApp2::CreateWindow()
{
	wnd_title = "SecureBrowser authentication process";
	setWindowTitle(wnd_title);

	wnd_width = 800;
	wnd_height = 600;
	setFixedSize(wnd_width, wnd_height);

	setWindowFlags(Qt::Window);
	setOptions(QWizard::NoCancelButtonOnLastPage);

	setWizardStyle(QWizard::ModernStyle);
	// this style can be changed:
	// 	QWizard::ClassicStyle, QWizard::ModernStyle, QWizard::MacStyle, QWizard::AeroStyle

}

void LoginApp2::CreateWizardButtonsLayout()
{
	layout << QWizard::Stretch << QWizard::NextButton << QWizard::CancelButton << QWizard::FinishButton;
	// this layout can be changed
	// All the QWizardButtons are: 
	// QWizard::BackButton, QWizard::NextButton, QWizard::CommitButton,
	// QWizard::FinishButton, QWizard::CancelButton, QWizard::HelpButton,
	// QWizard::CustomButton1, QWizard::CustomButton2, QWizard::CustomButton3
	
	setButtonLayout(layout);
}

void LoginApp2::SetPageSequence()
{
	if (FirstRun())
	{
		setPage(WELCOME_PAGE, new WelcomePage);
		setPage(LOGIN_PAGE, new LoginPage);
		setStartId(WELCOME_PAGE);
	}
	else
	{
		setPage(LOGIN_PAGE, new LoginPage);
		setStartId(LOGIN_PAGE);
	}
	
	MakePhotoPage* make_photo = new MakePhotoPage(this);
	QAbstractButton *nextButton = this->button(QWizard::NextButton);
	connect(nextButton, SIGNAL(clicked()), make_photo, SLOT(InitCamera()));
	setPage(MAKE_PHOTO_PAGE, make_photo);
	//setPage(MAKE_PHOTO_ID_PAGE, new MakePhotoIDPage);
	setPage(LAST_PAGE, new LastPage);
	
	SetFirstRunSetting();
	//RemoveFirstRunSetting(); // comments should be deleted if you want to show the welcome page
}

//void LoginApp2::GetHttp()
//{
//	//HttpClient client("https://www.google.com.ua");
//	//std::string path = "/q";
//	//HttpRequest my_request(HttpRequestMethod::Get, path);
//	////HttpResponse resp = Request(my_request);
//
//
//	//HttpResponse Get(const std::string& path);
//	//HttpResponse Post(const std::string& path, const std::vector<unsigned char>& data);
//
//	//auto fileStream = std::make_shared<ostream>();
//
//	//// Open stream to output file.
//	//pplx::task<void> requestTask = fstream::open_ostream(U("out.txt")).then([=](ostream outFile)
//	//{
//	//	*fileStream = outFile;
//
//	//	// Create http_client to send the request.
//	//	http_client client(U("http://www.bing.com/"));
//
//	//	// Build request URI and start the request.
//	//	uri_builder builder(U("/search"));
//	//	builder.append_query(U("q"), U("cats"));
//	//	return client.request(methods::GET, builder.to_string());
//	//})
//
//	//	// Handle response headers arriving.
//	//	.then([=](http_response response)
//	//{
//	//	printf("Received response status code:%u\n", response.status_code());
//
//	//	// Write response body into the file.
//	//	return response.body().read_to_end(fileStream->streambuf());
//	//})
//
//	//	// Close the file stream.
//	//	.then([=](size_t)
//	//{
//	//	return fileStream->close();
//	//});
//
//	//// Wait for all the outstanding I/O to complete and handle any exceptions
//	//try
//	//{
//	//	requestTask.wait();
//	//}
//	//catch (const std::exception &e)
//	//{
//	//	printf("Error exception:%s\n", e.what());
//	//}
//}
	
	
	/*HttpRequest(HttpRequestMethod::Get, "/search?q=cats");*/

	// Simple GET request
	/*http_response httpResponse = httpClient.request(methods::GET).get();
	if (httpResponse.status_code() == status_codes::OK)
	{
		wstring output = httpResponse.extract_utf16string().get();
		wcout << output << endl;
	}*/

	/*http_client client(U("http://en.cppreference.com/"));

	auto resp = client.request(U("GET")).get();

	QFile file("file.txt");
	QString str = "STATUS :" + resp.status_code();
	if (file.open(QIODevice::WriteOnly))
	{
		QTextStream stream(&file);
		stream << str;
		file.close();
	}*/
	
//void LoginApp2::SendHttpRequest()
//{
//		/*http_client client(U("http://en.cppreference.com/w/"));
//		auto resp = client.request(U("GET")).get();
//
//		cout  << U("STATUS : ") << resp.status_code() << endl;
//		qDebug << "content-type : " << resp.headers().content_type() << endl;
//		qDebug << resp.extract_string(true).get() << endl;*/
//
//		http_client client(L"http://en.cppreference.com");
//		http_request request(methods::GET);
//		client.request(request).then([](http_response response)
//		{
//			// Perform actions here to inspect the HTTP response...
//			if (response.status_code() == status_codes::OK)
//			{
//			}
//		});
	
	//qDebug << builder;

	//QFile file("file.txt");
	//QString str = "This is a test";
	//if (file.open(QIODevice::WriteOnly)) {
	//	QTextStream stream(&file);
	//	stream << str.toUpper(); // Запишет THIS IS A TEST
	//	file.close();
	//	if (stream.status() != QTextStream::Ok) {
	//		qDebug() << "Ошибка записи файла";
	//	}
	//}

	/*out << "This file is generated by Qt\n";

	http_response httpResponse = client.request(methods::GET).get();
	if (httpResponse.status_code() == status_codes::OK)
	{
		out << httpResponse.extract_utf16string().get() << "\n";
		
	}*/

	
	//auto fileStream = std::make_shared<ostream>();
	//pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
	//{
	//	*fileStream = outFile;

	//	// Create http_client to send the request.
	//	http_client client(U("http://www.bing.com/"));

	//	// Build request URI and start the request.
	//	uri_builder builder(U("/search"));
	//	builder.append_query(U("q"), U("Casablanca CodePlex"));
	//	return client.request(methods::GET, builder.to_string());
	//})


		// Open stream to output file.
		//pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
		//{
		//	*fileStream = outFile;

		//	// Create http_client to send the request.
		//	http_client client(U("http://www.bing.com/"));

		//	// Build request URI and start the request.
		//	uri_builder builder(U("/search"));
		//	builder.append_query(U("q"), U("Casablanca CodePlex"));
		//	return client.request(methods::GET, builder.to_string());
		//})

		//	// Handle response headers arriving.
		//	.then([=](http_response response)
		//{
		//	printf("Received response status code:%u\n", response.status_code());

		//	// Write response body into the file.
		//	return response.body().read_to_end(fileStream->streambuf());
		//})

		//	// Close the file stream.
		//	.then([=](size_t)
		//{
		//	return fileStream->close();
		//});

		//// Wait for all the outstanding I/O to complete and handle any exceptions
		//try
		//{
		//	requestTask.wait();
		//}
		//catch (const std::exception &e)
		//{
		//	printf("Error exception:%s\n", e.what());
		//}
	//file.close(); //  optional as QFile destructor already does it

void LoginApp2::SetFirstRunSetting()
{
	const QString reg_path = "HKEY_CURRENT_USER\\Software\\SoftServe\\SecureBrowser";
	QSettings setting(reg_path);

	setting.setDefaultFormat(QSettings::Registry64Format); 
	// Windows only:
	// Explicitly access the 64-bit system registry from a 32-bit application running on 64-bit Windows.
	// On 32-bit Windows or from a 64-bit application on 64-bit Windows, this works the same as
	// specifying NativeFormat. Was added in Qt 5.7.

	const QString reg_group_name = "Run";
	const QString reg_value_name = "FirstRun";
	setting.beginGroup(reg_group_name);
	bool first_run = false;
	setting.setValue(reg_value_name, first_run);
	setting.endGroup();
}

bool LoginApp2::FirstRun()
{
	const QString reg_path = "HKEY_CURRENT_USER\\Software\\SoftServe\\SecureBrowser";
	QSettings setting(reg_path);

	setting.setDefaultFormat(QSettings::Registry64Format);
	// Windows only:
	// Explicitly access the 64-bit system registry from a 32-bit application running on 64-bit Windows.
	// On 32-bit Windows or from a 64-bit application on 64-bit Windows, this works the same as
	// specifying NativeFormat. Was added in Qt 5.7.

	const QString reg_group_name = "Run";
	const QString reg_value_name = "FirstRun";
	setting.beginGroup(reg_group_name);
	QStringList keys = setting.childKeys();
	if (!keys.contains(reg_value_name, Qt::CaseInsensitive))
		return true;
	else
		return false;
	setting.endGroup();
}

void LoginApp2::RemoveFirstRunSetting()
{
	const QString reg_path = "HKEY_CURRENT_USER\\Software\\SoftServe\\SecureBrowser";
	QSettings setting(reg_path);

	setting.setDefaultFormat(QSettings::Registry64Format);
	// Windows only:
	// Explicitly access the 64-bit system registry from a 32-bit application running on 64-bit Windows.
	// On 32-bit Windows or from a 64-bit application on 64-bit Windows, this works the same as
	// specifying NativeFormat. Was added in Qt 5.7.

	const QString reg_group_name = "Run";
	const QString reg_value_name = "FirstRun";
	setting.beginGroup(reg_group_name);
	setting.remove(reg_value_name);
	setting.endGroup();
}

