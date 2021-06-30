/**
 * @file 迪米特法则.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-28
 * 
 * @copyright Copyright (c) 2021
 * 
 * 不管你有哪些楼盘 A B C D等，我只需要告诉你
 * 我需要什么样的楼盘，然后你直接告诉我有没有
 * 有的话就购买，没有就不买
 */
#include <iostream>
#include <vector>

using namespace std;

//基类
class AbstractBuilding
{
public:
    virtual void sale() = 0;
    virtual string getQuality() = 0;

protected:
    string quality;
};
//品质A楼盘
class BulidingA : public AbstractBuilding
{
public:
    BulidingA()
    {
        quality = "高品质";
    }
    virtual void sale()
    {
        cout << quality << "A楼盘售卖" << endl;
    }
    virtual string getQuality()
    {
        return quality;
    }
};
//品质B楼盘
class BulidingB : public AbstractBuilding
{
public:
    BulidingB()
    {
        quality = "低品质";
    }
    virtual void sale()
    {
        cout << quality << "B楼盘售卖" << endl;
    }
    virtual string getQuality()
    {
        return quality;
    }
};

//中介类
class Media
{
public:
    Media()
    {
        AbstractBuilding *building = new BulidingA;
        buildingVec.push_back(building);
        building = new BulidingB;
        buildingVec.push_back(building);
    }
    ~Media()
    {
        for (vector<AbstractBuilding *>::iterator it = buildingVec.begin(); it != buildingVec.end(); it++)
        {
            if (*it)
            {
                free(*it);
            }
        }
    }
    //对外接口
    AbstractBuilding *findMyBuilding(string quality)
    {
        for (vector<AbstractBuilding *>::iterator it = buildingVec.begin(); it != buildingVec.end(); it++)
        {
            if ((*it)->getQuality() == quality)
            {
                return *it;
            }
        }
        return nullptr;
    }

private:
    vector<AbstractBuilding *> buildingVec;
};
void test01()
{
    Media *media = new Media;
    AbstractBuilding* building = media->findMyBuilding("高品质");
    if(building){
        building->sale();
    }
}

//客户端
int main()
{
    test01();
}