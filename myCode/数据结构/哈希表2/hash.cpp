#include "Hash.hpp"
#include <pthread.h>
#include <mutex>
#include <chrono>

/**
 * @brief Construct a new Hash:: Hash object
 * 
 *      将哈希桶初始化，每个节点分配地址空间
 */
Hash::Hash()
{
    for (int i = 0; i < tableSize; i++)
    {
        hashTable[i] = new item();
        hashTable[i]->name = "empty";
        hashTable[i]->drink = "empty";
        hashTable[i]->next = nullptr;
    }
}

//  析构函数
Hash::~Hash()
{
}

/**
 * @brief 哈希函数，用作数据 key 的哈希映射
 * key 存的是姓名， value 存的是个人信息，经过哈希函数将 key映射到
 * 哈希表中，于是以后查询就可以通过 某人的姓名直接查找到其信息
 * @param key （输入 key 的数据）
 * @return int 
 */
int Hash::hashFunction(string key)
{
    int sum = 0;
    int index;

    for (size_t i = 0; i < key.size(); ++i)
    {
        //  static_cast --> 类型转换函数
        sum += static_cast<int>(key[i]);
    }
    //  哈希映射（方法可以有很多）
    index = sum & (tableSize - 1);

    cout << "key[0] = " << key[0] << endl;
    //cout << "key[0] = " << static_cast<int>(key[0]) << endl;
    cout << "key[1] = " << key[1] << endl;
    cout << "key[2] = " << key[2] << endl;
    cout << "sum = " << sum << endl;
    cout << "index = " << index << endl;
    cout << "--------------" << endl;

    return index;
}

/**
 * @brief 向哈希表增加键值对
 * 
 * @param name 姓名（相当于 key）
 * @param drink 信息（相当于 value）
 */
void Hash::AddItem(string name, string drink)
{

    int index = hashFunction(name);

    if (hashTable[index]->name == "empty")
    {
        hashTable[index]->name = name;
        hashTable[index]->drink = drink;
    }
    else
    {
        item *p = hashTable[index];
        item *n = new item(name, drink);

        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = n;
    }
}

/**
 * @brief 某个哈希桶下的元素个数
 * 
 * @param index （哈希桶位置）
 * @return int 
 */
int Hash::NumberOfItemsInIndex(int index)
{

    int count = 0;
    if (hashTable[index]->name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        item *p = hashTable[index];
        while (p->next)
        {
            count++;
            p = p->next;
        }
    }
    return count;
}

/**
 * @brief 打印各个桶的使用情况
 * 
 */
void Hash::PrintTable()
{

    int number;
    for (int i = 0; i < tableSize; ++i)
    {
        cout << "i = " << i << ": " << endl;
        number = NumberOfItemsInIndex(i);
        cout << "index = " << i << ": " << endl;
        cout << hashTable[i]->name << ", " << hashTable[i]->drink << endl;
        cout << "# of items = " << number << endl;
        cout << "---------------" << endl;
    }
}

/**
 * @brief 打印某个哈希桶内的元素
 * 
 * @param index 
 */
void Hash::PrintItemsInIndex(int index)
{
    item *p = hashTable[index];
    if (p->name == "empty")
    {
        cout << "index = " << index << " is empty" << endl;
    }
    else
    {
        cout << "index "
             << index
             << " contains the following items\n"
             << endl;

        while (p)
        {
            cout << p->name << ", " << p->drink << endl;
            p = p->next;
        }
    }
}

/**
 * @brief 查找某人的信息，通过 name（key）作哈希变换直接定位编号
 * 
 * @param name 
 */
void Hash::FindDrink(string name)
{

    int index = hashFunction(name);
    bool findname = false;

    string drink;
    item *p = hashTable[index];
    while (p)
    {
        if (p->name == name)
        {
            findname = true;
            drink = p->drink;
        }
        p = p->next;
    }
    if (findname)
    {
        cout << "find drink: " << drink << endl;
    }
    else
    {
        cout << name << " is not found" << endl;
    }
}

/**
 * @brief 删除某人信息
 * 
 * @param name 
 */
void Hash::RemoveItem(string name)
{
    int index = hashFunction(name);

    item *delPtr;
    item *p1;
    item *p2;

    //  哈希桶为空
    if (hashTable[index]->name == "empty" &&
        hashTable[index]->drink == "empty")
    {
        cout << name << " was not found in the hash table" << endl;
    }
    else if (hashTable[index]->name == name &&
             !hashTable[index]->next)
    {
        hashTable[index]->name = "empty";
        hashTable[index]->drink = "empty";
        cout << name << " was removed succeed" << endl;
    }
    else if (hashTable[index]->name == name)
    {
        delPtr = hashTable[index];
        hashTable[index] = hashTable[index]->next;
        delete delPtr;
        cout << name << " was removed succeed" << endl;
    }
    else
    {
        p1 = hashTable[index]->next;
        p2 = hashTable[index];

        while (p1 && p1->name != name)
        {
            p2 = p1;
            p1 = p1->next;
        }

        if (!p1)
        {
            cout << name << " was not found in the hash table" << endl;
        }
        else
        {
            delPtr = p1;
            p1 = p1->next;
            p2->next = p1;
            delete delPtr;
            cout << name << " was removed succeed" << endl;
        }
    }
}

void listChoice()
{
    cout << "-------------------------" << endl;
    cout << "please choose a operation" << endl;
    cout << "1，增加元素 "
         << "2，删除元素 "
         << "3，打印哈希表使用情况 "
         << "4，打印某个桶的元素 "
         << "5，查找指定元素"
         << endl;
}

int main()
{
    //  选择操作
    int select = 0;

    int show = 0;

    Hash hs1;
    string name1 = " ";
    string drink1 = " ";

    hs1.AddItem("myc", "可乐");
    hs1.AddItem("mcy", "雪碧");
    hs1.AddItem("ycm", "奶茶");
    hs1.AddItem("ymc", "咖啡");

    listChoice();
    while (cin >> select)
    {
        system("clear");
        switch (select)
        {
        case 1:
        {
            cout << "add a new pair" << endl;
            cin >> name1;
            cin >> drink1;
            hs1.AddItem(name1, drink1);
            break;
        }
        case 2:
        {
            cout << "remove a element" << endl;
            cin >> name1;
            hs1.RemoveItem(name1);
            break;
        }
        case 3:
        {
            cout << "printHashTable" << endl;
            hs1.PrintTable();
            break;
        }
        case 4:
        {
            cout << "printHashTable[i]" << endl;
            cin >> show;
            hs1.PrintItemsInIndex(show);
            break;
        }
        case 5:
        {
            cout << "which one u want to find ?" << endl;
            cin >> name1;
            hs1.FindDrink(name1);
            break;
        }
        default:
            break;
        }
        listChoice();
    }

    //cout << "printTable:" << endl;
    //hs1.PrintTable();
    //cout << "printItemsInIndex(0)" << endl;
    //hs1.PrintItemsInIndex(0)；
    // while(name != "quit"){
    //     cout << "please enter a name :" << endl;
    //     cin >> name;

    //     if(name != "quit"){
    //         hs1.FindDrink(name);
    //     }
    // }
    // while (name != "quit")
    // {
    //     cout << "plesae enter a name to remove :" << endl;
    //     cin >> name;

    //     if(name != "quit"){
    //         hs1.RemoveItem(name);
    //     }
    // }
}