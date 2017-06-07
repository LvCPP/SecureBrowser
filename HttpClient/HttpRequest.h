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
	HTTPCLIENT_API void SetBody(const std::string& body, const std::string& content_type);
	HTTPCLIENT_API std::string GetRequestUri() const;
	HTTPCLIENT_API std::multimap<std::string, std::string> GetHeaders();
	HTTPCLIENT_API std::vector<unsigned char> GetBody() const;
	HTTPCLIENT_API std::string GetStringBody() const;
	HTTPCLIENT_API const web::http::http_request& GetRequestImpl() const { return *request_; }
	web::http::http_request& GetRequestImpl() { return *request_; }

private:
	std::shared_ptr<web::http::http_request> request_;
};

}


