#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <numeric>

void accumulate_block_worker(int* data, size_t count, int* result) {
    *result = std::accumulate(data, data + count, 0);
}

int accumulate_block_worker_ret(int* data, size_t count) {
    return std::accumulate(data, data + count, 0);
}

std::vector<std::thread> launch_split_workers_with_std_thread(std::vector<int>& v,
                                                              std::vector<int>* results) {
    std::vector<std::thread> threads;
    threads.emplace_back(accumulate_block_worker, v.data(), v.size() / 2, &((*results)[0]));
    threads.emplace_back(accumulate_block_worker, v.data() + v.size() / 2, v.size() / 2, &((*results)[1]));
    return threads;
}

void testThread() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> results(2, 0);
    std::vector<std::thread> threads = launch_split_workers_with_std_thread(v, &results);
    for (auto& t : threads) {
        t.join();
    }
    std::cout << "results from launch_split_workers_with_std_thread: "
              << results[0] << " and " << results[1] << std::endl;
}

std::vector<std::future<int>> launch_split_workers_with_std_async(std::vector<int>& v) {
    std::vector<std::future<int>> futures;
    futures.push_back(std::async(std::launch::async, accumulate_block_worker_ret, v.data(), v.size() / 2));
    futures.push_back(std::async(std::launch::async, accumulate_block_worker_ret, v.data() + v.size() / 2, v.size() / 2));
    return futures;
}

void testAsync() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<std::future<int>> futures = launch_split_workers_with_std_async(v);
    std::cout << "results from launch_split_workers_with_std_async: "
              << futures[0].get() << " and " << futures[1].get() << std::endl;

    // we can wait for the future for a specific period of time
    /*while (futures[0].wait_for(std::chrono::seconds(1)) != std::future_status::ready) {
        std::cout << "... still not ready" << std::endl;
    }
    std::cout << "result " << futures[0].get() << std::endl;*/
}

/*

The default launch policy of std::async is broken. Scott Meyers, in his "Effective Modern C++", recommends
the following wrapper to launch tasks:

template <typename F, typename... Ts>
inline auto reallyAsync(F&& f, Ts&&... params) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}

*/

int main() {
    testThread();
    testAsync();
    return 0;
}