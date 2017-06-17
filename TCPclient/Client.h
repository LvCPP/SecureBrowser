#pragma once

#include <string>
#include <mutex>

namespace TCP_client
{
enum class ErrorCode
{
	ErrorUnknown = 0,
	SocketBusy,
	ServerNotFound,
	NoResponseFromServer,
	Ok
};


class Client
{
public:
	Client(const std::string& ip);

	ErrorCode GetConfig(std::string& config);
	ErrorCode SendFile(const std::string& path_to_file, const std::string& session);


private:

	std::string ip_;
	std::mutex mutex_;
};
}