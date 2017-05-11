#include "Logger.h"
#include <Windows.h>
#include <string>
#include <fstream>

using namespace BrowserLogger;

Logger::Logger(LogLevel min_log_level, std::ostream& write_to, std::function<std::string(const LogMessage&)> formatter)
	: stream_(write_to.rdbuf())
	, is_running_(true)
	, min_level_(min_log_level)
	, message_queue_()
	, formatter_(formatter)
{
	//initialize thread here, for avoid using not initialized *this
	write_thread_ = std::thread(&Logger::WriteThread, this);
}

Logger::~Logger()
{
	//wait for flush all messages
	is_running_ = false;
	Flush();

	//Notify all threads to end waiting for messages
	wait_message_.notify_all();
	if (write_thread_.joinable())
	{
		write_thread_.join();
	}
}

void Logger::Flush()
{
	while (!message_queue_.IsEmpty())
	{
		TryWrite();
	}
}

LOGGER_API void BrowserLogger::Logger::SetOutput(std::ostream& write_to)
{
	stream_.set_rdbuf(write_to.rdbuf());
}

LOGGER_API MessageBuilder Logger::MakeMessageBuilder(LogLevel level, const std::string& file,
	const std::string& function, unsigned int line, const tm& time)
{
	return MessageBuilder(bind(&Logger::Log, this, std::placeholders::_1, level, file, function, line, time));
}

void Logger::WriteThread()
{
	while (is_running_ || !message_queue_.IsEmpty())
	{
		std::unique_lock<std::mutex> lock(lock_waiting_message_);
		wait_message_.wait(lock);

		if (!message_queue_.IsEmpty())
		{
			TryWrite();
		}
	}
}

void Logger::Write(const LogMessage& log_message)
{
	if (log_message.level >= min_level_)
	{
		std::unique_lock<std::mutex> lock(lock_writing_);

		stream_ << log_message.message;

		if (IsDebuggerPresent())
			OutputDebugStringA(log_message.message.c_str());
	}
}

void Logger::Log(const std::string& msg, LogLevel level, const std::string& file,
	const std::string& function, unsigned int line, const tm& time)
{
	std::string formatted_message = formatter_({ msg, level, file, function, line, time });

	message_queue_.Add({ formatted_message, level });
	wait_message_.notify_one();
}

void Logger::TryWrite()
{
	try
	{
		Write(message_queue_.Pop());
	}
	catch (std::out_of_range&)
	{
		//ignore this exception, it's happened because other thread got message faster
	}
}