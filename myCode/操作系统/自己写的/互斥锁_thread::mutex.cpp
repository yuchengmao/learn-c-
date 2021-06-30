#include <unistd.h>
#include <iostream>
#include <thread>
//#include <pthread.h>

using namespace std;
/**
 * @brief 加不同的🔒相当于没加
 * 
 */
mutex m1;
pthread_mutex_t mutex1;

//线程处理函数
void test01()
{
    //lock_guard<mutex> locker(m1);
    pthread_mutex_lock(&mutex1);
    for (int i = 0; i < 100; i++)
    {
        cout << "进程id：" << getpid() << "," << pthread_self() << endl;
        cout << "子线程id：" << this_thread::get_id() << endl;
    }
    pthread_mutex_unlock(&mutex1);
}
void test02()
{
    //lock_guard<mutex> locker(m1);
    pthread_mutex_lock(&mutex1);
    for (int i = 0; i > -100; i--)
        cout << "子线程2" << endl;
    pthread_mutex_unlock(&mutex1);
}
int main()
{
    pthread_mutex_init(&mutex1, nullptr);

    thread thread1(test01);
    thread thread2(test02);

    thread1.join();
    thread2.join();

    cout << thread::hardware_concurrency() << endl;
}