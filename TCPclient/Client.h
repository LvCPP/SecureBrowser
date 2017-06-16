#pragma once

#include <string>
#include <mutex>

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

	ErrorCode get_config(std::string& config);
	ErrorCode send_file(const std::string& path_to_file, const std::string& session);


private:

	std::string m_ip;
	std::mutex m_mutex;
};