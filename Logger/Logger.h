#pragma once

#include "MutexQueue.h"
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

struct Message
	{
		std::string message;
		LogLevel level;
	};

class Logger final
{
public:
	Logger(LogLevel min_log_level = LogLevel::Debug, std::ostream& write_to = std::cout);
	Logger(LogLevel min_log_level, std::string& write_to_file);
	~Logger();

	void Debug(const std::string& msg);
	void Info(const std::string& msg);
	void Warning(const std::string& msg);
	void Error(const std::string& msg);

private:
	void Log(const std::string& msg, LogLevel level = LogLevel::Info);
	void WriteThread();
	void Write(const Message& msg) const;

	std::thread write_thread_;
	std::unique_ptr<std::ostream> stream_;
	std::atomic<bool> is_running_;
	LogLevel min_level_;
	MutexQueue<Message> message_queue_;

	Logger(const Logger& logger) = delete;
	Logger& operator=(const Logger& logger) = delete;
};

} // namespace SecureBrowser