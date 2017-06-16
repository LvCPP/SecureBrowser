#define WIN32_LEAN_AND_MEAN
#include "Client.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

/*
General message structure

|keyword |type   |content_size |content           |
|4 bytes |1 byte |8 bytes      |content_size bytes|

===================================================
Config request message

|keyword |type   |content_size |content           |
|ggwp    |0      |0            |      NULL        |

===================================================
Config replay message

|keyword |type   |content_size |content           |
|ggwp    |1      |config size  |     config       |

===================================================
Send file message

|keyword |type   |content_size |content                                                           |
|ggwp    |2      |  size       |file name size 4 bytes| file name| file size 8 bytes| file content|

*/

std::vector<char> create_request_config_message() {
	return std::vector<char>{
		'g', 'g', 'w', 'p', 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
}

std::streampos fileSize(const std::string& filePath) {

	std::streampos fsize = 0;
	std::ifstream file(filePath, std::ios::binary);

	fsize = file.tellg();
	file.seekg(0, std::ios::end);
	fsize = file.tellg() - fsize;
	file.close();

	return fsize;
}
std::vector<char> create_send_file_message(const std::string& filepath)
{
	std::vector<char> messgage{ 'g', 'g', 'w', 'p', 2 };
	messgage.insert(messgage.end(), 8, 0);
	messgage.insert(messgage.end(), 4, 0);

	size_t  pos = filepath.rfind('\\');

	std::string filename = pos != std::string::npos ? filepath.substr(pos + 1) : filepath;

	*((std::int32_t*)(messgage.data() + 13)) = filename.size();
	messgage.insert(messgage.end(), filename.data(), filename.data() + filename.size());

	size_t write_pos = messgage.size();
	messgage.insert(messgage.end(), 8, 0);

	std::uint64_t file_size = fileSize(filepath);
	*((std::uint64_t*)(messgage.data() + write_pos)) = file_size;

	std::ifstream input(filepath, std::ios::binary);
	// copies all data into buffer
	std::vector<char> buffer((
		std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));

	messgage.insert(messgage.end(), buffer.begin(), buffer.end());

	return messgage;
}



std::string parse_replay_config_message(const std::vector<char>& buffer) {

	std::uint64_t size = *((std::uint64_t*)(buffer.data() + 5));
	return std::string(buffer.data() + 13, size);
}



ErrorCode Client::get_config(std::string& config)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return ErrorCode::ErrorUnknown;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	{
		iResult = getaddrinfo(m_ip.c_str(), DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return ErrorCode::ErrorUnknown;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return ErrorCode::SocketBusy;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// Send an initial buffer

		ZeroMemory(recvbuf, recvbuflen);


		auto message = create_request_config_message();

		iResult = send(ConnectSocket, message.data(), message.size(), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
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

		config = parse_replay_config_message(buffer);
	}


	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return ErrorCode::Ok;
}


ErrorCode
Client::send_file(const std::string& path_to_file, const std::string& session)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return ErrorCode::ErrorUnknown;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	{
		iResult = getaddrinfo(m_ip.c_str(), DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return ErrorCode::ErrorUnknown;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return ErrorCode::SocketBusy;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// Send an initial buffer

		ZeroMemory(recvbuf, recvbuflen);


		auto message = create_send_file_message(path_to_file);

		iResult = send(ConnectSocket, message.data(), message.size(), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return ErrorCode::ServerNotFound;
		}

		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
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

Client::Client(const std::string& ip)
	:m_ip(ip)
	, m_mutex()
{
}