#include"HttpResponse.h"
#include<cpprest\http_client.h>

using namespace web::http;
using namespace utility::conversions;

using namespace BrowserHttp;

HttpResponse::HttpResponse()
	:response_(std::make_shared<http_response>(http_response()))
{
}

HttpResponse::HttpResponse(const http_response& impl)
	: response_(std::make_shared<http_response>(http_response(impl)))
{
}

HttpResponse HttpResponse::FromHttpImpl(const http_response& impl)
{
	return HttpResponse(impl);
}

std::multimap<std::string, std::string> HttpResponse::GetHeaders()
{
	std::multimap<std::string, std::string> response_headers;

	for (auto it = response_->headers().begin(); it != response_->headers().end(); ++it)
	{
		response_headers.emplace(to_utf8string(it->first), to_utf8string(it->second));
	}

	return response_headers;
}