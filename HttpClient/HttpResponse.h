#pragma once

#include <map>
#include<memory>
#include"HttpClientUtils.h"

namespace web {
namespace http {
class http_response;
}
}

namespace BrowserHttp {

class HttpResponse
{
public:
	HttpResponse();
	static HttpResponse FromHttpImpl(const web::http::http_response& impl);
	HTTPCLIENT_API std::multimap<std::string, std::string> GetHeaders();

private:
	std::shared_ptr<web::http::http_response> response_;
	HttpResponse(const web::http::http_response& impl);
};

}

