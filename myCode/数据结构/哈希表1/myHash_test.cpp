#include <iostream>
#include <iostream>
#include "myHash.hpp"
#include <map>
#include <unordered_map>

/**
 * @brief 
 * 哈希算法：
 *          
 */
using namespace std;

void test01(){
    char str[] = "myc";
    HashTable *table = new HashTable();
    table->Insert(str, 1);
}

int main(){
/*    
    unordered_map<string, int> map;
    map.insert(make_pair("myc", 23));
    cout << map["myc"] << endl;
    */

test01();
}