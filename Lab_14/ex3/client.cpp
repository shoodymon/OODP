#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <algorithm> // Для std::transform
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	setlocale(0, "");
	WSADATA wsadata;
	SOCKET sock;
	sockaddr_in serveraddr;
	char buffer[1024];

	// Инициализация Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cerr << "Ошибка инициализации Winsock." << std::endl;
		return 1;
	}

	// Создание сокета
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Ошибка создания сокета." << std::endl;
		WSACleanup();
		return 1;
	}

	// Настройка адреса сервера
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(54000);
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr); // IP-адрес сервера 
	// Порт – это логическая точка доступа к сетевому сервису. 

	// Подключение к серверу
	if (connect(sock, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
		std::cerr << "Ошибка подключения к серверу." << std::endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	std::cout << "Подключено к серверу." << std::endl;

	// Обмен сообщениями
	while (true) {
		// Получаем сообщение от сервера
		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0) {
			std::cerr << "Соединение с сервером закрыто." << std::endl;
			break;
		}
		std::cout << "Сообщение от сервера: " << buffer << std::endl;

		// Преобразование строки в верхний регистр
		std::string receivedMessage(buffer);
		std::transform(receivedMessage.begin(), receivedMessage.end(), receivedMessage.begin(), ::toupper);

		// Отправляем изменённое сообщение серверу
		send(sock, receivedMessage.c_str(), static_cast<int>(receivedMessage.size()), 0);
	}

	// Закрытие сокета
	closesocket(sock);
	WSACleanup();
	return 0;
}
