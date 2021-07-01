#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

#define READLOCK_NUM 5
#define WRITELOCK_NUM 5
#define READTIME 5
#define WRITETIME 50

//全局变量，读写锁需要操作的部分(共享资源)
int num = 0;

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

//读操作函数
void *read(void *arg)
{
    for (size_t i = 0; i < READTIME; i++)
    {
        //读锁
        pthread_rwlock_rdlock(&rwlock);
        printf("read, id = %d, number = %d\n", this_thread::get_id(), num);
        pthread_rwlock_unlock(&rwlock);
    }
    return nullptr;
}
//写操作函数
void *write(void *arg)
{
    for (size_t i = 0; i < WRITETIME; i++)
    {
        //写锁
        pthread_rwlock_wrlock(&rwlock);
        printf("write, id = %d, number = %d\n", pthread_self(), ++num);
        pthread_rwlock_unlock(&rwlock);
    }
    return nullptr;
}
int main(int argc, char const *argv[])
{
    //创建五个读线程和五个写线程
    pthread_t th1[READLOCK_NUM], th2[WRITELOCK_NUM];

    //创建线程
    for (size_t i = 0; i < READLOCK_NUM; i++)
    {
        pthread_create(&th1[i], nullptr, read, nullptr);
    }
    for (size_t i = 0; i < WRITELOCK_NUM; i++)
    {
        pthread_create(&th1[i], nullptr, write, nullptr);
    }
    sleep(10);
    //回收线程
    for (size_t i = 0; i < READLOCK_NUM; i++)
    {
        pthread_join(th1[i], nullptr);
    }
    for (size_t i = 0; i < WRITELOCK_NUM; i++)
    {
        pthread_join(th2[i], nullptr);
    }

    //读写锁销毁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
