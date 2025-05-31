#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	setlocale(0, "");
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	sockaddr_in serverAddr, clientAddr;
	int addrLen = sizeof(clientAddr);

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		cerr << "Не удалось создать сокет." << endl;
		WSACleanup();
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(8080);

	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		cerr << "Ошибка привязки сокета." << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	listen(serverSocket, 5);
	cout << "Сервер запущен. Ожидание подключения клиента..." << endl;

	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrLen);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "Ошибка подключения клиента." << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	cout << "Клиент подключен!" << endl;

	char buffer[512];
	while (true) {
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
		if (bytesReceived > 0) {
			buffer[bytesReceived] = '\0'; // Завершаем строку
			cout << "Получено сообщение от клиента: " << buffer << endl;

			// Проверяем выход
			if (string(buffer) == "exit") {
				cout << "Клиент завершил соединение." << endl;
				break;
			}

			// Изменяем сообщение
			string modifiedMessage = string(buffer) + " (изменено сервером)";
			send(clientSocket, modifiedMessage.c_str(), modifiedMessage.length(), 0);
		}
		else {
			cerr << "Ошибка получения данных или клиент отключился." << endl;
			break;
		}
	}

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();

	return 0;
}
