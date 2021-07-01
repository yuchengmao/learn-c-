#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <utility>

using namespace std;

//mutex m1;

class singlemode
{
private:
    static singlemode* instance;
    singlemode() {}
    ~singlemode() {}
    singlemode(const singlemode&) {}
    static mutex m1;

public:
    static singlemode* getInstance(){
        if(!instance){
            //lock_guard<mutex> locker1(m1, adopt_lock);
            //lock_guard<mutex> locker2(m1);
            instance = new singlemode();
            cout << "已给对象分配空间" << endl;
            for (int i = 0; i > -100; i--){
                cout << "class" << endl;
            }
            //this_thread::sleep_for(chrono::milliseconds(1));
        }
        return instance;
    }
};
//  静态成员变量需要在类外初始化
singlemode* singlemode::instance = nullptr;
mutex singlemode::m1;

int main(){

    singlemode* mode = singlemode::getInstance();
    //thread t1(singlemode::getInstance());
    //t1.join();
    for (int i = 0; i < 100; i++)
    {
        cout << "main" << endl;
    }
}