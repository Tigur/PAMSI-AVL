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
    Tree* root=0;
    type key;
    Tree* leftSon=0;
    Tree* rightSon=0;
    Tree* father=0;

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

    Tree* findPlace (type key)
    {

    }

    bool insert (Tree* newleaf)
    {
        Tree* current=0;
        Tree* curPar=0;

        type key;
        newleaf = new Tree;
        newleaf->key=key;
        if(!root)
        {
            newleaf->root= newleaf;
        }
        current = root;
        while (current!=NULL)
        {
            curPar = current;

            if (newleaf->key < current->key)
                current = current->leftSon;
            else
                current = current->rightSon;
        }


        newleaf->father = curPar;

        if(newleaf->key<curPar->key)
            curPar->leftSon=newleaf;
        else
            curPar->rightSon=newleaf;

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