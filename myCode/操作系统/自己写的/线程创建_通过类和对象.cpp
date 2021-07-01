#include <iostream>
#include <thread>

using namespace std;

class MM
{
private:
public:
    MM() {}
    ~MM() {}
    void operator()()
    {
        cout << "子线程启动..." << endl;
    }
};

/**
 * @brief 对象充当线程处理函数
 * 
 */
void test01()
{
    MM mm;
    thread th1(mm);
    th1.join();
}

void test02()
{
    thread th2((MM()));
    th2.join();
}
int main()
{
    test01();
    test02();
}