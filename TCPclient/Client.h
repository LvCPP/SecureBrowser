#pragma once

#include <An.hpp>
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
	Client();

	ErrorCode GetConfig(std::string& config) const;
	ErrorCode SendFile(const std::string& path_to_file, const std::string& session) const;


private:

	std::string ip_;
	std::mutex mutex_;
};
}

namespace Utils
{

template <>
void AnFill<TCP_client::Client>(An<TCP_client::Client>& an);

} // namespace Utils