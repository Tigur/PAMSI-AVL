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
    int height=0;


    void updateBalance(Tree* startLeaf)
    {
        Tree* current = startLeaf;
        while (current!=NULL) // keep an eye on this
        {
            current->DoBalance(startLeaf);
            if(current->key<current->father->key)
                current->rightHeight+=1;
            else
                current->leftHeight+=1;
        }
    }


    void RRrot()
    {
        Tree *a,*b,*c;// from top to bottom
        Tree *tmp;

        a=this;
        b=a->rightSon;
        c=b->rightSon;

        tmp=b->leftSon;
        b->leftSon=a;
        b->father=a->father;
        a->father=b;
        a->rightSon=tmp;


    }
    void LLrot()
    {
        Tree *a,*b,*c;// from top to bottom
        Tree *tmp;

        a=this;
        b=a->leftSon;
        c=b->leftSon;

        tmp=b->rightSon;
        b->rightSon=a;
        b->father=a->father;
        a->father=b;
        a->leftSon=tmp;
    }

    void RLrot()
    {
        Tree *a,*b,*c;// from top to bottom
        Tree *tmp;

        a=this;
        b=a->rightSon;
        c=b->leftSon;

        tmp=c->rightSon;
        c->rightSon=b;
        c->father=a->father;
        b->leftSon=tmp;
        tmp=c->leftSon;
        c->leftSon=a;
        a->rightSon=tmp;
        a->father=c;
        b->father=c;
    }
    void LRrot()
    {
        Tree *a,*b,*c;// from top to bottom
        Tree *tmp;

        a=this;
        b=a->leftSon;
        c=b->rightSon;

        tmp=c->leftSon;
        c->leftSon=b;
        c->father=a->father;
        b->rightSon=tmp;
        tmp=c->rightSon;
        c->rightSon=a;
        a->leftSon=tmp;
        a->father=c;
        b->father=c;
    }

    void rotate (Tree* addedLeaf)
    {

        // define which rotation, anker to the new cell
        if(addedLeaf->key < this->key && addedLeaf->key < this->leftSon->key)
        {
            LLrot();
        }
        if(addedLeaf->key > this->key && addedLeaf->key > this->leftSon->key)
        {
            RRrot();
        }
        if(addedLeaf->key > this->key && addedLeaf->key < this->leftSon->key)
        {
            RLrot();
        }
        if(addedLeaf->key < this->key && addedLeaf->key > this->leftSon->key)
        {
            LRrot();
        }

    }

    int DoBalance (Tree* addedLeaf)
    {
        this->balance=rightHeight-leftHeight;
        if (balance<-1||balance>1)
        {
            rotate( addedLeaf);
        }
        return balance;
    }

    Tree* findPlace (type key)
    {

    }

    bool insert (type key) // DEL bedzie miało inne update !!
    {
        Tree* current=0; // pointer to iterate
        Tree* curPar=0; // supposed parent

        Tree *newleaf;
        //type key;
        newleaf = new Tree;
        newleaf->key=key;
        if(!root)
        {
            newleaf->root= newleaf;
        }
        else {
            current = root;
            while (current != NULL)
            {
                curPar = current;

                if (newleaf->key < current->key)
                {
                    current = current->leftSon;

                }
                else
                {
                    current = current->rightSon;
                }
            }


            newleaf->father = curPar;

            if (newleaf->key < curPar->key) {
                curPar->leftSon = newleaf;
                updateBalance(curPar);
                // curPar->leftHeight+=1;
            } else {
                curPar->rightSon = newleaf;
                updateBalance(curPar);

                //curPar->rightHeight+=1;
            }
        }
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