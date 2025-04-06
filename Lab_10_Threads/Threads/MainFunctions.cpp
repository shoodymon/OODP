#include "MainFunctions.hpp"
#include "TaskFunctions.hpp"

void performFirstTask() {
    std::vector<int> vec1 = { -1, 2, 3, -4, 5 };
    std::thread thread1(multiplyVectorElements, std::ref(vec1));
    thread1.join();
}

void performSecondTask() {
    const int NUM_THREADS = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(printIteratorAndThreadId, i);
    }

    for (auto& t : threads) {
        t.join();
    }
}

void performThirdTask() {
    std::vector<int> vec2 = { 1, 2, 3, 4 };
    std::vector<int> vec3 = { 5, 6, 7, 8 };
    std::atomic<int> scalar_result(0);

    std::vector<std::thread> computation_threads;
    int interval_size = vec2.size() / 2;

    computation_threads.emplace_back(multiplyVectorIntervals,
        std::ref(vec2), std::ref(vec3), 0, interval_size, std::ref(scalar_result));
    computation_threads.emplace_back(multiplyVectorIntervals,
        std::ref(vec2), std::ref(vec3), interval_size, vec2.size(), std::ref(scalar_result));

    for (auto& t : computation_threads) {
        t.join();
    }

    std::cout << "Задание 3: Скалярное произведение = " << scalar_result << std::endl;
}
