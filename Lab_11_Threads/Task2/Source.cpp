#include <iostream>
#include <thread>
#include <vector>


void printFn(int iteration)
{
	std::cout << "Iteration: " << iteration << std::endl;
	std::cout << "Current thread ID: " << std::this_thread::get_id() << std::endl;
}


int main()
{
	const int THREADS_COUNT = 5;

	std::vector<std::thread> vec_threads;
	for (int i = 0; i < THREADS_COUNT; i++)
	{
		vec_threads.emplace_back(printFn, i);
	}

	for (auto& thread : vec_threads)
	{
		thread.join();
	}

	return 0;
}
