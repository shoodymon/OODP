#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <future>

template <typename RandomAccessIterator, typename F>
void parallelTransform(RandomAccessIterator begin, RandomAccessIterator end, F&& func) {
    auto size = std::distance(begin, end);

    if (size <= 10000) {
        std::transform(begin, end, begin, std::forward<F>(func)); // - единичная функция для диапазона
    }
    else {
        int thread_count = 5;
        std::vector<std::thread> threads;
        auto block_size = size / thread_count;

        for (int i = 0; i < thread_count; ++i)
        {
            auto block_begin = begin + i * block_size;
            auto block_end = (i == thread_count - 1) ? end : block_begin + block_size;

            threads.emplace_back([block_begin, block_end, i, &func]() {
                std::cout << "Поток " << i + 1 << " [" << std::distance(block_begin, block_end) << "] начал работу\n";
                std::transform(block_begin, block_end, block_begin, std::forward<F>(func));
                std::cout << "Поток " << i + 1 << " завершил работу\n";
                });
        }

        for (auto& t : threads) {
            t.join();
        }
    }
}

int square(int x) {
    return x * x;
}

int main()
{
    setlocale(0, "");

    std::vector<int> temp(20000);
    for (size_t i = 0; i < temp.size(); i++)
    {
        temp.at(i) = i + 1;
    }

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << temp.at(i) << " ";
    }
    std::cout << std::endl;

    parallelTransform(temp.begin(), temp.end(), square);

    std::cout << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << temp.at(i) << " ";
    }
}
