#include <string>

namespace Decryptor
{

class Base64Decryptor
{
public:
	Base64Decryptor() = delete;
	Base64Decryptor(Base64Decryptor&) = delete;
	Base64Decryptor(Base64Decryptor&&) = delete;
	Base64Decryptor& operator= (Base64Decryptor&) = delete;
	Base64Decryptor& operator= (Base64Decryptor&&) = delete;

	static std::string Decode(std::string const& encoded_string);
};

} // namespace Decryptor