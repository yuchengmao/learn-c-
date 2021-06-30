#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{
    int (*pMax)(int, int) = nullptr;
    pMax = [](int a, int b) -> int
    { return a > b ? a : b; };
    cout << pMax << endl;

    thread th1([]
               { cout << "子线程" << endl; });
    th1.join();
    cout << "主线程" << endl;
    return 0;
}
