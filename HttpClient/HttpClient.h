#pragma once

#include"HttpRequest.h"
#include"HttpResponse.h"
#include"HttpClientUtils.h"
#include<memory>

class HttpClientImpl;

namespace BrowserHttp {

class HttpClient
{
public:
	HTTPCLIENT_API HttpClient(const std::string& host);

	HTTPCLIENT_API HttpResponse Request(HttpRequest& request);
	HTTPCLIENT_API HttpResponse Get(const std::string& path);
	HTTPCLIENT_API HttpResponse Post(const std::string& path, const std::vector<unsigned char>& data);

private:
	std::shared_ptr<HttpClientImpl> client_impl_;
};

}

