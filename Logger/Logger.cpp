#include "Logger.h"
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>
#include <map>

using namespace SecureBrowser;

static std::map<LogLevel, int> log_level_weight{{LogLevel::Debug, 0}
	,{LogLevel::Info, 1}
	,{LogLevel::Warning, 2}
	,{LogLevel::Error, 3}};

static std::map<LogLevel, std::string> log_level_name{{LogLevel::Debug, "Debug"}
	,{LogLevel::Info, "Info"}
	,{LogLevel::Warning, "Warning"}
	,{LogLevel::Error, "Error"}};

Logger::Logger(LogLevel min_log_level, std::ostream& write_to)
		: stream_(new std::ostream(write_to.rdbuf()))
		, is_running_(true)
		, min_level_(min_log_level)
		, message_queue_()
{
	//initialize thread here, for avoid using not initialized *this
	write_thread_ = std::thread(&Logger::WriteThread, this);
}

Logger::Logger(LogLevel min_log_level, std::string& write_to_file)
		: is_running_(true)
		, min_level_(min_log_level)
		, message_queue_()
{
	std::unique_ptr<std::ofstream> file(new std::ofstream(write_to_file, std::ios::app));
	if (file->is_open())
	{
		stream_ = move(file);
		write_thread_ = std::thread(&Logger::WriteThread, this);
	}
	else
	{
		throw std::invalid_argument("Can't open file");
	}
}

Logger::~Logger()
{
	//wait for flush all messages
	is_running_ = false;
	if (write_thread_.joinable())
	{
		write_thread_.join();
	}

	//if it's file - close file. dynamic cast return nullptr if can't downcast
	auto file = dynamic_cast<std::ofstream*>(stream_.get());
	if (file)
		file->close();
}

static std::string GetFormattedCurrentDateTime()
{
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	char buf[30] = { 0 };
	strftime(buf, sizeof(buf), "[%d/%m/%y at %T]", localtime(&now));
	return buf;
}

void Logger::Debug(const std::string& msg)
{
	Log(msg, LogLevel::Debug);
}

void Logger::Info(const std::string& msg)
{
	Log(msg, LogLevel::Info);
}

void Logger::Warning(const std::string& msg)
{
	Log(msg, LogLevel::Warning);
}

void Logger::Error(const std::string& msg)
{
	Log(msg, LogLevel::Error);
}

void Logger::Log(const std::string& msg, const LogLevel level)
{
	message_queue_.Add({ msg, level });
}

void Logger::WriteThread()
{
	while (is_running_ || !message_queue_.IsEmpty())
	{
		if (!message_queue_.IsEmpty())
		{
			try
			{
				Write(message_queue_.Pop());
			}
			catch (std::exception& ex)
			{
				Write({ ex.what(), LogLevel::Error });
			}
		}
	}
}

void Logger::Write(const Message& msg) const
{
	if (log_level_weight[msg.level] >= log_level_weight[min_level_])
	{
		*stream_ << GetFormattedCurrentDateTime() << " [" << log_level_name[msg.level] << "] "
			<< msg.message << std::endl;
	}
}
