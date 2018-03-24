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
    type key=NULL;
    Tree* leftSon=0;
    Tree* rightSon=0;
    Tree* father=0;
    const Tree* OmniTree=0;

    int balance=rightHeight-leftHeight;
    int height=0;


    void preorderRootUpdate(Tree* Node, Tree* newRoot) // zamiast tego preorder, update root, wstawic to do Rotacji
    {
        cout << Node->key << endl;
        root=newRoot;
        if(Node->leftSon)
            preorderRootUpdate(Node->leftSon,newRoot);
        if(Node->rightSon)
            preorderRootUpdate(Node->rightSon, newRoot);


    }



    void updateBalance(Tree* startLeaf)
    {
        Tree* current = startLeaf;
        while (current!=NULL && current->father!=NULL) // keep an eye on this
        {
            //current->DoBalance(current);
            if(current->key<current->father->key)
            {

                current->father->balance -= 1;
                current->father->DoBalance(current);
            }
            else
            {
                current->father->balance += 1;
                current->father->DoBalance(startLeaf); // było current father
            }

            current=current->father;
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

        if(a==root)
        {
            preorderRootUpdate(b,b);
        }

        if(b->balance>0) // Nigdy nie powinien wychodzić ujemny balance dla b w tej rotacji
        {
            a->balance=0;
            b->balance=0;

        }
        else
        {
            a->balance=  1;
            b->balance= -1;
        }


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

        if(a==root)
        {
            preorderRootUpdate(b,b);
        }

        if(b->balance<0) // Nigdy nie powinien wychodzić dodatni balance dla b w tej rotacji
        {
            a->balance=0;
            b->balance=0;

        }
        else
        {
            a->balance=-1;
            b->balance= 1;
        }
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


        if(a==root)
        {
            preorderRootUpdate(c,c);
        }

        if(c->balance>0)
        {
            a->balance=1;
            b->balance=0;
            c->balance=0;

        }
        if(c->balance<0)
        {
            a->balance=0;
            b->balance=-1;
            c->balance=0;
        }
        if(c->balance==0)
        {
            a->balance=0;
            b->balance=0;
            c->balance=0;
        }


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


        if(a==root)
        {
            preorderRootUpdate(c,c);

        }


        if(c->balance<0)
        {
            a->balance=-1;
            b->balance=0;
            c->balance=0;

        }
        if(c->balance>0)
        {
            a->balance=0;
            b->balance=1;
            c->balance=0;
        }
        if(c->balance==0)
        {
            a->balance=0;
            b->balance=0;
            c->balance=0;
        }

    }

    void rotate (Tree* addedLeaf)
    {

        // define which rotation, anker to the new cell
        if(addedLeaf->key < this->key && this->leftSon && addedLeaf->key < this->leftSon->key)
        {
            LLrot();
        }
        if(addedLeaf->key > this->key && this->rightSon && addedLeaf->key > this->rightSon->key)
        {
            RRrot();
        }
        if(addedLeaf->key > this->key && this->rightSon && addedLeaf->key < this->rightSon->key)
        {
            RLrot();
        }
        if(addedLeaf->key < this->key && this->leftSon && addedLeaf->key > this->leftSon->key)
        {
            LRrot();
        }

    }

    int DoBalance (Tree* addedLeaf)
    {
        //this->balance=rightHeight-leftHeight;
        if (balance<-1||balance>1)
        {
            cout << "robie rotacje od wezła "<< this->key<< endl;
            rotate( addedLeaf);

            //cout << "robie rotacje od wezła "<< this->key<< endl;
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
            root=newleaf;
            newleaf->root= newleaf;
            //root->father=this; // zmiana powazna
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
            newleaf->root = curPar->root;

            if (newleaf->key < curPar->key) {
                curPar->leftSon = newleaf;
                updateBalance(newleaf);
                // curPar->leftHeight+=1;
            } else {
                curPar->rightSon = newleaf;
                updateBalance(newleaf);

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