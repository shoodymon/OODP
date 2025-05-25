#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

//	������� 3.
//	������������ pipes.
//	����������� ������������ �������� ������ ����� ����� ���������� ����� ��� pipes.
//	1. �������� ��� pipes.
//	2. ������� - �������� ���������� ������ ��������� ��������, � �������� ������ �������� ������(������ ��������� ����������
//	��������������) � ��������� � ������� ��������.
//	3. �������� ������ ������� ��������� ������ �� �����.
//	������������: ����������� ��� pipes � ������� �� �������� ����������
//	���������.

// ������� �������-�����:
//1.	������������ ������� ���������� ������ � pipe.
//2.	�������� ������� �������� ������, �������� �(��������, ��������� � ������� �������) � ���������� �������.
//3.	������������ ������� �������� ������������ ������ � ������� �.
//� ��������� ������������ ��� �����, ����� ��������� ������ ��������.���� ���� ��� �� �������� � ���������, ������ � �� ��������� � ��������.

using namespace std;

int main() {
	setlocale(0, "");
	WSADATA wsadata;
	SOCKET listeningSocket, clientSocket;
	sockaddr_in serveraddr, clientaddr;
	int clientAddrSize = sizeof(clientaddr);
	char buffer[1024];

	// ������������� Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cerr << "������ ������������� Winsock." << std::endl;
		return 1;
	}

	// �������� ������ ��� ������������� (����� � ��� ����������� ��������� ��� �������� ��������������)
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket == INVALID_SOCKET) {
		std::cerr << "������ �������� ������." << std::endl;
		WSACleanup();
		return 1;
	}

	// ��������� ������ �������
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(54000);
	serveraddr.sin_addr.s_addr = INADDR_ANY; // ����� �������� IP

	// �������� ������ � ������
	if (bind(listeningSocket, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
		std::cerr << "������ �������� ������." << std::endl;
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	// ������������� �������� ����������
	if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "������ �������������." << std::endl;
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "������ ������� �����������..." << std::endl;

	// �������� ����������� �������
	clientSocket = accept(listeningSocket, (sockaddr*)&clientaddr, &clientAddrSize);
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "������ ����������� �������." << std::endl;
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "������ ���������!" << std::endl;

	// ����� �����������
	std::string message;
	while (true) {
		std::cout << "������� ��������� ��� ������� (��� 'exit' ��� ������): ";
		std::getline(std::cin, message);

		if (message == "exit") {
			break;
		}

		// ���������� ��������� �������
		send(clientSocket, message.c_str(), static_cast<int>(message.size()), 0);

		// ������� ����� �� �������
		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0) {
			std::cerr << "���������� � �������� �������." << std::endl;
			break;
		}
		std::cout << "��������� �� �������: " << buffer << std::endl;
	}

	// �������� �������
	closesocket(clientSocket);
	closesocket(listeningSocket);
	WSACleanup();
	return 0;
}
