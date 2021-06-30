#include <iostream>

using namespace std;

class Child;
class Parent
{
private:
    shared_ptr<Child> ChildPtr;
public:
    Parent(/* args */) {}
    ~Parent() {}

    void setChild(shared_ptr<Child> child){
        ChildPtr = child;
    }
};

class Child
{
private:
    shared_ptr<Parent> ParentPtr;
public:
    Child(/* args */) {}
    ~Child() {}

    void setParent(shared_ptr<Parent> parent){
        ParentPtr = parent;
    }
};
int main(){

    weak_ptr<Parent> pa;
    weak_ptr<Child> ch;

    shared_ptr<Parent> p(new Parent);
    shared_ptr<Child> c(new Child);

    p->setChild(c);
    c->setParent(p);

    cout << p.use_count() << endl;
    cout << c.use_count() << endl;
}