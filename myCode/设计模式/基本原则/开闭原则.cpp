/**
 * @file 开闭原则.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-28
 * 
 * @copyright Copyright (c) 2021
 * 
 * 添加新方法只需要增加代码而不需要修改
 */

#include <iostream>

using namespace std;

class AbstractCalculator
{
public:
    virtual int getResult(int a, int b) = 0;

protected:
    int mA, mB;
};

class Plus : public AbstractCalculator
{
public:
    virtual int getResult(int a, int b)
    {
        this->mA = a;
        this->mB = b;
        cout << a << " + " << b 
            << " = " << mA + mB 
            << endl;
        return mA + mB;
    }
};
class Subtration : public AbstractCalculator
{
public:
    virtual int getResult(int a, int b)
    {
        this->mA = a;
        this->mB = b;
        cout << a << " - " << b 
            << " = " << mA - mB 
            << endl;
        return mA - mB;
    }
};
class  Multiply : public AbstractCalculator
{
public:
    virtual int getResult(int a, int b)
    {
        this->mA = a;
        this->mB = b;
        cout << a << " * " << b 
            << " = " << mA * mB 
            << endl;
        return mA * mB;
    }
};
class Division : public AbstractCalculator
{
public:
    virtual int getResult(int a, int b)
    {
        this->mA = a;
        this->mB = b;
        cout << a << " / " << b 
            << " = " << mA / mB 
            << endl;
        return mA / mB;
    }
};

int main()
{
    AbstractCalculator *plus = new Plus;
    plus->getResult(1, 2);
    AbstractCalculator *sub = new Subtration;
    sub->getResult(1, 2);
    AbstractCalculator *mul = new Multiply;
    mul->getResult(1, 2);
    AbstractCalculator *div = new Division;
    div->getResult(1, 2);
}