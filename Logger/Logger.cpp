#include "Logger.h"
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <iomanip>

using namespace SecureBrowser;

static const std::map<LogLevel, std::string> log_level_name{{LogLevel::Debug, "Debug"}
	,{LogLevel::Info, "Info"}
	,{LogLevel::Warning, "Warning"}
	,{LogLevel::Error, "Error"}};

Logger::Logger(LogLevel min_log_level, std::ostream& write_to)
	: stream_(write_to.rdbuf())
	, is_running_(true)
	, min_level_(min_log_level)
	, message_queue_()
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
	cond_var_.notify_all();
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

MessageBuilder Logger::operator<<(LogLevel level)
{
	//after string is builded, Logger::Log will be called with those string as a parameter
	return MessageBuilder(bind(&Logger::Log, this, std::placeholders::_1, level));
}

void Logger::WriteThread()
{
	while (is_running_ || !message_queue_.IsEmpty())
	{
		std::unique_lock<std::mutex> lock(lock_waiting_message_);
		cond_var_.wait(lock);

		if (!message_queue_.IsEmpty())
		{
			TryWrite();
		}
	}
}

void Logger::Write(const LogMessage& message)
{
	if (message.level >= min_level_)
	{
		std::unique_lock<std::mutex> lock(lock_writing_);

		time_t time_now = time(nullptr);
		tm local_time_now;
		localtime_s(&local_time_now, &time_now);

		stream_ << std::put_time(&local_time_now, "[%d/%m/%y at %T]") << " [" 
			<< log_level_name.at(message.level) << "] " << message.message << std::endl;
	}
}

void Logger::Log(const std::string& msg, LogLevel level)
{
	message_queue_.Add({ msg, level });
	cond_var_.notify_one();
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
