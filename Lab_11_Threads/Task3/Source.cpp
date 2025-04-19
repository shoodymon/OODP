#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


static int scalar_var = 0;


void someFn(const std::vector<int>& vec1, const std::vector<int>& vec2, int start, int end)
{
	int mult_vec1 = 1;
	int mult_vec2 = 1;

	for (int i = start; i <= end; i++)
	{
		mult_vec1 *= vec1[i];
		mult_vec2 *= vec2[i];
	}

	scalar_var += (mult_vec1 + mult_vec2);
}


int main()
{
	std::vector<int> vec1 = { 1,2,3,4 };
	std::vector<int> vec2 = { 5,6,7,8 };
	std::vector<std::pair<int, int>> intervals;
	std::vector<std::thread> threads;

	for (int i = 0; i < vec1.size() - 1; i++)
	{
		intervals.emplace_back(std::make_pair(i, i + 1));
	}

	//checking intervals
	for (const auto& interval : intervals)
	{
		std::cout << interval.first << ", " << interval.second << std::endl;
	}

	for (const auto& interval : intervals)
	{
		threads.emplace_back(someFn, vec1, vec2, interval.first, interval.second);
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	std::cout << "Total sum: " << scalar_var << std::endl;


	return 0;
}