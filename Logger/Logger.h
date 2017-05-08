#pragma once

#include "MutexQueue.h"
#include "MessageBuilder.h"
#include "LoggerUtils.h"
#include <thread>
#include <iostream>
#include <atomic>

namespace BrowserLogger
{

class Logger final
{
public:
	explicit LOGGER_API Logger(LogLevel min_log_level = LogLevel::Debug,
		std::ostream& write_to = std::cout,
		std::function<std::string(const LogMessage&)> formatter = DefaultFormat);
	LOGGER_API ~Logger();

	LOGGER_API void Flush();

	/* Main idea of output: 1) After call with LogLevel create temporary object of MessageBuilder.
	 * 2)call other chained << operators for MessageBuilder
	 * 3)return string by callback function in destructor of MessageBuilder */
	LOGGER_API MessageBuilder operator<<(LogLevel level);

private:

	void WriteThread();
	void Write(const LogMessage& log_message);
	void Log(const std::string& msg, LogLevel level);
	void TryWrite();

	std::mutex lock_writing_;
	std::mutex lock_waiting_message_;
	std::condition_variable wait_message_;
	std::thread write_thread_;
	std::ostream stream_;
	std::atomic<bool> is_running_;
	LogLevel min_level_;
	MutexQueue<LogMessage> message_queue_;
	std::function<std::string(const LogMessage& log_message)> formatter_;
};

} // namespace BrowserLogger