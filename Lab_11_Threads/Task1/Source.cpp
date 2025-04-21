#include <iostream>
#include <thread>
#include <vector>


/*
������� - ��� ����������� � ����������� ������ ��������� ����������.

� C++ ����� (thread) � ��� ������� ����������, ������� ����� �������� ����������� � ������� �������� � ������ ����� ���������.
*/


void calculateNegativeSum(const std::vector<int>& vec) {
    int sum = 0;
    for (int element : vec) {
        if (element < 0) {
            sum += element;
        }
    }
    std::cout << "Total sum = " << sum << std::endl;
}

int main() {
    std::vector<int> A = { -1, 2, 3, -4, 5 };

    std::thread calculation_thread(calculateNegativeSum, std::ref(A));

    calculation_thread.join();

    return 0;
}