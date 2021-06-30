#include <iostream>
#include <thread>

using namespace std;

void print(unique_ptr<int> ptr)
{
    cout << "子线程:" << ptr.get() << endl;
    cout << this_thread::get_id() << endl;
}
int main()
{
    unique_ptr<int> ptr(new int(1000));
    cout << "主线程:" << ptr << endl;

    thread th1(print, move(ptr));
    th1.join();

    cout << this_thread::get_id() << endl;
    cout << "主线程:" << ptr << endl;
}