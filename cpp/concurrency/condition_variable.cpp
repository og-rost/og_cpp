/*

Defined in header <condition_variable>
class condition_variable; (since C++11)


The condition_variable class is a synchronization primitive used with a std::mutex to block one or more threads until another
thread both modifies a shared variable (the condition) and notifies the condition_variable.

The thread that intends to modify the shared variable must:

1) Acquire a std::mutex (typically via std::lock_guard)
2) Modify the shared variable while the lock is owned
3) Call notify_one or notify_all on the std::condition_variable (can be done after releasing the lock)

Even if the shared variable is atomic, it must be modified while owning the mutex to correctly publish the modification
to the waiting thread.

Any thread that intends to wait on a std::condition_variable must:

1) Acquire a std::unique_lock<std::mutex> on the mutex used to protect the shared variable
2) Do one of the following:
    a) Check the condition, in case it was already updated and notified
    b) Call wait, wait_for, or wait_until on the std::condition_variable
    (atomically releases the mutex and suspends thread execution until the condition variable is notified,
    a timeout expires, or a spurious wakeup occurs, then atomically acquires the mutex before returning)
3) Check the condition and resume waiting if not satisfied
    or:
    Use the predicated overload of wait, wait_for, and wait_until, which performs the same three steps


std::condition_variable works only with std::unique_lock<std::mutex>, which allows for maximal efficiency on some platforms.
std::condition_variable_any provides a condition variable that works with any BasicLockable object, such as std::shared_lock.

Condition variables permit concurrent invocation of the wait, wait_for, wait_until, notify_one and notify_all member functions.

The class std::condition_variable is a StandardLayoutType. It is not CopyConstructible, MoveConstructible, CopyAssignable,
or MoveAssignable.
*/


#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread() {
    // Wait until main() sends data
    std::unique_lock lk(m);
    cv.wait(lk, []{return ready;});
 
    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}
 
int main() {
    std::thread worker(worker_thread);
 
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock lk(m);
        cv.wait(lk, []{return processed;}); // atomicly drops the lock and goes to sleep
                                            // it re-aquires the lock when wakes up
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}
