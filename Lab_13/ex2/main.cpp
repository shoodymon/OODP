/*

������� 2.

����������� ���������� ������ �� �������� �����.
� ������ ���������� � ����� ������� ��������� � �������. 
� ���������� ������� ����� ��������� ����� ��� �������� ������� � id ������, ������������ �����. 
��������� ����������� ���������� �������.

*/



#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void threadTask(int id) {
    std::cout << "Thread " << id << " started. ID: " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    std::cout << "Thread " << id << " resumed. ID: " << std::this_thread::get_id() << "\n";
}

int main() {
    const int numThreads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadTask, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}