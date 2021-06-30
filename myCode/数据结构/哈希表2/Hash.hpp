#ifndef C92C7D0C_FF73_4D63_A012_C9C9DA1663ED
#define C92C7D0C_FF73_4D63_A012_C9C9DA1663ED

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Hash
{
private:
    /* data */
    struct item
    {
        string name;
        string drink;
        item *next;

        item():name("empty"), drink("empty"), next(nullptr){}
        item(string n, string d):name(n), drink(d), next(nullptr){}
    };

    static const int tableSize = 16;
    item *hashTable[tableSize];

public:
    Hash();
    ~Hash();
    int hashFunction(string key);
    void AddItem(string name, string drink);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    void FindDrink(string name);
    void RemoveItem(string name);
};

#endif /* C92C7D0C_FF73_4D63_A012_C9C9DA1663ED */
