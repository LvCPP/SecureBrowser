#include "HttpClient.h"
#include<cpprest\http_client.h>

using namespace web;
using namespace web::http;

namespace Http {

HttpClient::HttpClient(const std::string& host)
	: client_(new web::http::client::http_client(utility::conversions::to_string_t(host)))
{
}

HttpResponse HttpClient::Request(HttpRequest& request)
{
	auto task = client_->request(request.GetRequestImpl());
	auto status = task.wait();
	if (status != pplx::task_group_status::completed)
		throw 1;

	return HttpResponse::FromHttpImpl(task.get());
}

HttpResponse HttpClient::Get(const std::string& path)
{
	HttpRequest req(HttpRequestMethod::Get, path);
	return Request(req);
}

HttpResponse HttpClient::Post(const std::string& path, const std::vector<unsigned char>& data)
{
	HttpRequest req(HttpRequestMethod::Post, path);
	req.SetBody(data);
	return Request(req);
}

}
