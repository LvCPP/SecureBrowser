#pragma once

#include<map>
#include<vector>
#include<memory>

namespace web {
	namespace http {
		class http_request;
	} 
}

namespace Http
{

enum class HttpRequestMethod
{
	Get,
	Post
};
class HttpRequest
{
public:
	HttpRequest(const HttpRequestMethod& method, const std::string& path = "/");
	void SetRequestUri(const std::string& uri);
	std::string GetRequestUri() const;
	void SetRequestHeader(const std::string& name, const std::string& value);
	std::map<std::string, std::string> GetHeaders();
	void SetBody(const std::vector<unsigned char>& body);
	std::vector<unsigned char> GetBody() const;
	const web::http::http_request& GetRequestImpl() const { return *request_; }
	web::http::http_request& GetRequestImpl() { return *request_; }

private:
	std::shared_ptr<web::http::http_request> request_;
};

}
