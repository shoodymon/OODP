#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <future>

// Параллельная реализация алгоритма transform
template<typename InputIt, typename OutputIt, typename UnaryOp>
void parallel_transform(InputIt first, InputIt last, OutputIt d_first, UnaryOp op) {
    // Определение количества доступных аппаратных потоков
    const auto num_threads = std::thread::hardware_concurrency();
    // Если у нас только 1 поток или очень маленький диапазон, используем последовательную обработку
    auto dist = std::distance(first, last);
    if (num_threads <= 1 || dist < 1000) {
        std::transform(first, last, d_first, op);
        return;
    }

    // Определяем размер блока для каждого потока
    const auto block_size = dist / num_threads;

    // Вектор для хранения потоков
    std::vector<std::future<void>> futures;
    futures.reserve(num_threads);

    // Создание и запуск потоков
    for (unsigned int i = 0; i < num_threads - 1; ++i) {
        auto block_start = first;
        std::advance(block_start, i * block_size);

        auto block_end = block_start;
        std::advance(block_end, block_size);

        auto output_start = d_first;
        std::advance(output_start, i * block_size);

        // Запускаем задачу асинхронно
        futures.push_back(
            std::async(std::launch::async,
                [=]() {
                    std::transform(block_start, block_end, output_start, op);
                }
            )
        );
    }

    // Последний блок обрабатываем отдельно, чтобы учесть остаток элементов
    auto last_block_start = first;
    std::advance(last_block_start, (num_threads - 1) * block_size);

    auto last_output_start = d_first;
    std::advance(last_output_start, (num_threads - 1) * block_size);

    // Последний блок обрабатываем в основном потоке
    std::transform(last_block_start, last, last_output_start, op);

    // Ждем завершения всех потоков
    for (auto& future : futures) {
        future.wait();
    }
}

// Функция для тестирования
int main() {
    setlocale(0, "");
    // Исходный вектор
    std::vector<int> source(10000);
    for (int i = 0; i < 10000; ++i) {
        source[i] = i;
    }

    // Вектор для результатов
    std::vector<int> result(source.size());

    // Определяем операцию возведения в квадрат
    auto square = [](int x) { return x * x; };

    // Применяем параллельный transform
    parallel_transform(source.begin(), source.end(), result.begin(), square);

    // Проверка результатов
    std::cout << "Проверка первых 10 элементов результата:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << source[i] << " в квадрате = " << result[i] << std::endl;
    }

    std::cout << "Проверка последних 10 элементов результата:" << std::endl;
    for (int i = source.size() - 10; i < source.size(); ++i) {
        std::cout << source[i] << " в квадрате = " << result[i] << std::endl;
    }

    return 0;
}