#pragma once

#include "MutexQueue.h"
#include "Message.h"
#include <thread>
#include <iostream>
#include <atomic>

namespace SecureBrowser
{

enum class LogLevel
{
	Debug,
	Info,
	Warning,
	Error,
};

struct LogMessage
{
	std::string message;
	LogLevel level;
};

class Logger final
{
public:
	//if ostream is file, please, don't close it. Logger automatically close it in destructor
	explicit __declspec(dllexport) Logger(LogLevel min_log_level = LogLevel::Debug,
			std::ostream& write_to = std::cout);
	__declspec(dllexport) ~Logger();
	__declspec(dllexport) MessageBuilder operator<<(LogLevel level);
	__declspec(dllexport) void Log(const std::string& msg, LogLevel level = LogLevel::Info);				   

private:
	void WriteThread();
	void Write(const LogMessage& message);

	std::thread write_thread_;
	std::ostream stream_;
	std::atomic<bool> is_running_;
	LogLevel min_level_;
	MutexQueue<LogMessage> message_queue_;
};

} // namespace SecureBrowser