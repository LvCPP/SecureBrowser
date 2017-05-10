#include"HttpResponse.h"
#include<cpprest\http_client.h>

using namespace web::http;

using namespace BrowserHttp;

/*HttpResponse::HttpResponse()
:response_(std::make_shared<http_response>(http_response()))
{
}*/

HttpResponse::HttpResponse(const http_response& impl)
	: response_(std::make_shared<http_response>(http_response(impl)))
{
}

HttpResponse HttpResponse::FromHttpImpl(const http_response& impl)
{
	return HttpResponse(impl);
}