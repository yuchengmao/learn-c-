#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/**
 * @brief 
 * mac OS X 不支持sem_init()和sem_destroy()
解决办法:

sem_init(&sem, 0, 1)改成
sem_open("sem", O_CREAT|O_EXCL, S_IRWXU, 0)

sem_destory(&sem)改成
sem_unlink("sem");
另外，支持pthread_mutex_init(&mutex, NULL)
却不支持pthread_mutex_destory(&mutex)
 * 
 */
using namespace std;

sem_t *sem1, *sem2;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

//生产者消费者数量
#define PRODUCER 5
#define CONSUMER 5
#define MAX_ITEM 50

struct Node
{
    int num;
    struct Node *next;
    Node() {}
    Node(int num) : num(num), next(nullptr) {}
    Node(int num, Node *next) : num(num), next(next) {}
};
Node *head = nullptr;

//获取当前仓库内物品数量
int getItemNum(Node *head)
{
    Node *myhead = head;
    int num = 0;
    while (myhead)
    {
        num++;
        myhead = myhead->next;
    }
    return num;
}

//生产函数
void *producer(void *arg)
{
    while (1)
    {
        sem_wait(sem1);
        pthread_mutex_lock(&mutex1);
        Node *item = new Node(rand() % 100);
        item->next = head;
        head = item;
        printf("生产者，id：%ld，number：%d, total = %d\n", pthread_self(), item->num, getItemNum(head));
        sem_post(sem2);
        pthread_mutex_unlock(&mutex1);
        sleep(rand() % 3);
    }
    return nullptr;
}
//消费函数
void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(sem2);
        pthread_mutex_lock(&mutex1);
        Node *item = head;
        if (head)
        {
            head = head->next;
            printf("消费者，id：%ld，number：%d, total = %d\n", pthread_self(), item->num, getItemNum(head));
        }
        else
        {
            printf("消费者，id：%ld，number：%d, total = %d\n", pthread_self(), -1, getItemNum(head));
        }
        delete (item);
        pthread_mutex_unlock(&mutex1);
        sem_post(sem1);
        sleep(rand() % 3);
    }
    return nullptr;
}

int main()
{
    /*
        sem_t *sem_open(const char *name, int oflag, mode_t mode, unsinged int value);
        name --> 信号灯的外部名字
        oflag --> 选择创建或打开一个现有的信号灯
        mode --> 权限位
        value --> 信号灯初始值

        oflag参数可以是：
            1，0
            2，O_CREAT 创建一个信号灯
            3，O_CREAT｜O_EXCL 如果没有指定的信号灯就创建
    */
    //sem1 = sem_open("sem1", O_CREAT | O_EXCL, S_IRWXU, 10);
    //sem2 = sem_open("sem2", O_CREAT | O_EXCL, S_IRWXU, 0);

    sem_init(sem1, 0, 5);
    sem_init(sem2, 0, 5);

    srand(time(nullptr));
    //创建线程
    pthread_t th1[PRODUCER], th2[CONSUMER];
    for (size_t i = 0; i < PRODUCER; i++)
    {
        pthread_create(&th1[i], nullptr, producer, nullptr);
    }
    for (size_t i = 0; i < CONSUMER; i++)
    {
        pthread_create(&th2[i], nullptr, consumer, nullptr);
    }
    //回收线程
    for (size_t i = 0; i < PRODUCER; i++)
    {
        pthread_join(th1[i], nullptr);
    }
    for (size_t i = 0; i < CONSUMER; i++)
    {
        pthread_join(th2[i], nullptr);
    }

    pthread_mutex_destroy(&mutex1);
    sem_destroy(sem1);
    sem_destroy(sem2);
}
