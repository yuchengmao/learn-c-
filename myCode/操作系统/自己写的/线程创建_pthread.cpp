#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <thread>

using namespace std;

// #if 0
// void *func(void* arg){
//     for (size_t i = 0; i < 5; i++)
//     {
//         cout << "子线程: " << pthread_self() << endl;
//     }
//     return nullptr;
// }
// int main(){
//     pthread_t tid;
//     pthread_create(&tid, nullptr, func, nullptr);
//     //pthread_exit(tid);
//     for (int i = 0; i < 5; i++)
//     {
//         cout << "主线程: " << pthread_self() << endl;
//         //sleep(1);
//     }
//     //指定哪个子线程和主线程分离
//     //pthread_detach(tid);
//     pthread_exit(nullptr);
// }
// #elif 0

// void func()
// {
//     for (int i = 0; i < 5; i++)
//     {
//         cout << "子线程: " << pthread_self() << endl;
//     }
// }
// int main()
// {
//     thread th1(func);
//     th1.join();
//     for (int i = 0; i < 5; i++)
//     {
//         cout << "主线程: " << pthread_self() << endl;
//     }
// }
// #elif 1
/**
 * @brief 线程回收
 * 
 */
#if 0
struct Test
{
    int num;
    int age;
    Test(int n, int a) : num(n), age(a) {}
};
void *func(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "子线程: " << pthread_self() << endl;
    }
    Test *t = (Test *)arg;
    t->age = 20;
    t->num = 18;
    //cout << "num = " << t->num 
    //   << "age = " << t->age << endl;
    pthread_exit(t);

    return nullptr;
}
int main()
{
    //指针请赋初值
    Test *t(new Test(1, 2));
    pthread_t tid;
    pthread_create(&tid, nullptr, func, t);
    //pthread_exit(tid);
    for (int i = 0; i < 5; i++)
    {
        cout << "主线程: " << pthread_self() << endl;
        //sleep(1);
    }
    void *ptr;
    pthread_join(tid, &ptr);
    //Test *pt = (Test *)ptr;
    cout << t->num << ", " << t->age << endl;
}
#endif

/**
 * @brief 线程分离
 * 
 */
#if 1
struct Test
{
    int num;
    int age;
    Test(int n, int a) : num(n), age(a) {}
};
void *func(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "子线程: " << pthread_self() << endl;
    }
    Test *t = (Test *)arg;
    t->age = 20;
    t->num = 18;
    //cout << "num = " << t->num 
    //   << "age = " << t->age << endl;
    pthread_exit(t);

    return nullptr;
}
int main()
{
    //指针请赋初值
    Test *t(new Test(1, 2));
    pthread_t tid;
    pthread_create(&tid, nullptr, func, t);
    //pthread_exit(tid);
    for (int i = 0; i < 5; i++)
    {
        cout << "主线程: " << pthread_self() << endl;
        //sleep(1);
    }
    pthread_detach(tid);
    pthread_exit(nullptr);
}
#endif
