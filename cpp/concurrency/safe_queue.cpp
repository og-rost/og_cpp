#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class Queue {
private:
    std::queue<int> q;
    std::mutex mu;
    std::condition_variable cv;

public:
    void enqueue(int val) {
        std::unique_lock lock(mu);
        q.push(val);
        cv.notify_one();
    }

    int dequeue() {
        std::unique_lock lock(mu);
        /*
        
        When the wait function is called with a predicate, it releases the lock and starts waiting.
        During this waiting period, other threads can acquire the lock and make changes to the shared resource
        (e.g., enqueue elements to the queue).
        When the predicate becomes true (in this case, when the queue is no longer empty),
        the wait function internally reacquires the lock before returning.
        This ensures that the subsequent front() and pop() operations on the queue are performed with the necessary synchronization,
        preventing potential data races and ensuring the correct operation of the program.
        So, the wait function provides a convenient way to block a thread's execution until a certain condition is met,
        while also handling the lock release and reacquisition automatically to ensure proper synchronization between threads.
        
        */
        cv.wait(lock, [this]() { return !q.empty(); });
        int tmp = q.front();
        q.pop();
        return tmp;
    }
};

void enqueue_elements(Queue &q, int start, int end) {
    for (int i = start; i < end; ++i) {
        q.enqueue(i);
    }
}

void dequeue_elements(Queue &q, int count) {
    for (int i = 0; i < count; ++i) {
        int value = q.dequeue();
        std::cout << "Dequeued: " << value << std::endl;
    }
}

int main() {
    Queue q;

    // Create producer threads
    std::thread producer1(enqueue_elements, std::ref(q), 0, 50);
    std::thread producer2(enqueue_elements, std::ref(q), 50, 100);

    // Create consumer threads
    std::thread consumer1(dequeue_elements, std::ref(q), 50);
    std::thread consumer2(dequeue_elements, std::ref(q), 50);

    // Wait for threads to finish
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}
