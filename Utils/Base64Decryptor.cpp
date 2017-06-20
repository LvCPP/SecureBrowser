#include "Base64Decryptor.h"

using namespace Decryptor;

static std::string BASE64_SYMBOLS_ =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

static inline bool IsBase64(unsigned char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64Decryptor::Decode(std::string const& encoded_string)
{
	size_t length = encoded_string.size();
	size_t i = 0;
	int pos = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string decrypted;

	while (length-- && (encoded_string[pos] != '=') && IsBase64(encoded_string[pos])) {
		char_array_4[i++] = encoded_string[pos++];
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = static_cast<unsigned char>(BASE64_SYMBOLS_.find(char_array_4[i]));

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				decrypted += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (size_t j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (size_t j = 0; j < 4; j++)
			char_array_4[j] = static_cast<unsigned char>(BASE64_SYMBOLS_.find(char_array_4[j]));

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (size_t j = 0; (j < i - 1); j++) decrypted += char_array_3[j];
	}

	return decrypted;
}