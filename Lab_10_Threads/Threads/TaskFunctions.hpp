#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <numeric>
#include <algorithm>

void multiplyVectorElements(const std::vector<int>& vec);
void printIteratorAndThreadId(int iterator);
void multiplyVectorIntervals(const std::vector<int>& vec1, const std::vector<int>& vec2,
    int start, int end, std::atomic<int>& result);
