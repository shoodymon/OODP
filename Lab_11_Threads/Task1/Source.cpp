#include <iostream>
#include <thread>
#include <vector>


/*
1. ����� ������� �������������� ������� ��������������� (��������� �����, �������� ���������� (deadlock))?

2. ���������� � ������ ����������� ����������� ���������� C++, ��������� � ����������������,
	����� ��� std::future � std::promise,
	������� ��������� ����������� ����������������
*/


/*
������� - ��� ����������� � ����������� ������ ��������� ����������.

� C++ ����� (thread) � ��� ������� ����������, ������� ����� �������� ����������� � ������� �������� � ������ ����� ���������.
*/


std::vector<int> multFn(const std::vector<int>& cref_vec, int k)
{
	std::vector<int> result_vec;
	for (int i = 0; i < cref_vec.size(); i++)
	{
		result_vec.emplace_back(cref_vec[i] * k);
	}

	for (int i = 0; i < result_vec.size(); i++)
	{
		std::cout << "result_vec[" << i << "] = " << result_vec[i] << std::endl;
	}

	return result_vec;
}


int main()
{
	std::vector<int> vec = { 1,2,3,4,5 };

	std::thread thread_1(multFn, vec, 10);

	thread_1.join();

	return 0;
}