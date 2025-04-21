#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <future>

// ������������ ���������� ��������� transform
template<typename InputIt, typename OutputIt, typename UnaryOp>
void parallel_transform(InputIt first, InputIt last, OutputIt d_first, UnaryOp op) {
    // ����������� ���������� ��������� ���������� �������
    const auto num_threads = std::thread::hardware_concurrency();
    // ���� � ��� ������ 1 ����� ��� ����� ��������� ��������, ���������� ���������������� ���������
    auto dist = std::distance(first, last);
    if (num_threads <= 1 || dist < 1000) {
        std::transform(first, last, d_first, op);
        return;
    }

    // ���������� ������ ����� ��� ������� ������
    const auto block_size = dist / num_threads;

    // ������ ��� �������� �������
    std::vector<std::future<void>> futures;
    futures.reserve(num_threads);

    // �������� � ������ �������
    for (unsigned int i = 0; i < num_threads - 1; ++i) {
        auto block_start = first;
        std::advance(block_start, i * block_size);

        auto block_end = block_start;
        std::advance(block_end, block_size);

        auto output_start = d_first;
        std::advance(output_start, i * block_size);

        // ��������� ������ ����������
        futures.push_back(
            std::async(std::launch::async,
                [=]() {
                    std::transform(block_start, block_end, output_start, op);
                }
            )
        );
    }

    // ��������� ���� ������������ ��������, ����� ������ ������� ���������
    auto last_block_start = first;
    std::advance(last_block_start, (num_threads - 1) * block_size);

    auto last_output_start = d_first;
    std::advance(last_output_start, (num_threads - 1) * block_size);

    // ��������� ���� ������������ � �������� ������
    std::transform(last_block_start, last, last_output_start, op);

    // ���� ���������� ���� �������
    for (auto& future : futures) {
        future.wait();
    }
}

// ������� ��� ������������
int main() {
    setlocale(0, "");
    // �������� ������
    std::vector<int> source(10000);
    for (int i = 0; i < 10000; ++i) {
        source[i] = i;
    }

    // ������ ��� �����������
    std::vector<int> result(source.size());

    // ���������� �������� ���������� � �������
    auto square = [](int x) { return x * x; };

    // ��������� ������������ transform
    parallel_transform(source.begin(), source.end(), result.begin(), square);

    // �������� �����������
    std::cout << "�������� ������ 10 ��������� ����������:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << source[i] << " � �������� = " << result[i] << std::endl;
    }

    std::cout << "�������� ��������� 10 ��������� ����������:" << std::endl;
    for (int i = source.size() - 10; i < source.size(); ++i) {
        std::cout << source[i] << " � �������� = " << result[i] << std::endl;
    }

    return 0;
}