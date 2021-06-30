#ifndef C1EEFC0C_CC55_46EE_A9ED_1064FF0A65A1
#define C1EEFC0C_CC55_46EE_A9ED_1064FF0A65A1

#include <iostream>
#define Default_Size 16;
/**
 * @brief 
 *      键（key）：组员的编号
 *      值（value）：组员的信息
 *      索引：数组的下标
 *      哈希桶：保存索引的数组（链表或数组），数组成员为每一个索引值相同的多个元素
 *      哈希函数：将组员变好映射到索引上，采用求余法等
 * @tparam T 
 */
// 节点结构体
typedef struct _ListNode
{
    int key;
    void* data;
    struct _ListNode *next;

} ListNode;

// 链表结构体
typedef ListNode *List;

// 元素结构体
typedef ListNode *Element;

// 哈希表类
class HashTable
{
private:
//  桶个数
    int tableSize;
//  桶链表
    List *HashList;
public:
    HashTable();
    ~HashTable();
    int Hash(int key, int tableSize);
    Element Find(int key);
    
    //template<class T>
    void Insert(void* val, int key);
    
    void Delete(int key);
};

// 构造函数
HashTable::HashTable(){
    int i = 0;
    HashTable *hTable = nullptr;

    if(tableSize <= 0){
        tableSize = Default_Size;
    }

    hTable = (HashTable *)malloc(sizeof(HashTable));

    if(NULL == hTable){
        printf("hashtable malloc error");
        return;
    }

    hTable->tableSize = tableSize;

    hTable->HashList = (List *)malloc(sizeof(List) * tableSize);
    if (NULL == hTable->HashList)
    {
        printf("hashtable malloc error");
        return;
    }
// 为哈希桶对应的指针数组初始化链表节点
    for (int i = 0; i < tableSize; i++){
        hTable->HashList[i] = (ListNode *)malloc(sizeof(ListNode));
        if(NULL == hTable->HashList[i]){
            printf("hashtable malloc error");
            free(hTable->HashList);
            free(hTable);
            return;
        }
        else{
            memset(hTable->HashList[i], 0, sizeof(ListNode));
        }
    }
}

// 哈希操作
int HashTable::Hash(int key, int tableSize){
    return (key & (tableSize - 1));
}

// 查找
Element HashTable::Find(int key){
    int i = 0;
    List L = nullptr;
    Element e = nullptr;
    i = Hash(key, this->tableSize);
    L = this->HashList[i];
    e = L->next;
    while (e && e->key != key)
    {
        e = e->next;
    }
    return e;
}

// 插入
//template<class T>
void HashTable::Insert(void* val, int key){
    Element e = nullptr, tmp = nullptr;
    List L = nullptr;
    e = Find(key);

    if(!e){
        tmp = (Element)malloc(sizeof(ListNode));
        if(!tmp){
            printf("malloc error\n");
            return;
        }
        L = this->HashList[Hash(key, tableSize)];
        tmp->key = key;
        tmp->data = val;
        tmp->next = L->next;
        L->next = tmp;
    }
    else{
        printf("the key already exist");
    }
}

// 删除
void HashTable::Delete(int key){
    Element e = nullptr, last = nullptr;
    List L = nullptr;

    int i = Hash(key, this->tableSize);
    L = this->HashList[i];

    last = L;
    e = L->next;
    while(e && e->key != key){
        last = e;
        e = e->next;
    }

    if(e){
        last->next = e->next;
        free(e);
    }
}

#endif /* C1EEFC0C_CC55_46EE_A9ED_1064FF0A65A1 */
