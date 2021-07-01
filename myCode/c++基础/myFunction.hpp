#ifndef E6BB1535_9F99_4B50_B497_DFD431E45D2D
#define E6BB1535_9F99_4B50_B497_DFD431E45D2D

#include <iostream>
#include <memory>

using namespace std;

template<class T>
void printVal(T* p){
    cout << "address = " << p << " , val = " << *p << endl;
}
template<class T>
void printVal(shared_ptr<T> p){
    cout << "address = " << p << " , val = " << *p << endl;

}

#endif /* E6BB1535_9F99_4B50_B497_DFD431E45D2D */
