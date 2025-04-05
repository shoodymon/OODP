#include "MainFunctions.hpp"
#include "TaskFunctions.hpp"

std::mutex console_mutex;

void multiplyVectorElements(const std::vector<int>& vec) {
    int result = 1;
    for (int num : vec) {
        result *= num;
    }

    std::lock_guard<std::mutex> lock(console_mutex);
    std::cout << "Задание 1: Результат умножения элементов вектора = " << result << std::endl;
}

void printIteratorAndThreadId(int iterator) {
    std::lock_guard<std::mutex> lock(console_mutex);
    std::cout << "Задание 2: Итератор = " << iterator
        << ", ID потока = " << std::this_thread::get_id() << std::endl;
}

void multiplyVectorIntervals(const std::vector<int>& vec1, const std::vector<int>& vec2,
    int start, int end, std::atomic<int>& result) {
    int local_result = 0;
    for (int i = start; i < end; ++i) {
        local_result += vec1[i] * vec2[i];
    }

    result.fetch_add(local_result);
}
