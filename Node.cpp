//
// Created by resolution on 15.03.18.
//
#include<iostream>
using namespace std;


template <typename type>
class Tree
{
private:
    int leftHeight=0;
    int rightHeight=0;


public:
    type key;
    Tree* leftSon;
    Tree* rightSon;
    int balance=rightHeight-leftHeight;
    int height;



    void rotate ()
    {

    }

    int DoBalance ()
    {
        this->balance=rightHeight-leftHeight;
        if (balance<-1||balance>1)
        {
            rotate();
        }
        return balance;
    }



    bool insert (Tree* newleaf, Tree* father)
    {

    }

    bool del (type keyToDel)
    {

    }
    int countElements(Tree root)
    {

    }
    Tree* searchFor(type key)
    {

    }
};