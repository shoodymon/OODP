#include <windows.h>
#include <iostream>
#include <string>
using namespace std;


//	������� 1.
//	����������� �������������� ����� ����� ���������� � ������� ������������ ������.
//	1. �������� ���������, ������� ������� ����������� �����.
//	2. ���� �������(��������) ����� ������ ������ �� ������, � ������
//	�������(��������) ����� ���������� ������ � ����.
//	3. �������� ������ ���������� ������, � �������� �������� � �� �����.

int main()
{
	const char* pipeName = R"(\\.\pipe\my_named_pipe)";
	HANDLE hPipe;

	// �������� ������������ ������
	hPipe = CreateNamedPipeA(
		pipeName,
		PIPE_ACCESS_OUTBOUND, // ������ ��� ������
		PIPE_TYPE_BYTE | PIPE_WAIT,
		1, // ������������ ���������� �����������
		512, // ������ ��������� ������
		512, // ������ �������� ������
		0, // ����� ��������
		nullptr // ���������� ������������
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		cerr << "Failed to create named pipe." << endl;
		return 1;
	}

	cout << "Named pipe created. Waiting for a client to connect..." << endl;

	// �������� �������
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
