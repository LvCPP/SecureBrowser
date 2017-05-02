#pragma once
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"HttpClientUtils.h"
#include<memory>

namespace web {
namespace http {
namespace client {
class http_client;
}
}
}

namespace Http {

class HttpClient
{
public:
	HTTPCLIENT_API HttpClient(const std::string& host = "https://www.google.com.ua");

	HTTPCLIENT_API HttpResponse Request(HttpRequest& request);
	HTTPCLIENT_API HttpResponse Get(const std::string& path);
	HTTPCLIENT_API HttpResponse Post(const std::string& path, const std::vector<unsigned char>& data);

private:
	std::shared_ptr<web::http::client::http_client> client_;
};

}

