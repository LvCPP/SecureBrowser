#include"HttpResponse.h"
#include<cpprest\http_client.h>

using namespace web;
using namespace web::http;

namespace Http {

HttpResponse::HttpResponse()
{
	response_ = std::make_shared<web::http::http_response> (web::http::http_response());
}

HttpResponse::HttpResponse(const web::http::http_response& impl)
	: response_(std::make_shared<web::http::http_response>(web::http::http_response(impl)))
{
}

HttpResponse HttpResponse::FromHttpImpl(const web::http::http_response& impl)
{
	return HttpResponse(impl);
}

}