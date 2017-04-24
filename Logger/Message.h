#pragma once

#include "Utils.h"
#include <sstream>
#include <functional>

namespace SecureBrowser
{

class MessageBuilder
{
public:
	explicit MessageBuilder(
		const std::function<void(std::string&&)>& completed_string_function);

	MessageBuilder(const MessageBuilder&& builder);

	//User code calls destructor, so we need to export it
	LOGGER_API ~MessageBuilder();

	template <class T>
	__declspec(dllexport) friend std::ostream& operator<< (MessageBuilder&& builder,
		const T& object)
	{
		return builder.message_stream_ << object;
	}

private:
	std::stringstream message_stream_;
	std::function<void(std::string&&)> completed_string_function_;
};

} // namespace SecureBrowser