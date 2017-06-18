#define WIN32_LEAN_AND_MEAN
#include "Client.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace TCP_client;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "5938"

/*
General message structure

|keyword |type   |content_size |content           |
|4 bytes |1 byte |8 bytes      |content_size bytes|

===================================================
Config request message

|keyword |type   |content_size |content           |
|ggwp    |0      |0            |      NULL        |

===================================================
Config reply message

|keyword |type   |content_size |content           |
|ggwp    |1      |config size  |     config       |

===================================================
Send file message

|keyword |type   |content_size |content                                                           |
|ggwp    |2      |  size       |file name size 4 bytes| file name| file size 8 bytes| file content|

*/

std::vector<char> CreateRequestConfigMessage()
{
	return std::vector<char>
	{
		'g', 'g', 'w', 'p', 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
}

std::streampos FileSize(const std::string& file_path)
{
	std::streampos fsize = 0;
	std::ifstream file(file_path, std::ios::binary);

	fsize = file.tellg();
	file.seekg(0, std::ios::end);
	fsize = file.tellg() - fsize;
	file.close();

	return fsize;
}
std::vector<char> CreateSendFileMessage(const std::string& file_path)
{
	std::vector<char> messgage{ 'g', 'g', 'w', 'p', 2 };
	messgage.insert(messgage.end(), 8, 0);
	messgage.insert(messgage.end(), 4, 0);

	size_t  pos = file_path.rfind('\\');

	std::string filename = pos != std::string::npos ? file_path.substr(pos + 1) : file_path;

	*reinterpret_cast<int32_t*>(messgage.data() + 13) = filename.size();
	messgage.insert(messgage.end(), filename.data(), filename.data() + filename.size());

	size_t write_pos = messgage.size();
	messgage.insert(messgage.end(), 8, 0);

	uint64_t file_size = FileSize(file_path);
	*reinterpret_cast<uint64_t*>(messgage.data() + write_pos) = file_size;

	std::ifstream input(file_path, std::ios::binary);
	// copies all data into buffer
	std::vector<char> buffer(file_size);
	input.read(&buffer[0], file_size);

	messgage.insert(messgage.end(), buffer.begin(), buffer.begin() + file_size);

	return messgage;
}

std::string ParseReplyConfigMessage(const std::vector<char>& buffer)
{
	uint64_t size = *(uint64_t*)(buffer.data() + 5);
	return std::string(buffer.data() + 13, size);
}

ErrorCode Client::GetConfig(std::string& config) const
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	addrinfo* result = nullptr;
	addrinfo* ptr = nullptr;
	addrinfo hints;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return ErrorCode::ErrorUnknown;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	{
		iResult = getaddrinfo(ip_.c_str(), DEFAULT_PORT, &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return ErrorCode::ErrorUnknown;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
		{

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET)
			{
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return ErrorCode::SocketBusy;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Unable to connect to server!\n");
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// Send an initial buffer

		ZeroMemory(recvbuf, recvbuflen);


		auto message = CreateRequestConfigMessage();

		iResult = send(ConnectSocket, message.data(), message.size(), 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return ErrorCode::ErrorUnknown;
		}

		// Receive until the peer closes the connection

		std::vector<char> buffer;
		buffer.reserve(10 * 1024);

		do
		{
			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
				buffer.insert(buffer.end(), recvbuf, recvbuf + recvbuflen);
			else if (iResult == 0)
				printf("End session\n");
			else
				printf("recv failed with error: %d\n", WSAGetLastError());

		} while (iResult > 0);

		config = ParseReplyConfigMessage(buffer);
	}


	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return ErrorCode::Ok;
}


ErrorCode Client::SendFile(const std::string& path_to_file, const std::string& session) const
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	addrinfo* result = nullptr;
	addrinfo* ptr = nullptr;
	addrinfo hints;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return ErrorCode::ErrorUnknown;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	{
		iResult = getaddrinfo(ip_.c_str(), DEFAULT_PORT, &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return ErrorCode::ErrorUnknown;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
		{
			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET)
			{
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return ErrorCode::SocketBusy;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Unable to connect to server!\n");
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// Send an initial buffer

		ZeroMemory(recvbuf, recvbuflen);


		auto message = CreateSendFileMessage(path_to_file);

		iResult = send(ConnectSocket, message.data(), message.size(), 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return ErrorCode::ErrorUnknown;
		}
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return ErrorCode::Ok;
}

Client::Client()
	: mutex_()
{
	ip_ = "127.0.0.1";
}

namespace Utils
{

template <>
void AnFill<Client>(An<Client>& an)
{
	static Client instance;
	an = &instance;
}

} // namespace Utils