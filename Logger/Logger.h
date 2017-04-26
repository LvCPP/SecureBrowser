#pragma once

#include "MutexQueue.h"
#include "MessageBuilder.h"
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

class Logger final
{
public:
	explicit LOGGER_API Logger(LogLevel min_log_level = LogLevel::Debug,
		std::ostream& write_to = std::cout);
	LOGGER_API ~Logger();

	LOGGER_API void Flush();

	/* Main idea of output: 1) After call with LogLevel create temporary object of MessageBuilder.
	 * 2)call other chained << operators for MessageBuilder
	 * 3)return string by callback function in destructor of MessageBuilder */
	LOGGER_API MessageBuilder operator<<(LogLevel level);

private:
	struct LogMessage
	{
		std::string message;
		LogLevel level;
	};

	void WriteThread();
	void Write(const LogMessage& message);
	void Log(const std::string& msg, LogLevel level = LogLevel::Info);
	void TryWrite();

	std::mutex lock_writing_;
	std::mutex lock_waiting_message_;
	std::condition_variable cond_var_;
	std::thread write_thread_;
	std::ostream stream_;
	std::atomic<bool> is_running_;
	LogLevel min_level_;
	MutexQueue<LogMessage> message_queue_;
};

} // namespace SecureBrowser