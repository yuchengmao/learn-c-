#ifndef A579CC93_9407_400C_A2BD_1669FA080019
#define A579CC93_9407_400C_A2BD_1669FA080019

#include <iostream>
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <string.h>

using namespace std;
using callback = void (*)(void *arg);

//任务结构体-------------------------------------
struct Task
{
    Task()
    {
        function = nullptr;
    }
    Task(callback f, void *arg)
    {
        this->arg = arg;
        function = f;
    }
    callback function;
    void *arg;
};

//任务队列类型------------------------------------
class TaskQueue
{
public:
    TaskQueue();
    ~TaskQueue();

    //添加任务
    void addTask(Task task);
    //重载
    void addTask(callback f, void *arg);
    //取出一个任务
    Task takeTask();
    //获取当前任务个数
    inline int taskNum()
    {
        return m_taskQ.size();
    }

private:
    pthread_mutex_t mutex1;
    queue<Task> m_taskQ;
};

//构造函数
TaskQueue::TaskQueue()
{
    pthread_mutex_init(&mutex1, nullptr);
}
//析构函数
TaskQueue::~TaskQueue()
{
    pthread_mutex_destroy(&mutex1);
}
//增加任务
void TaskQueue::addTask(Task task)
{
    pthread_mutex_lock(&mutex1);
    this->m_taskQ.push(task);
    pthread_mutex_unlock(&mutex1);
}
//增加任务重载
void TaskQueue::addTask(callback f, void *arg)
{
    pthread_mutex_lock(&mutex1);
    this->m_taskQ.push(Task(f, arg));
    pthread_mutex_unlock(&mutex1);
}
//取出任务
Task TaskQueue::takeTask()
{
    pthread_mutex_lock(&mutex1);
    Task taskNow;
    if (!m_taskQ.empty())
    {
        taskNow = this->m_taskQ.front();
        m_taskQ.pop();
    }
    pthread_mutex_unlock(&mutex1);
    return taskNow;
}

//线程池类---------------------------------------
class threadPool
{
public:
    threadPool(int max, int min);
    ~threadPool();
    void addTask(Task task);
    int getBusyNum();
    int getAliveNum();
    void exitThread();

private:
    static void *worker(void *arg);
    static void *manager(void *arg);

    TaskQueue *taskQ;    //任务队列
    pthread_t managerID; //管理线程 ID
    pthread_t *workerID; //工作线程 ID

    int maxNum;                  //最大线程数
    int minNum;                  //最小线程数
    int busyNum;                 //工作中线程数
    int liveNum;                 //活着的线程数
    int exitNum;                 //要杀死的线程数
    static const int NUMBER = 2; //每次添加线程数

    pthread_mutex_t mutexpool; //线程池锁
    pthread_cond_t notempty;   //是否为空

    bool shutdown; //是否需要销毁
};
//线程池初始化
threadPool::threadPool(int max, int min)
{
    //实例化任务队列
    taskQ = new TaskQueue;
    if (!taskQ)
    {
        cout << "malloc task failed" << endl;
    }
    do
    {
        //实例化工作线程
        workerID = new pthread_t[max];
        if (!workerID)
        {
            cout << "failed to malloc workerid" << endl;
            break;
        }
        memset(workerID, 0, sizeof(pthread_t) * max);

        //初始化相关参数
        this->minNum = min;
        this->maxNum = max;
        this->busyNum = 0;
        this->liveNum = min;
        this->exitNum = 0;
        this->shutdown = false;

        //初始化线程
        if (pthread_mutex_init(&mutexpool, nullptr) != 0 ||
            pthread_cond_init(&notempty, nullptr) != 0)
        {
            cout << "failed to init mutex or cond" << endl;
            break;
        }

        //创建线程
        pthread_create(&managerID, nullptr, manager, this);
        for (int i = 0; i < min; i++)
        {
            pthread_create(&workerID[i], nullptr, worker, this);
        }

        return;
    } while (0);

    //初始化失败，释放相关内存
    if (workerID)
    {
        delete[] workerID;
    }
    if (taskQ)
    {
        delete taskQ;
    }
}
//线程池析构
threadPool::~threadPool()
{
    //关闭线程池
    shutdown = 1;
    //阻塞回收管理者线程
    pthread_join(managerID, nullptr);
    //唤醒阻塞的消费者线程
    for (int i = 0; i < liveNum; i++)
    {
        pthread_cond_signal(&notempty);
    }
    //释放堆内存
    if (taskQ)
    {
        delete taskQ;
    }
    if (this->workerID)
    {
        delete[] workerID;
    }
    //销毁锁和条件变量
    pthread_mutex_destroy(&mutexpool);
    pthread_cond_destroy(&notempty);

}
//线程池增加任务
void threadPool::addTask(Task task)
{
    // 由于添加任务函数已经做过同步，因此这里不需要再加锁
    if (shutdown)
    {
        pthread_mutex_unlock(&mutexpool);
        return;
    }
    // 添加任务
    this->taskQ->addTask(task);
}
//线程池获取忙线程数
int threadPool::getBusyNum()
{
    pthread_mutex_lock(&mutexpool);
    return this->busyNum;
    pthread_mutex_unlock(&mutexpool);
}
//线程池获取活线程数
int threadPool::getAliveNum()
{
    pthread_mutex_lock(&mutexpool);
    return this->liveNum;
    pthread_mutex_unlock(&mutexpool);
}
//线程池退出线程
void threadPool::exitThread()
{
    pthread_t pid = pthread_self();
    for (int i = 0; i < maxNum; i++)
    {
        if (workerID[i] == pid)
        {
            workerID[i] = 0;
            printf("exitThread...");
            break;
        }
    }
    pthread_exit(nullptr);
}
//线程池工作线程
void *threadPool::worker(void *arg)
{
    //由于这是静态函数，需要拿到实例对象才能对类中参数操作
    threadPool *pool = static_cast<threadPool *>(arg);

    while (true)
    {
        pthread_mutex_lock(&pool->mutexpool);

        while (pool->taskQ->taskNum() == 0 && !pool->shutdown)
        {
            //阻塞工作线程
            pthread_cond_wait(&pool->notempty, &pool->mutexpool);

            //判断是否需要销毁线程
            if (pool->exitNum > 0)
            {
                pool->exitNum--;
                if (pool->liveNum > pool->minNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexpool);
                    pool->exitThread();
                }
            }

            //判断线程池是否关闭
            if (pool->shutdown)
            {
                pthread_mutex_unlock(&pool->mutexpool);
                pool->exitThread();
                return nullptr;
            }

            //从任务队列取出任务
            Task task = pool->taskQ->takeTask();
            pool->busyNum++;
            pthread_mutex_unlock(&pool->mutexpool);

            cout << "thread: " << pthread_self() << "start working..." << endl;

            task.function(task.arg);
            free(task.arg);
            task.arg = nullptr;

            printf("thread %ld end working...\n", pthread_self());
            pthread_mutex_lock(&pool->mutexpool);
            pool->busyNum--;
            pthread_mutex_unlock(&pool->mutexpool);
        }
    }
}
//线程池管理线程
void *threadPool::manager(void *arg)
{
    threadPool *pool = static_cast<threadPool *>(arg);
    while (!pool->shutdown)
    {
        sleep(3);

        //取出线程池中任务数量，当前线程数量，忙线程数量
        pthread_mutex_lock(&pool->mutexpool);
        int queueSize = pool->taskQ->taskNum();
        int liveNum = pool->liveNum;
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexpool);

        // 添加线程
        // 任务的个数 > 存活线程个数 && 存活线程个数 < 最大线程数
        if (queueSize > liveNum && liveNum < pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexpool);
            int counter = 0;
            for (int i = 0; i < pool->maxNum && counter < NUMBER; i++)
            {
                if (pool->workerID[i] == 0)
                {
                    pthread_create(&pool->workerID[i], nullptr, worker, pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexpool);
        }

        //销毁线程
        // 忙线程 * 2 < 存活线程数 && 存活线程数 > 最小线程数
        if (busyNum * 2 < liveNum && liveNum > pool->minNum)
        {
            pthread_mutex_lock(&pool->mutexpool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexpool);

            //让工作线程自销毁
            for (int i = 0; i < NUMBER; i++)
            {
                pthread_cond_signal(&pool->notempty);
            }
        }
    }
}


#endif /* A579CC93_9407_400C_A2BD_1669FA080019 */
