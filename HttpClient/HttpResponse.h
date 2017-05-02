#pragma once

#include<memory>

namespace web {
namespace http {
class http_response;
}
}

namespace Http {

class HttpResponse
{
public:
	HttpResponse();
	static HttpResponse FromHttpImpl(const web::http::http_response& impl);

private:
	HttpResponse(const web::http::http_response& impl);
	std::shared_ptr<web::http::http_response> response_;
};

}

