#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;

class Test
{
public:
    void print(int &num)
    {
        lock_guard<mutex> locker1(m1);
        num = 1001;
        for (size_t i = 0; i < 100; i++)
        {
            cout << "子线程1 : " << i << ", " << this_thread::get_id() << endl;
        }
    }
    void print2()
    {
        lock_guard<mutex> locker2(m1);
        for (size_t i = 0; i < 100; i++)
        {
            cout << "子线程2 : " << i << ", " << this_thread::get_id() << endl;
        }
    }
};

int main()
{
    Test t1;
    int num = 1000;

    thread th1(&Test::print, t1, ref(num));
    thread th2(&Test::print2, t1);

    th1.join();
    th2.join();

    return 0;
}