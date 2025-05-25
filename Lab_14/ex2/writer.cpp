#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

//	������� 2.
//	Pipes ��� �������� ���������� �����.
//	����������� �������� ���������� ����� �� ������������� �������� � ��������� ����� pipes.
//	1. ����������� ��� �� ������, ��� � � ������ �������, �� ����������� ��������� �����(��������, 5 �����).
//	2. ������������ ������� ������ ��������� ���� �� ������������ � ���������� ������ � �������� �������.
//	3. �������� ������� ������ ������ ������ �� pipes � �������� �� �� �����.
//	������������: ����������� ���� ��� ������ � ������.
// !!!������������ ��������� �����, ������� ���������� ������������� ���� ��� ��������.

int main() {
	const char* pipeName = R"(\\.\pipe\my_named_pipe)";
	HANDLE hPipe;

	// �������� ������������ ������
	hPipe = CreateNamedPipeA(
		pipeName,
		PIPE_ACCESS_OUTBOUND, // ������ ��� ������
		PIPE_TYPE_MESSAGE | PIPE_WAIT,
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

	// �������� ����������� �������
	if (ConnectNamedPipe(hPipe, nullptr) != FALSE) {
		cout << "Client connected. Enter 5 messages to send:" << endl;

		for (int i = 0; i < 5; ++i) { // ���������� 5 �����
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
