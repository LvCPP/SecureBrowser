#include "LoginPage.h"
#include "LoginApp2.h"
#include "windows.h"

//#include "HttpClient.h"
//#include "HttpClientUtils.h"
//#include "HttpRequest.h"
//#include "HttpResponse.h"

//#include <memory>
//#include <QDebug>
//#include <string>
//
//#include <iostream>
//#include <sstream>


//using namespace BrowserHttp;

//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
//
//
//using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
//using namespace web::http;                  // Common HTTP functionality
//using namespace web::http::client;          // HTTP client features
//using namespace concurrency::streams;       // Asynchronous streams
//using namespace utility::conversions;

//#include "cpprest/containerstream.h"
//#include "cpprest/filestream.h"
//#include "cpprest/http_client.h"
//#include "cpprest/json.h"
//#include "cpprest/producerconsumerstream.h"
//#include <iostream>
//#include <sstream>

//using namespace ::pplx;
//using namespace utility;
//using namespace concurrency::streams;
//
//using namespace web;
//using namespace web::http;
//using namespace web::http::client;
//using namespace web::json;

using namespace Login;

LoginPage::LoginPage(QWidget *parent)
	: QWizardPage(parent)
{
	CreateLoginPageBackground();
	CreateTopLabel();
	CreateUsernameLabel();
	CreateUsernameLineedit();
	CreatePasswordLabel();
	CreatePasswordLineEdit();
	CreateAgreeCheckBox();
	CreateAgreeLabel();

	CreateLoginButton();

	connect(agree_checkbox, SIGNAL(toggled(bool)), login_button, SLOT(setEnabled(bool)));

	login_checked = false;
	connect(login_button, SIGNAL(clicked()), this, SLOT(CheckLogin()));

	/*OutputDebugStringA(MoodleAuthenticated().c_str());*/

	/*if (MoodleAuthenticated())
	{
		qDebug << "Yes";
	}
	else
	{
		qDebug << "No";
	}*/

}

LoginPage::~LoginPage()
{
}

void LoginPage::CreateLoginPageBackground()
{
	white_color = "background-color: rgb(255, 255, 255);";
	setStyleSheet(white_color);

}

void LoginPage::CreateTopLabel()
{
	top_label = new QLabel(this);
	top_label->setText("You are invited to take the test as one of the stages\n to be "
		"enrolled in SoftServe IT Academy.\n\n"
		"Please input your credentials:");
	x = 50;
	y = 50;
	width = 700;
	height = 100;
	top_label->setGeometry(QRect(x, y, width, height));
	top_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	QFont arial_14("Arial", 14);
	top_label->setFont(arial_14);
	top_label->setWordWrap(true);
}

void LoginPage::CreateUsernameLabel()
{
	username_label = new QLabel(this);
	x = 250;
	y = 180;
	width = 100;
	height = 25;
	username_label->setGeometry(QRect(x, y, width, height));
	username_label->setAlignment(Qt::AlignRight);
	QFont arial_12("Arial", 12);
	username_label->setFont(arial_12);
	username_label->setText("Username*");
}

void LoginPage::CreateUsernameLineedit()
{
	username_lineedit = new QLineEdit(this);
	x = 360;
	y = 180;
	width = 150;
	height = 25;
	username_lineedit->setGeometry(QRect(x, y, width, height));
	QFont arial_14("Arial", 14);
	username_lineedit->setFont(arial_14);
	registerField("Username*", username_lineedit);
}

void LoginPage::CreatePasswordLabel()
{
	password_label = new QLabel(this);
	x = 250;
	y = 225;
	width = 100;
	height = 25;
	password_label->setGeometry(QRect(x, y, width, height));
	password_label->setAlignment(Qt::AlignRight);
	QFont arial_12("Arial", 12);
	password_label->setFont(arial_12);
	password_label->setText("Password*");
}

void LoginPage::CreatePasswordLineEdit()
{
	password_lineedit = new QLineEdit(this);
	x = 360;
	y = 225;
	width = 150;
	height = 25;
	password_lineedit->setGeometry(QRect(x, y, width, height));
	QFont arial_14("Arial", 14);
	password_lineedit->setFont(arial_14);
	password_lineedit->setEchoMode(QLineEdit::Password);
	registerField("Password*", password_lineedit);
}

void LoginPage::CreateAgreeCheckBox()
{
	agree_checkbox = new QCheckBox(this);
	x = 275;
	y = 275;
	width = 30;
	height = 25;
	agree_checkbox->setGeometry(x, y, width, height);
	registerField("agree_checkbox*", agree_checkbox);
}

void LoginPage::CreateAgreeLabel()
{
	agree_label = new QLabel(this);
	x = 295;
	y = 280;
	width = 250;
	height = 25;
	agree_label->setGeometry(QRect(x, y, width, height));
	agree_label->setAlignment(Qt::AlignLeft);
	QFont arial_12("Arial", 12);
	agree_label->setFont(arial_12);
	agree_label->setText("<html><head / ><body><p><span style = \" font-size:10pt;\">I agree with "
		"</span><a href=\"https://drive.google.com/open?id=0B9Xa2M9s3StoOFNXYXQ2QWZPZ28\"><span style=\" font-size:12pt;"
		"text-decoration: underline; color:#0000ff;\">Rules and Agreements</span></a></p></body></html>");
	agree_label->setOpenExternalLinks(true);
}

void LoginPage::CreateLoginButton()
{
	login_button = new QPushButton(this);
	x = 310;
	y = 325;
	width = 130;
	height = 60;
	login_button->setGeometry(QRect(x, y, width, height));
	login_button->setText("Login");
	QFont button_font;
	button_font.setFamily(QStringLiteral("Arial"));
	button_font.setPointSize(14);
	login_button->setDisabled(true);
	login_button->setFont(button_font);
	QString gray_color = "background-color: rgb(225, 225, 225);";
	login_button->setStyleSheet(gray_color);
}

bool LoginPage::CheckLogin()
{
	QString  username = username_lineedit->text();
	QString password = password_lineedit->text();

	if (username == "12345" && password == "12345")
	{
		login_checked = true;
		QMessageBox::information(this, "Login", "User found");
		return true;
	}
	else
	{
		QMessageBox::warning(this, "Login", "Not correct. "
			"Please provide correct username and password");
		return false;
	}
}

int LoginPage::nextId() const
{
	bool login_button_enabled = login_button->isEnabled();
	if (login_checked && login_button_enabled)
		return LoginApp2::MAKE_PHOTO_PAGE;
	else
		return LoginApp2::LOGIN_PAGE;
}


void LoginPage::MoodleAuthenticated()
{
	/*concurrency::streams::basic_istream<unsigned char> fileStream
		= file_stream<unsigned char>::open_istream("C:\Desktop\Sample.txt").get();
	concurrency::streams::stringstreambuf streamBuffer;
	fileStream.read_to_end(streamBuffer).get();
	std::string textFile = move(streamBuffer.collection());
	fileStream.close();
	streamBuffer.close();

	web::uri_builder builder(U("http://virt.lac.lviv.ua/"));
	builder.append_path(U("login/index.php"));

	builder.append_query(U("username"), U("z1"));
	builder.append_query(U("passsord"), U("111"));

	http_client client(builder.to_string());

	http_request req;
	req.set_method(methods::GET);

	http_response response = client.request(req).get();


	std::cout << response.status_code();*/




	//http_client_config config;
	//credentials creds(U("z1"), U("111"));
	//config.set_credentials(creds);
	//http_client session(U("http://virt.lac.lviv.ua"), config);

	//session
	//	// send the HTTP GET request asynchronous
	//	.request(methods::GET)
	//	// continue when the response is available
	//	.then([](http_response response) -> pplx::task<json::value>
	//{
	//	// if the status is OK extract the body of the response into a JSON value
	//	// works only when the content type is application\json
	//	if (response.status_code() == status_codes::OK)
	//	{
	//		return response.extract_json();
	//	}

	//	// return an empty JSON value
	//	return pplx::task_from_result(json::value());
	//})
	//	// continue when the JSON value is available
	//	.then([](pplx::task<json::value> previousTask)
	//{
	//	// get the JSON value from the task and display content from it
	//	try
	//	{
	//		json::value const & value = previousTask.get();
	//		if (!value.is_null())
	//		{
	//			qDebug() << "JSON is null";
	//		}
	//	}
	//	catch (http_exception const & e)
	//	{
	//		wcout << e.what() << endl;
	//	}
	//})
	//	.wait();
}

	/*auto XYZtaW46Wr6yZW0xMAXY = base64("username:password");

	

	http_request request;
	request.set_method(methods::GET);
	req.headers().add(U("Authorization", L"Basic XYZtaW46Wr6yZW0xMAXY"));
	req.set_request_uri(U("/login/index.php?username=z1&password=111"));

	pplx::task<http_response> responses = client.request(req);
	pplx::task<web::json::value> jvalue = responses.get().extract_json();
	wcout << jvalue.get().to_string();

	uri_builder builder(U("/login/"));


	request.set_request_uri(uri(U("/login/index.php?username=z1&password=111")));

	std::string requestBody = "username=z1&password=111";*/
	
	
	
	/*request.set_body(requestBody, L"application/json");
	request.headers().add(header_names::accept, U("application/json"));*/
	//return session.request(request).then
	//(
	//	[](http_response response)
	//	{
	//		status_code responseStatus = response.status_code();
	//		std::wstring responseBodyU = response.extract_string().get();
	//		string responseBody = utility::conversions::to_utf8string(responseBodyU);
	//		if (responseStatus == status_codes::OK)
	//			qDebug() << "OK";
	//		else if (responseStatus == status_codes::Unauthorized)
	//			qDebug() << "Bad password";
	//		else
	//		{
	//			qDebug() << "Unexpected result:";
	//			/*std::wout << responseStatus;
	//			std::wout << response.reason_phrase();
	//			std::wout << responseBody;*/
	//		}
	//	}
	//);

	



	
	
	//// Please check how to convert into base64
	//QTextStream  out(stdout);
	//#define XYZtaW46Wr6yZW0xMAXY = base64("z1:111");

	//// Creating http_client
	//http_client_config config;
	//credentials cred(L"z1", L"111");
	//config.set_credentials(cred);
	//http_client client(L"http://virt.lac.lviv.ua", config);
	//// create header
	//http_request req(methods::GET);
	//// Add base64 result to header
	//req.headers().add(L"Authorization", L"Basic XYZtaW46Wr6yZW0xMAXY");
	//req.set_request_uri(L"/login/index.php");
	//pplx::task<http_response> responses = client.request(req);
	//pplx::task<web::json::value> jvalue = responses.get().extract_json();
	//utility::string_t str = jvalue.get().to_string();

	/*std::vector<unsigned char> vect = from_base64(str);
	std::wstring widestring(vect.begin(), vect.end());
	std::string s(widestring.begin(), widestring.end());


	std::cout << s;*/

	
	
	//auto fileStream = std::make_shared<ostream>();

	//// Open stream to output file.
	//auto requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
	//{
	//	*fileStream = outFile;

	//	// Create http_client to send the request.
	//	http_client_config config;
	//	credentials creds((utility::string_t)"z1", (utility::string_t)"111");
	//	config.set_credentials(creds);
	//	http_client client(U("http://virt.lac.lviv.ua"), config);

	//	// Build request URI and start the request.
	//	uri_builder builder(U("/login/index.php"));

	//	return client.request(methods::GET, builder.to_string());
	//})

	/*HttpClient client("http://virt.lac.lviv.ua");
	HttpRequest req(HttpRequestMethod::Post, "/login/index.php");
	PByteArray 
	req.SetBody("username=z1&password=111");
	HttpResponse resp = client.Request(req);*/

	
	/*
	QString  username = username_lineedit->text();
	QString password = password_lineedit->text();
	QString my_body = "username=" + username + "&" + "password=" + password;
	//std::wstring new_body = U(my_body);
	http_client client(U("http://virt.lac.lviv.ua"));
	http_request req(methods::POST);
	req.set_request_uri(U("/login/index.php"));
	//req.headers().add(header_names::user_agent, U("myclient"));

	//req.set_body(new_body);
	req.set_body(U("username=12345&password=12345"));
	http_response response = client.request(req).get();

	if (response.status_code() == status_codes::OK)
	{
		const utility::string_t body = response.extract_string().get();
		return false;
	}
	else
		return true;
		*/

	

	





