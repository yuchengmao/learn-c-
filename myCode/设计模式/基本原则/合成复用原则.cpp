/**
 * @file 合成复用原则.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

using namespace std;

class AbstractCar
{
public:
    virtual void run() = 0;
};

class daZhong : public AbstractCar
{
public:
    virtual void run()
    {
        cout << "大众" << endl;
    }
};

class tuoLaJi : public AbstractCar
{
public:
    virtual void run()
    {
        cout << "拖拉机" << endl;
    }
};

#if 0
//使用继承
class PersonA : public daZhong
{
public:
    void douFeng(){
        run();
    }
};

class PersonB : public tuoLaJi
{
public:
    void douFeng(){
        run();
    }
};
#endif

//使用组合
class Person
{
public:
    void setCar(AbstractCar *car)
    {
        this->car = car;
    }
    ~Person()
    {
        if (this->car)
        {
            free(this->car);
        }
    }
    void douFeng()
    {
        if (this->car)
        {
            cout << "开";
            this->car->run();
            cout << "兜风" << endl;
        }
        else{
            cout << "你没车" << endl;
        }

        if (this->car)
        {
            free(this->car);
            this->car = nullptr;
        }
    }

private:
    AbstractCar *car;
};

void test01()
{

    Person *p1 = new Person;
    p1->setCar(new daZhong);
    p1->douFeng();

    p1->douFeng();

    p1->setCar(new tuoLaJi);
    p1->douFeng();
}

int main()
{
    test01();
}