#pragma once

#include "MutexQueue.h"
#include "Message.h"
#include "Utils.h"
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
	explicit LOGGER_API Logger(LogLevel min_log_level = LogLevel::Debug,
		std::ostream& write_to = std::cout);
	LOGGER_API ~Logger();

	/* Main idea of output: 1) After call with LogLevel create temporary object of MessageBuilder.
	 * 2)call other chained << operators for MessageBuilder
	 * 3)return string by callback function in destructor of MessageBuilder */
	LOGGER_API MessageBuilder operator<<(LogLevel level);

private:
	void WriteThread();
	void Write(const LogMessage& message);
	void Log(const std::string& msg, LogLevel level = LogLevel::Info);

	std::thread write_thread_;
	std::ostream stream_;
	std::atomic<bool> is_running_;
	LogLevel min_level_;
	MutexQueue<LogMessage> message_queue_;
};

} // namespace SecureBrowser