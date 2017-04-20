#include "Message.h"

using namespace SecureBrowser;

MessageBuilder::MessageBuilder(const std::function<void(std::string&&)>& completed_string_function)
		: message_stream_(std::make_shared<std::stringstream>())
		, completed_string_function_(completed_string_function) {}

MessageBuilder::~MessageBuilder()
{
	//call function with builded string as a parameter
	completed_string_function_(message_stream_->str());
}