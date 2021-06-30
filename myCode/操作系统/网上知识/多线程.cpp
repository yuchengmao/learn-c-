#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

void f1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread " << n << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void *f2(void *n)
{
    pthread_detach(pthread_self());
    std::mutex m1;
    std::lock_guard<std::mutex> locker(m1);
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread " << n << " executing\n"
                  << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    pthread_exit(NULL);
}

int main()
{

    int n = 0;
    pthread_t threads[5] = {0};

    int ret = 0;
    int indexes[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        std::cout << " main " << i << std::endl;
        ret = pthread_create(&threads[i], NULL, f2, (void *)&(indexes[i]));

        if (ret)
        {
            std::cout << "error" << ret << std::endl;
            exit(-1);
        }
    }
}
