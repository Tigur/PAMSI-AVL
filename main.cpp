#include <iostream>
#include "Node.cpp"
using namespace std;
int main ()
{
Tree <int> T;

    T.insert(3);
    T.insert(4);
    T.insert(7);
    T.insert(1);
    T.insert(41);
    T.insert(11);
    T.insert(24);
    T.insert(31);
    T.insert(12);
    T.insert(22);
    T.insert(5);
    T.insert(6);
    T.insert(111);
    T.preorder(T.root);
}
