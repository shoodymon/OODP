#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <algorithm> // ��� std::transform
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	setlocale(0, "");
	WSADATA wsadata;
	SOCKET sock;
	sockaddr_in serveraddr;
	char buffer[1024];

	// ������������� Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cerr << "������ ������������� Winsock." << std::endl;
		return 1;
	}

	// �������� ������
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "������ �������� ������." << std::endl;
		WSACleanup();
		return 1;
	}

	// ��������� ������ �������
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(54000);
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr); // IP-����� ������� 
	// ���� � ��� ���������� ����� ������� � �������� �������. 

	// ����������� � �������
	if (connect(sock, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
		std::cerr << "������ ����������� � �������." << std::endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	std::cout << "���������� � �������." << std::endl;

	// ����� �����������
	while (true) {
		// �������� ��������� �� �������
		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0) {
			std::cerr << "���������� � �������� �������." << std::endl;
			break;
		}
		std::cout << "��������� �� �������: " << buffer << std::endl;

		// �������������� ������ � ������� �������
		std::string receivedMessage(buffer);
		std::transform(receivedMessage.begin(), receivedMessage.end(), receivedMessage.begin(), ::toupper);

		// ���������� ��������� ��������� �������
		send(sock, receivedMessage.c_str(), static_cast<int>(receivedMessage.size()), 0);
	}

	// �������� ������
	closesocket(sock);
	WSACleanup();
	return 0;
}
