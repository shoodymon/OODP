// main.cpp
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>


//	��������������� ������������� ���������� ���������.
//	����������� ���������, ������� ���������� ��������� �������� ��������� ��� ��������� ������.
//	1. �������� ���������, � ������� ������������ ������� ����� ������������ ��������� �������� ���������(��������, 3).
//	2. ������������ ������� ���������� ������ � ������ �������� �������, ������� ������������ ������(������ ��������� ���������� ��������������) � ���������� ��������� ����������, � ��� �����.
//	3. ��������� ������� ���������� ��������� ������� ��������, ������� ������� ��� �� �����.
//	������������: ����������� ��� pipes : ���� ��� �������� ������ �� �������� � �������� ��������� � ���� ��� �������� ����������� �������.


void ErrorExit(const char* msg) {
	std::cerr << msg << " ������: " << GetLastError() << std::endl;
	ExitProcess(1);
}

void childProcess(int readHandle, int writeHandle) {
	HANDLE hRead = (HANDLE)readHandle;
	HANDLE hWrite = (HANDLE)writeHandle;

	char buffer[256];
	DWORD bytesRead, bytesWritten;

	if (!ReadFile(hRead, buffer, sizeof(buffer), &bytesRead, NULL)) {
		ErrorExit("������ ������ � �������� ��������");
	}

	buffer[bytesRead] = '\0';
	std::string data(buffer);

	data += " -> ����������";

	if (!WriteFile(hWrite, data.c_str(), data.length(), &bytesWritten, NULL)) {
		ErrorExit("������ ������ � �������� ��������");
	}

	CloseHandle(hRead);
	CloseHandle(hWrite);

	ExitProcess(0);
}

int main(int argc, char* argv[]) {
	setlocale(0, "");

	if (argc >= 2 && std::string(argv[1]) == "child") {
		childProcess(
			(int)(intptr_t)GetStdHandle(STD_INPUT_HANDLE),
			(int)(intptr_t)GetStdHandle(STD_OUTPUT_HANDLE)
		);
		return 0;
	}

	// === ������������ ������� ===

	HANDLE pipes1[2];
	HANDLE pipes2[2];
	HANDLE pipes3[2];
	HANDLE pipesBack[2];

	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

	if (!CreatePipe(&pipes1[0], &pipes1[1], &sa, 0)) ErrorExit("CreatePipe 1");
	if (!CreatePipe(&pipes2[0], &pipes2[1], &sa, 0)) ErrorExit("CreatePipe 2");
	if (!CreatePipe(&pipes3[0], &pipes3[1], &sa, 0)) ErrorExit("CreatePipe 3");
	if (!CreatePipe(&pipesBack[0], &pipesBack[1], &sa, 0)) ErrorExit("CreatePipe Back");

	CHAR modulePath[MAX_PATH];
	GetModuleFileNameA(NULL, modulePath, MAX_PATH);

	// ������ 3 ���������
	for (int i = 0; i < 3; ++i) {
		STARTUPINFOA si = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		si.cb = sizeof(si);

		HANDLE hStdInput, hStdOutput;

		if (i == 0) {
			hStdInput = pipes1[0];
			hStdOutput = pipes2[1];
		}
		else if (i == 1) {
			hStdInput = pipes2[0];
			hStdOutput = pipes3[1];
		}
		else {
			hStdInput = pipes3[0];
			hStdOutput = pipesBack[1];
		}

		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdInput = hStdInput;
		si.hStdOutput = hStdOutput;
		si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

		char cmdLine[512];
		strcpy_s(cmdLine, modulePath);
		strcat_s(cmdLine, " child");

		if (!CreateProcessA(
			NULL,
			cmdLine,
			NULL,
			NULL,
			TRUE,
			0,
			NULL,
			NULL,
			&si,
			&pi))
		{
			ErrorExit("������ ������� ��������� ��������");
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}


	// ����� ������� ��������� �������� ����� ������� ������ ������� ������:

	CloseHandle(pipes1[0]); // input ��������� �������� 1
	CloseHandle(pipes2[0]); // input ��������� �������� 2
	CloseHandle(pipes3[0]); // input ��������� �������� 3
	CloseHandle(pipes2[1]); // output ��������� �������� 1
	CloseHandle(pipes3[1]); // output ��������� �������� 2
	CloseHandle(pipesBack[1]); // output ��������� �������� 3

	// ���������� ��������� ������
	std::string input = "��������� ������";
	DWORD bytesWritten;
	if (!WriteFile(pipes1[1], input.c_str(), input.length(), &bytesWritten, NULL)) {
		ErrorExit("������ ������ ��������� ������");
	}
	CloseHandle(pipes1[1]); // ��������� ���� ������� ������

	// �������� �������� ������
	char buffer[256];
	DWORD bytesRead;
	if (!ReadFile(pipesBack[0], buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
		ErrorExit("������ ������ ����������");
	}
	buffer[bytesRead] = '\0';

	std::cout << "��������� ���������: " << buffer << std::endl;

	CloseHandle(pipesBack[0]);

	return 0;
}
