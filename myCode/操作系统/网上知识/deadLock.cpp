#include <iostream>
#include <utility>
#include <chrono>
#include <mutex>
#include <thread>
#include <assert.h>
#include <string>

using std::thread;

std::mutex m1;
std::mutex m2;

void deadLock(std::mutex &mtA, std::mutex &mtB)
{

    std::lock_guard<std::mutex> lock1(mtA);
    std::cout << " get the first mutex in thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::lock_guard<std::mutex> lock2(mtB);
    std::cout << " get the second mutex in thread " << std::this_thread::get_id() << std::endl;
    std::cout << " do something in thread " << std::this_thread::get_id() << std::endl;
}

void deadLockProcess1(std::mutex &mtA, std::mutex &mtB)
{

    std::lock(mtA, mtB);

    std::lock_guard<std::mutex> lock1(mtA, std::adopt_lock);
    std::cout << " get the first mutex in thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::lock_guard<std::mutex> lock2(mtB, std::adopt_lock);
    std::cout << " get the second mutex in thread " << std::this_thread::get_id() << std::endl;
    std::cout << " do something in thread " << std::this_thread::get_id() << std::endl;
}

void deadLockProcess2(std::mutex &mtA, std::mutex &mtB)
{

    std::unique_lock<std::mutex> lock1(mtA, std::defer_lock);
    std::cout << " get the first mutex in thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::unique_lock<std::mutex> lock2(mtB, std::defer_lock);
    std::cout << " get the second mutex in thread " << std::this_thread::get_id() << std::endl;

    std::lock(lock1, lock2);

    assert(lock1.owns_lock() == true);

    std::cout << " do something in thread " << std::this_thread::get_id() << std::endl;
}

int main()
{
#if 1
    thread t1([&] { deadLock(m1, m2); });
    thread t2([&] { deadLock(m2, m1); });
    for (int i = 0; i < 100; i++)
    {
        std::cout << "what" << std::endl;
    }
    t1.join();
    t2.join();
#endif
    // 最多可使用线程数  hardware_concurrency()
    std::cout << std::thread::hardware_concurrency() << std::endl;
}