#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

//生产者消费者数量
#define PRODUCER 5
#define CONSUMER 5
#define MAX_ITEM 50

//条件变量与互斥锁
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

struct Node
{
    int num;
    struct Node *next;
    Node() {}
    Node(int num) : num(num), next(nullptr) {}
    Node(int num, Node* next) : num(num), next(next) {}
};
Node *head = nullptr;

//获取当前仓库内物品数量
int getItemNum(Node *head){
    Node *myhead = head;
    int num = 0;
    while(myhead){
        num++;
        myhead = myhead->next;
    }
    return num;
}
//生产函数
void *producer(void *arg)
{
    //生产者一直想要生产，卷王就是你
    while(1){
        //进来把锁锁上
        pthread_mutex_lock(&mutex1);

        //如果仓库满了，那我没法生产了
        while(getItemNum(head) >= MAX_ITEM){
            cout << "仓库都满啦！！" << endl;
            sleep(1);
            /*
                休息一下，把条件变量存储起来 cond2 存储发起的请求线程的信息
                mutex 此时打开，等到谁给 cond2 发起通知时，自动加锁（还是要抢）继续生产
            */
            pthread_cond_wait(&cond2, &mutex1);
        }

        //生产过程
        Node *item = new Node(rand() % 100);
        item->next = head;
        head = item;
        printf("生产者，id：%ld，number：%d, total = %d\n", pthread_self(), item->num, getItemNum(head));
        
        //解锁
        pthread_mutex_unlock(&mutex1);
        //向消费者发送信息
        pthread_cond_broadcast(&cond1);
        sleep(rand()%3);
    }
    return nullptr;
}
//消费函数
void *consumer(void *arg)
{
    //贪得无厌，一直消费
    while(1){
        //进来先把门锁上
        pthread_mutex_lock(&mutex1);

        //当仓库没有东西，没法消费
        while(getItemNum(head) < 1){
            cout << "仓库都空啦！！" << endl;
            //等，cond1 存储等的人的信息
            pthread_cond_wait(&cond1, &mutex1);
        }
        Node *item = head;
        head = head->next;
        printf("消费者，id：%ld，number：%d, total = %d\n", pthread_self(), item->num, getItemNum(head));
        delete item;

        pthread_mutex_unlock(&mutex1);
        //给生产者发送信息
        pthread_cond_broadcast(&cond2);
        sleep(rand()%3);
    }
    return nullptr;
}

int main()
{
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
    //删除锁和条件变量
    pthread_mutex_destroy(&mutex1);
    pthread_cond_destroy(&cond1);
}