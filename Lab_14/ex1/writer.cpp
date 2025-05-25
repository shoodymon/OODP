#include <windows.h>
#include <iostream>
#include <string>
using namespace std;


//	Задание 1.
//	Реализовать взаимодействие между двумя процессами с помощью именованного канала.
//	1. Создайте программу, которая создает именованный канал.
//	2. Один процесс(читатель) будет читать данные из канала, а другой
//	процесс(писатель) будет записывать данные в него.
//	3. Писатель должен передавать строку, а читатель выводить её на экран.

int main()
{
	const char* pipeName = R"(\\.\pipe\my_named_pipe)";
	HANDLE hPipe;

	// Создание именованного канала
	hPipe = CreateNamedPipeA(
		pipeName,
		PIPE_ACCESS_OUTBOUND, // Доступ для записи
		PIPE_TYPE_BYTE | PIPE_WAIT,
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

	// Ожидание клиента
	if (ConnectNamedPipe(hPipe, nullptr) != FALSE) {
		string message;
		cout << "Client connected. Enter messages to send (type 'exit' to quit):" << endl;
		while (true) {
			getline(cin, message);
			if (message == "exit") {
				break;
			}
			DWORD bytesWritten;
			WriteFile(hPipe, message.c_str(), message.size(), &bytesWritten, nullptr);
		}
	}

	CloseHandle(hPipe);
	return 0;
}
