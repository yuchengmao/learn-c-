#include <iostream>
#include <thread>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#define THREAD_NUM 10

#if 0
/**
 * @brief 互斥锁 mutex
 * 
 */
mutex m1;
void *thread_proc(void *arg)
{
    lock_guard<mutex> locker(m1);
    int *pcount = (int *)arg;
    int i = 0;
    while (i++ < 100000)
    {
        (*pcount)++;
        //usleep(1);
    }
    return 0;
}

int main()
{
    int i = 0;
    pthread_t __thread_id[THREAD_NUM] = {0};
    int count = 0;

    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&__thread_id[i], NULL, thread_proc, &count);
    }

    for (i = 0; i < 200; i++)
    {
        //cout << "i = " << i << endl;
        cout << "count = " << count << endl;
        usleep(10);
    }

    return 0;
}
#endif

#if 0
/**
 * @brief 自旋锁 
 * 
 */
pthread_spinlock_t spinlock;

void *thread_proc(void *arg)
{
    lock_guard<mutex> locker(spinlock);
    int *pcount = (int *)arg;
    int i = 0;
    while (i++ < 100000)
    {
        (*pcount)++;
        usleep(1);
    }
    return 0;
}

int main()
{
    int i = 0;
    pthread_t __thread_id[THREAD_NUM] = {0};
    int count = 0;

    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&__thread_id[i], NULL, thread_proc, &count);
    }

    for (i = 0; i < 200; i++)
    {
        //cout << "i = " << i << endl;
        cout << "count = " << count << endl;
        usleep(10);
    }

    return 0;
}
#endif

#if 1
/**
 * @brief 互斥锁
 * 
 */
pthread_mutex_t mutexlock;
int pcount = 0;
void *thread_proc(void *arg)
{
    //int *pcount = (int *)arg;
    int i = 0;
    while (i++ < 10)
    {
        pthread_mutex_lock(&mutexlock);
        pcount++;
        cout << "pthread_self = "
             << pthread_self() << ", "
             << "pcount = "
             << pcount << endl;
        //pthread_mutex_unlock(&mutexlock);
    }
    //pthread_exit(&pcount);
    return 0;
}
int main()
{
    int i = 0;
    pthread_t __thread_id[THREAD_NUM] = {0};

    pthread_mutex_init(&mutexlock, nullptr);

    for (i = 0; i < THREAD_NUM; i++)
    {
        //cout << "i = " << i << endl;
        pthread_create(&__thread_id[i], NULL, thread_proc, &pcount);
    }
    for (size_t i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(__thread_id[i], nullptr);
        cout << "pcount_mian = " << pcount << endl;
    }
    sleep(1);
    pthread_mutex_destroy(&mutexlock);
    // for (i = 0; i < 10; i++)
    // {
    //     //cout << "i = " << i << endl;
    //     cout << "count = " << count << endl;
    //     sleep(1);
    // }

    return 0;
}
#endif