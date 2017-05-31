#pragma once

#include"HttpClientUtils.h"

#include<map>
#include<vector>
#include<memory>

namespace web {
namespace http {
class http_request;
}
}

namespace BrowserHttp
{

enum class HttpRequestMethod
{
	Get,
	Post
};

class HttpRequest
{
public:
	HTTPCLIENT_API HttpRequest(HttpRequestMethod method, const std::string& path = "/");

	HTTPCLIENT_API void AddRequestHeader(const std::string& name, const std::string& value);

	HTTPCLIENT_API void SetRequestUri(const std::string& uri);
	HTTPCLIENT_API void SetBody(const std::vector<unsigned char>& body);
	std::string GetRequestUri() const;
	std::map<std::string, std::string> GetHeaders();
	std::vector<unsigned char> GetBody() const;
	const web::http::http_request& GetRequestImpl() const { return *request_; }
	web::http::http_request& GetRequestImpl() { return *request_; }

private:
	std::shared_ptr<web::http::http_request> request_;
};

}


