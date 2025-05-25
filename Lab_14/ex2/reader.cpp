#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
	const char* pipeName = R"(\\.\pipe\my_named_pipe)";
	HANDLE hPipe;
	char buffer[512];
	DWORD bytesRead;

	// Подключение к именованному каналу
	hPipe = CreateFileA(
		pipeName,
		GENERIC_READ, // Доступ для чтения
		0, // Ожидание совместного доступа
		nullptr, // Дескриптор безопасности
		OPEN_EXISTING, // Подключение к существующему каналу
		0, // Флаги
		nullptr // Шаблон
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		cerr << "Failed to connect to the named pipe." << endl;
		return 1;
	}

	cout << "Connected to the named pipe. Reading messages..." << endl;

	while (true) {
		if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
			buffer[bytesRead] = '\0'; // Завершаем строку
			cout << "Received: " << buffer << endl;
		}
		else {
			cerr << "Failed to read from the pipe or all messages are read." << endl;
			break;
		}
	}

	CloseHandle(hPipe);
	return 0;
}
