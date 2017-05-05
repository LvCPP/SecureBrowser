#include "HttpClient.h"
#include<cpprest\http_client.h>

using namespace web;
using namespace web::http::client;
using namespace utility::conversions;

using namespace BrowserHttp;

class HttpClientImpl
{
public:
	HttpClientImpl(const std::string& host)
		: client(to_string_t(host))
	{
	}

	http_client client;
};

HttpClient::HttpClient(const std::string& host)
	: client_impl_(std::make_shared<HttpClientImpl>(host))
{
}

HttpResponse HttpClient::Request(HttpRequest& request)
{
	auto task = client_impl_->client.request(request.GetRequestImpl());
	auto status = task.wait();
	if (status != pplx::task_group_status::completed)
		throw std::exception("status incompleted");

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