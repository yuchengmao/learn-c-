#include <iostream>
#include "threadPool.hpp"

using namespace std;

int main()
{
    ThreadPool *pool = new ThreadPool;
    createPool(1, 1, 2);
}