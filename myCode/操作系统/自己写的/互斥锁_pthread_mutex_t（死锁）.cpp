#include <iostream>
#include <pthread.h>
#include <thread>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutexlock;
pthread_mutex_t mutexlock1 = PTHREAD_MUTEX_INITIALIZER;
/**
 * @brief 没有解锁
 * 
 */
void *test01(void *arg)
{
    for (size_t i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutexlock);
        cout << "test01" << endl;
        //没有解锁
        //pthread_mutex_unlock(&mutexlock);
    }
    return nullptr;
}

/**
 * @brief 重复加锁导致死锁
 * 
 */
void *test02(void *arg)
{
    for (size_t i = 0; i < 10; i++)
    {
        //重复加锁,直接没有输出
        pthread_mutex_lock(&mutexlock);
        pthread_mutex_lock(&mutexlock);

        cout << "test02" << endl;
        pthread_mutex_unlock(&mutexlock);
    }
    return nullptr;
}

/**
 * @brief 两个共享资源被两个线程加锁，导致互相拿不到另一个资源
 * 
 * @param arg 
 * @return void* 
 */
void *test03(void *arg)
{
    for (size_t i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&mutexlock);
        usleep(1);
        pthread_mutex_lock(&mutexlock1);
        cout << "test03: " << i << endl;
        pthread_mutex_unlock(&mutexlock1);
        pthread_mutex_unlock(&mutexlock);
    }
    return nullptr;
}
void *test03_1(void *arg)
{
    for (size_t i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&mutexlock1);
        usleep(1);
        pthread_mutex_lock(&mutexlock);
        cout << "test03_1: " << i << endl;
        pthread_mutex_unlock(&mutexlock);
        pthread_mutex_unlock(&mutexlock1);
    }
    return nullptr;
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutexlock, nullptr);
    pthread_t tid;
    pthread_t tid1;
    pthread_create(&tid, nullptr, test03, nullptr);
    pthread_create(&tid1, nullptr, test03_1, nullptr);
    sleep(10);
    return 0;
}
