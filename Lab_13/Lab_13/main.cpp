/*

Задание 1.
Реализовать цикл создания потоков.
В потоки передать номер итератора цикла.
В начале выполнения потока и при завершении вывести сообщение в консоль.

*/


#include <iostream>
#include <thread>
#include <vector>

void threadTask(int id) 
{
    std::cout << "Thread " << id << " started.\n";
    std::cout << "Thread " << id << " finished.\n";
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
