#include <stack>
#include <mutex>
#include <optional>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

template <typename T>
class ThreadSafeStack {
public:
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        stack.push(value);
        lock.unlock();
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mtx);
        if (stack.empty()) {
            lock.unlock();
            return std::nullopt;
        }
        T value = stack.top();
        stack.pop();
        lock.unlock();
        return value;
    }

    std::optional<T> top() {
        std::unique_lock<std::mutex> lock(mtx);
        if (stack.empty()) {
            lock.unlock();
            return std::nullopt;
        }
        T value = stack.top();
        lock.unlock();
        return value;
    }

    bool empty() {
        std::unique_lock<std::mutex> lock(mtx);
        bool is_empty = stack.empty();
        lock.unlock();
        return is_empty;
    }

    size_t size() {
        std::unique_lock<std::mutex> lock(mtx);
        size_t stack_size = stack.size();
        lock.unlock();
        return stack_size;
    }

private:
    std::stack<T> stack;
    std::mutex mtx;
};


int main() {
    ThreadSafeStack<int> stack;

    // Launch threads to push elements onto the stack
    std::vector<std::thread> push_threads;
    for (size_t i = 0; i < 10; ++i) {
        push_threads.emplace_back([&stack]() {
            for (size_t j = 0; j < 10; ++j) {
                stack.push(j);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    }

    // Join the threads
    for (auto& t : push_threads) {
        t.join();
    }

    // Launch threads to pop elements from the stack
    std::vector<std::thread> pop_threads;
    for (size_t i = 0; i < 10; ++i) {
        pop_threads.emplace_back([&stack]() {
            while (!stack.empty()) {
                auto value = stack.pop();
                if (value) {
                    std::cout << "Popped value: " << *value << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
    }

    // Join the pop threads
    for (auto& t : pop_threads) {
        t.join();
    }

    return 0;
}