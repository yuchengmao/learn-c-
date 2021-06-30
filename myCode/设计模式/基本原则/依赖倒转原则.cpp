/**
 * @file 依赖倒转原则.cpp
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

#if 0
/**
 * @brief 高层依赖下一层
 * 
 */
//高层模块
class bankWorker{
public:
    void save(){
        cout << "存款业务" << endl;
    }
    void pay(){
        cout << "支付业务" << endl;
    }
    void trans(){
        cout << "转账业务" << endl;
    }
};

//中层模块
//办理存款模块
void doSave(bankWorker* worker){
    worker->save();
}
//办理支付模块
void doPay(bankWorker* worker){
    worker->pay();
}
//办理转账模块
void doTrans(bankWorker* worker){
    worker->trans();
}

//业务模块
void test01(){
    bankWorker *worker = new bankWorker;
    doSave(worker);
    doPay(worker);
    doTrans(worker);
}
#endif

/**
 * @brief 上层业务，类保遵循一职责原则
 * 
 */
class AbstractWorker
{
public:
    virtual void work() = 0;
};
//负责存款业务的员工
class Save : public AbstractWorker
{
public:  
    virtual void work(){
        cout << "存款" << endl;
    }
};
//负责支付业务的员工
class Pay : public AbstractWorker
{
public:  
    virtual void work(){
        cout << "支付" << endl;
    }
};
//负责转账业务的员工
class Trans : public AbstractWorker
{
public:  
    virtual void work(){
        cout << "转账" << endl;
    }
};

//中层业务（依赖于抽象层）
void doWork(AbstractWorker* worker){
    worker->work();
}

void test01(){
    AbstractWorker *worker = new Pay;
    doWork(worker);
}

int main()
{
    test01();
}