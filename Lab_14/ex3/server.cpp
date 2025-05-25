#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

//	Задание 3.
//	Двусторонний pipes.
//	Реализовать двустороннюю передачу данных между двумя процессами через два pipes.
//	1. Создайте два pipes.
//	2. Процесс - родитель отправляет строку дочернему процессу, а дочерний должен изменить строку(формат изменения выбирается
//	самостоятельно) и отправить её обратно родителю.
//	3. Родитель должен вывести изменённую строку на экран.
//	Рекомендации: используйте два pipes и следите за порядком выполнения
//	процессов.

// принцип «запрос-ответ»:
//1.	Родительский процесс отправляет строку в pipe.
//2.	Дочерний процесс получает строку, изменяет её(например, переводит в верхний регистр) и отправляет обратно.
//3.	Родительский процесс получает обработанную строку и выводит её.
//В программе используется два пайпа, чтобы разделить каналы передачи.Один пайп идёт от родителя к дочернему, второй – от дочернего к родителю.

using namespace std;

int main() {
	setlocale(0, "");
	WSADATA wsadata;
	SOCKET listeningSocket, clientSocket;
	sockaddr_in serveraddr, clientaddr;
	int clientAddrSize = sizeof(clientaddr);
	char buffer[1024];

	// Инициализация Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cerr << "Ошибка инициализации Winsock." << std::endl;
		return 1;
	}

	// Создание сокета для прослушивания (Сокет – это программный интерфейс для сетевого взаимодействия)
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket == INVALID_SOCKET) {
		std::cerr << "Ошибка создания сокета." << std::endl;
		WSACleanup();
		return 1;
	}

	// Настройка адреса сервера
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(54000);
	serveraddr.sin_addr.s_addr = INADDR_ANY; // Любой входящий IP

	// Привязка сокета к адресу
	if (bind(listeningSocket, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
		std::cerr << "Ошибка привязки сокета." << std::endl;
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	// Прослушивание входящих соединений
	if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Ошибка прослушивания." << std::endl;
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "Сервер ожидает подключений..." << std::endl;

	// Ожидание подключения клиента
	clientSocket = accept(listeningSocket, (sockaddr*)&clientaddr, &clientAddrSize);
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "Ошибка подключения клиента." << std::endl;
		closesocket(listeningSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "Клиент подключен!" << std::endl;

	// Обмен сообщениями
	std::string message;
	while (true) {
		std::cout << "Введите сообщение для клиента (или 'exit' для выхода): ";
		std::getline(std::cin, message);

		if (message == "exit") {
			break;
		}

		// Отправляем сообщение клиенту
		send(clientSocket, message.c_str(), static_cast<int>(message.size()), 0);

		// Ожидаем ответ от клиента
		memset(buffer, 0, sizeof(buffer));
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived <= 0) {
			std::cerr << "Соединение с клиентом закрыто." << std::endl;
			break;
		}
		std::cout << "Сообщение от клиента: " << buffer << std::endl;
	}

	// Закрытие сокетов
	closesocket(clientSocket);
	closesocket(listeningSocket);
	WSACleanup();
	return 0;
}
