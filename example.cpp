#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.hpp"

int main()
{
    ThreadPool pool(4);
    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.push_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    pool.wait();
    std::cout << "Done waiting for all threads to finish every queued task." << std::endl;

    for (size_t i = 0; i < results.size(); ++i)
        std::cout << results[i].get() << ' ';
    std::cout << std::endl;

    return 0;
}
