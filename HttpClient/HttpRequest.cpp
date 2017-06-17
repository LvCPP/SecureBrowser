#include"HttpRequest.h"
#include<cpprest\http_client.h>

using namespace web::http;
using namespace utility::conversions;

using namespace BrowserHttp;

static const std::map<HttpRequestMethod, method> RequestToStringMap = {
	{ HttpRequestMethod::Get, methods::GET },
	{ HttpRequestMethod::Post, methods::POST }
};

HttpRequest::HttpRequest(HttpRequestMethod method, const std::string& path)
	: request_(std::make_shared<http_request>(http_request(RequestToStringMap.at(method))))
{
}

void HttpRequest::SetRequestUri(const std::string& uri)
{
	request_->set_request_uri(to_string_t(uri));
}

std::string HttpRequest::GetRequestUri() const
{
	return to_utf8string(request_->request_uri().to_string());
}

void HttpRequest::AddRequestHeader(const std::string& name, const std::string& value)
{
	request_->headers().add(to_string_t(name), to_string_t(value));
}

std::multimap<std::string, std::string> HttpRequest::GetHeaders() const
{
	std::multimap<std::string, std::string> request_headers;

	for (auto it = request_->headers().begin(); it != request_->headers().end(); ++it)
	{
		request_headers.emplace(to_utf8string(it->first), to_utf8string(it->second));
	}

	return request_headers;
}

void HttpRequest::SetBody(const std::vector<unsigned char>& body)
{
	request_->set_body(body);
}

void HttpRequest::SetBody(const std::string& body,const std::string& content_type)
{
	request_->set_body(body, content_type);
}

std::vector<unsigned char> HttpRequest::GetBody() const
{
	return request_->extract_vector().get();
}

std::string HttpRequest::GetStringBody() const
{
	return request_->extract_utf8string().get();
}
