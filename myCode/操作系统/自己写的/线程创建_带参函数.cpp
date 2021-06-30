
#include <iostream>
#include <thread>

using namespace std;

void print(int &num)
{
    cout << "子线程" << endl;
}

int main()
{

    int num = 0;
    thread th1(print, ref(num));
    th1.join();

    cout << "main" << endl;
    auto it = 0;
}