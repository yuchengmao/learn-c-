#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

mutex m1;

// #if 0
// void function_1()
// {
//     //m1.lock();
//     for (int i = 0; i > -100; i--)
//     {
//         cout << "from f1 : " << i << endl;
//     }
//     //m1.unlock();
// }
// int main()
// {
//     // 线程 main 和 function_1 占用同一个资源 cout，输出混乱
//     thread t1(function_1);
//     for (int i = 0; i < 100; i++)
//     {
//         cout << "from main : " << i << endl;
//     }
//     t1.join();
// }
// #endif

// #if 0
// void share_print(string msg, int id){
//     m1.lock();
//     // 如果这个代码抛出异常则会永远锁在这里，因此不推荐使用 lock 和 unlock
//     cout << msg << id << endl;
//     m1.unlock();
// }
// void function_1()
// {
//     for (int i = 0; i > -100; i--)
//     {
//         share_print("from f1 : ", i);
//     }
// }
// int main()
// {
//     thread t1(function_1);
//     for (int i = 0; i < 100; i++)
//     {
//         share_print("from main : ", i);
//     }
//     t1.join();
// }
// #endif

// #if 0
// void share_print(string msg, int id)
// {
//     lock_guard<mutex> guard(m1);
//     cout << msg << id << endl;
// }
// void function_1()
// {
//     for (int i = 0; i > -100; i--)
//     {
//         share_print("from f1 : ", i);
//     }
// }
// int main()
// {
//     thread t1(function_1);
//     for (int i = 0; i < 100; i++)
//     {
//         share_print("from main : ", i);
//     }
//     t1.join();
// }
// #endif

#if 1
class lockFile
{
public:
    lockFile() { f.open("log.txt"); }
    void shared_print(string msg, int id)
    {
        lock_guard<mutex> locker(m_mutex, adopt_lock);
        
        std::cout << msg << " : " << id << std::endl;
        f << msg << " : " << id << std::endl;

        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

private:
    mutex m_mutex;
    ofstream f;
};

void function_1()
{
    lockFile log;
    for (int i = 0; i > -100; i--)
    {
        log.shared_print("f1 : ", i);
    }
}
int main()
{
    lockFile lF1;
    thread t1(function_1);
    try
    {
        for (int i = 0; i < 100; i++)
        {
            lF1.shared_print("main : ", i);
        }
        t1.join();
    }
    catch (...){}
    t1.join();
}
#endif