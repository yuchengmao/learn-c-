#include <iostream>
#include <memory>

using namespace std;

struct binaryTree
{
    /* data */
    void* data;
    binaryTree *left;
    binaryTree *right;

    binaryTree() {}
    binaryTree(void* val) : data(val) {}
    binaryTree(void* val, binaryTree* left, binaryTree* right) : data(val), left(left), right(right) {} 
};

int main()
{
    shared_ptr<binaryTree> root = make_shared<binaryTree>((void*)"hello");

    cout << static_cast<char *>(root->data) << endl;
    
}