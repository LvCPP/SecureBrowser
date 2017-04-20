#pragma once

#include <sstream>
#include <memory>
#include <functional>

namespace SecureBrowser
{

class MessageBuilder
{
public:
	explicit __declspec(dllexport) MessageBuilder(
			std::function<void(std::string&&)> completed_string_function);

	__declspec(dllexport) ~MessageBuilder();

	template <class T>
	__declspec(dllexport) friend std::ostream& operator<< (const MessageBuilder& builder,
			const T& object)
	{
		return *builder.message_stream_ << object;
	}

private:
	std::shared_ptr<std::stringstream> message_stream_;
	std::function<void(std::string&&)> completed_string_function_;
};

} // namespace SecureBrowser