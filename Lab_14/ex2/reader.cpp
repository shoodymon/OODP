#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
	const char* pipeName = R"(\\.\pipe\my_named_pipe)";
	HANDLE hPipe;
	char buffer[512];
	DWORD bytesRead;

	// ����������� � ������������ ������
	hPipe = CreateFileA(
		pipeName,
		GENERIC_READ, // ������ ��� ������
		0, // �������� ����������� �������
		nullptr, // ���������� ������������
		OPEN_EXISTING, // ����������� � ������������� ������
		0, // �����
		nullptr // ������
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		cerr << "Failed to connect to the named pipe." << endl;
		return 1;
	}

	cout << "Connected to the named pipe. Reading messages..." << endl;

	while (true) {
		if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
			buffer[bytesRead] = '\0'; // ��������� ������
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
