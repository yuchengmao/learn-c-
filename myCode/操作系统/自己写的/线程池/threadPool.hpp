#ifndef FA58F577_B970_4454_BB92_9AEC9CF77351
#define FA58F577_B970_4454_BB92_9AEC9CF77351

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <queue>

using namespace std;

void *manager(void *arg);
void *worker(void *arg);

//任务结构体
struct Task
{
    void (*function)(void *arg);
    void *arg;
};

//线程池结构体
struct ThreadPool
{
    //任务队列
    Task *taskQ;
    int queueCapacity; //容量
    int queueSize;     //当前任务个数
    int queueFront;    //队列头
    int queueRear;     //队列尾

    pthread_t manaagerID; //管理者线程 ID
    pthread_t *threadIDs; //工作者线程 ID

    int minNum;  //最小线程数量
    int maxNum;  //最大线程数量
    int busyNum; //忙的线程数量
    int liveNum; //存活的线程数量
    int exitNum; //要销毁的线程数量

    pthread_mutex_t mutexPool; //锁整个线程池
    pthread_mutex_t mutexBusy; //锁 busyNum 变量
    pthread_cond_t notFull;    //任务队列是否满了
    pthread_cond_t notEmpty;   //任务队列是否空了

    int shutdown; //当前线程池是否需要被销毁
};

//创建线程池
ThreadPool *createPool(int maxnum, int minnum, int queuesize)
{
    ThreadPool *pool = new ThreadPool();
    if (!pool)
    {
        printf("malloc threadpool error!!");
        return nullptr;
    }

    pool->threadIDs = (pthread_t *)malloc(sizeof(pthread_t) * maxnum);
    if (!pool->threadIDs)
    {
        printf("malloc threadid error!!");
        return nullptr;
    }
    memset(pool->threadIDs, 0, sizeof(pthread_t) * maxnum);

    pool->minNum = minnum;
    pool->maxNum = maxnum;
    pool->busyNum = 0;
    pool->liveNum = minnum;
    pool->exitNum = 0;
    pool->notFull = PTHREAD_COND_INITIALIZER;
    pool->notEmpty = PTHREAD_COND_INITIALIZER;
    pool->mutexPool = PTHREAD_MUTEX_INITIALIZER;
    pool->mutexBusy = PTHREAD_MUTEX_INITIALIZER;
    /**
     * @brief 调用函数初始化方法    
     * pthread_cond_init(&pool->isEmpty, nullptr);
     * pthread_cond_init(&pool->isFull, nullptr);
     * pthread_mutex_init(&pool->mutexPool, nullptr);
     * pthread_mutex_init(&pool->mutexBusy, nullptr);
     */

    pool->taskQ = new Task();
    pool->queueCapacity = queuesize;
    pool->queueSize = 0;
    pool->queueFront = 0;
    pool->queueRear = 0;
    pool->shutdown = 0;

    //创建线程
    pthread_create(&pool->manaagerID, nullptr, manager, nullptr);
    for (size_t i = 0; i < minnum; i++)
    {
        pthread_create(pool->threadIDs, nullptr, worker, nullptr);
    }

    return nullptr;
}
//管理者函数
void *manager(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    while ((!pool->shutdown))
    {
        sleep(3);

        pthread_mutex_lock(&pool->mutexPool);
        int queuesize = pool->queueSize;
        int livenum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        pthread_mutex_lock(&pool->mutexBusy);
        int busynum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);
    }

    return nullptr;
}
//工作者函数
void *worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;

    while (1)
    {
        pthread_mutex_lock(&pool->mutexPool);
        //当前任务队列是否为空
        while (pool->queueSize == 0 && !pool->shutdown)
        {
            //阻塞工作线程
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
        }
        //判断线程池是否关闭
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            pthread_exit(nullptr);
        }
        //从任务队列中取出一个任务
        Task task;
        task.function = pool->taskQ[pool->queueFront].function; //??
        task.arg = pool->taskQ[pool->queueFront].arg;
        //移动头节点
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
        pool->queueSize--;
        //解锁
        pthread_mutex_unlock(&pool->mutexPool);

        task.function(task.arg);
        free(task.arg);
        task.arg = nullptr;

        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);
    }
    return nullptr;
}

//销毁线程池

//给线程池添加任务

//获取线程池中工作的线程个数

//获取线程池中活着的线程个数

#endif /* FA58F577_B970_4454_BB92_9AEC9CF77351 */
