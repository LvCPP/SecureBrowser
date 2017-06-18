#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <array>
#include <fstream>
// Need to link with Ws2_32.lib
#pragma comment(lib,"ws2_32")
//#pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "5938"



namespace
{
const std::string default_cfg =
"max_fps:60\n"
"session_id:4300\n";

std::vector<char> CreateConfigReplay()
{
	std::vector<char> message{ 'g', 'g', 'w', 'p', 1 };

	std::array<char, 8> size = {};
	*reinterpret_cast<std::uint64_t*>(size.data()) = default_cfg.size();

	message.insert(message.end(), size.data(), size.data() + size.size());

	message.insert(message.end(), default_cfg.data(), default_cfg.data() + default_cfg.size());

	return message;
}
}

int __cdecl main()
{
	WSADATA wsaData;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = nullptr;
	struct addrinfo hints;

	char recvbuf[DEFAULT_BUFLEN] = {};
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	for (;;)
	{
		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR)
		{
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		// Accept a client socket
		ClientSocket = accept(ListenSocket, nullptr, nullptr);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		// Receive until the peer shuts down the connection

		std::vector<char> buffer;
		buffer.reserve(10 * 1024 * 1024);
		do
		{
			ZeroMemory(recvbuf, recvbuflen);
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
			{
				buffer.insert(buffer.end(), recvbuf, recvbuf + iResult);
			}
			else if (iResult == 0)
			{
				printf("End session\n");
			}
			else 
			{
				printf("recv failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				break;
			}
		} while (iResult > 0);


		printf("Message received\n");

		if (buffer[4] == 0)
		{
			printf("Preparing answer\n");

			auto replay = CreateConfigReplay();
			int iSendResult = send(ClientSocket, replay.data(), replay.size(), 0);

			if (iSendResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
			}
		}
		else if (buffer[4] == 2)
		{
			const uint32_t string_size = *reinterpret_cast<uint32_t*>(buffer.data() + 13);
			std::string fileName(buffer.data() + 17, string_size);

			std::ofstream file(fileName, std::ios::binary);

			const uint64_t file_size = *reinterpret_cast<uint64_t*>(buffer.data() + 17 + string_size);

			file.write(buffer.data() + 17 + string_size + 8, file_size);
			file.close();

			printf("Received file with file name size %d file name %s file size %d", 
				string_size, fileName.c_str(), file_size);
		}

		buffer.clear();

		// shutdown the connection since we're done
		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	}
}