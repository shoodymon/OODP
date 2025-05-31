#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	setlocale(0, "");
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;
	char buffer[512];

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "�� ������� ������� �����." << endl;
		WSACleanup();
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);

	if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
		cerr << "������������ IP-�����." << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		cerr << "������ ����������� � �������." << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	cout << "����������� � ������� �������!" << endl;

	while (true) {
		cout << "\n������� ��������� (�������� 'exit' ��� ������): ";
		string message;
		getline(cin, message);

		send(clientSocket, message.c_str(), message.length(), 0);

		if (message == "exit") {
			break;
		}

		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
		if (bytesReceived > 0) {
			buffer[bytesReceived] = '\0';
			cout << "����� �� �������: " << buffer << endl;
		}
		else {
			cerr << "������ ��������� ������ �� �������." << endl;
			break;
		}
	}

	closesocket(clientSocket);
	WSACleanup();

	return 0;
}
