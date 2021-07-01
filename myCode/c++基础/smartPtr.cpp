#include <iostream>
#include <memory>
#include "myFunction.hpp"
#include <unordered_map>

using namespace std;

/**
 * @brief   shared_ptr
 * 
 *          对于 new 出来的两个指针，若将一个指针指向另一个指针后，两个指针此时指向同一地址，
 *          于是就会空出一个地址变成 孤儿地址，导致内存泄漏
 * 
 *          对于 智能指针，每个指针有一个引用计数，若将两个指针中的一个指向另一个，则当前地址
 *          的引用计数变为 0，地址自动释放，而指向的另一个地址 引用计数 加一
 * 
 */
void test01()
{
    int *p1 = new int(1);
    int *p2 = new int(2);
    int *pp = p2;

    cout << "刚分配地址时：---------------------" << endl;
    cout << "p1 : ";
    printVal(p1);
    cout << "p2 : ";
    printVal(p2);

    cout << "将 p1 赋给 p2 后：---------------------" << endl;
    p2 = p1;
    cout << "p1 :";
    printVal(p1);
    cout << "p2 :";
    printVal(p2);

    cout << "将 p2 delete 后：---------------------" << endl;
    delete p2;
    cout << "p1 :";
    printVal(p1);
    cout << "p2 :";
    printVal(p2);
    cout << "pp :";
    printVal(pp);

    shared_ptr<int> p3 = make_shared<int>(3);
    shared_ptr<int> p4 = make_shared<int>(4);
    shared_ptr<int> p5 = p4;

    p3 = p4;
    p4 = p3;

    //p3.reset();
    //p3.~shared_ptr();
    //p4.~shared_ptr();
    //p4.~shared_ptr();

    cout << p3.use_count() << endl;
    cout << p4.use_count() << endl;
    cout << p5.use_count() << endl;
}

void test02()
{
    auto_ptr<int> p1(new int(3));
    auto_ptr<int> p2;
    //  将 p1 赋给 p2 后， p2 会剥夺 p1 所有权，再去访问 p1 会内存泄漏
    p2 = p1;

    cout << *p1 << endl;
    cout << *p2 << endl;
}

void test03()
{
    unique_ptr<string> p3(new string("hello")), p4(new string("world"));

    cout << *p3 << endl;
    cout << *p4 << endl;

    p3 = move(p4);
    cout << *p3 << endl;
    cout << *p4 << endl;
}
/**
 * @brief 野指针
 * 
 */
void test04(){
    int *a = new int(1);
    int *b = a;

    delete a;
    cout << *b << endl;
}
int main()
{
   
    //test03();
    //test01();
    //test02();
}