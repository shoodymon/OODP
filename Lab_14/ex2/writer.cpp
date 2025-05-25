#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

//	Задание 2.
//	Pipes для передачи нескольких строк.
//	Реализовать передачу нескольких строк от родительского процесса к дочернему через pipes.
//	1. Используйте тот же подход, что и в первом задании, но передавайте несколько строк(например, 5 строк).
//	2. Родительский процесс должен принимать ввод от пользователя и отправлять строки в дочерний процесс.
//	3. Дочерний процесс должен читать строки из pipes и выводить их на экран.
//	Рекомендации: используйте цикл для чтения и записи.
// !!!Используется несколько строк, поэтому приходится реализовывать цикл для передачи.

int main() {
	const char* pipeName = R"(\\.\pipe\my_named_pipe)";
	HANDLE hPipe;

	// Создание именованного канала
	hPipe = CreateNamedPipeA(
		pipeName,
		PIPE_ACCESS_OUTBOUND, // Доступ для записи
		PIPE_TYPE_MESSAGE | PIPE_WAIT,
		1, // Максимальное количество экземпляров
		512, // Размер выходного буфера
		512, // Размер входного буфера
		0, // Время ожидания
		nullptr // Дескриптор безопасности
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		cerr << "Failed to create named pipe." << endl;
		return 1;
	}

	cout << "Named pipe created. Waiting for a client to connect..." << endl;

	// Ожидание подключения клиента
	if (ConnectNamedPipe(hPipe, nullptr) != FALSE) {
		cout << "Client connected. Enter 5 messages to send:" << endl;

		for (int i = 0; i < 5; ++i) { // Отправляем 5 строк
			string message;
			cout << "Message " << i + 1 << ": ";
			getline(cin, message);

			DWORD bytesWritten;
			if (!WriteFile(hPipe, message.c_str(), message.size(), &bytesWritten, nullptr)) {
				cerr << "Failed to write to pipe." << endl;
				break;
			}
		}

		cout << "All messages sent." << endl;
	}
	else {
		cerr << "Failed to connect to the client." << endl;
	}

	CloseHandle(hPipe);
	return 0;
}
