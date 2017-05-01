#pragma once
#include"HttpRequest.h"
#include"HttpResponse.h"
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
	HttpClient(const std::string& host = "https://www.google.com.ua");

	HttpResponse Request(HttpRequest& request);
	HttpResponse Get(const std::string& path);
	HttpResponse Post(const std::string& path, const std::vector<unsigned char>& data);

private:
	std::shared_ptr<web::http::client::http_client> client_;
};

}

