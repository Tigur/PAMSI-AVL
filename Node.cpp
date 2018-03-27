//
// Created by resolution on 15.03.18.
//
#include<iostream>
#include <cstdlib>
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
        Node->root=newRoot;
        if(Node->leftSon)
            preorderRootUpdate(Node->leftSon,newRoot);
        if(Node->rightSon)
            preorderRootUpdate(Node->rightSon, newRoot);


    }
    void preorder(Tree* Node) // zamiast tego preorder, update root, wstawic to do Rotacji
    {
        cout << Node->key << endl;

        if (Node->leftSon) {
            cout << "LEFT of " << Node->key << endl;
            preorder(Node->leftSon);
        }
        if (Node->rightSon) {
            cout << "RIGHT of " << Node->key << endl;
            preorder(Node->rightSon);
        }

    }

    void postorder(Tree* Node) // zamiast tego preorder, update root, wstawic to do Rotacji
    {


        if (Node->leftSon) {
            cout << "LEFT of " << Node->key << endl;
            postorder(Node->leftSon);
        }
        if (Node->rightSon) {
            cout << "RIGHT of " << Node->key << endl;
            postorder(Node->rightSon);
        }
        cout << Node->key << endl;
    }

    void inorder(Tree* Node) // zamiast tego preorder, update root, wstawic to do Rotacji
    {


        if (Node->leftSon) {
            cout << "LEFT of " << Node->key << endl;
            postorder(Node->leftSon);
        }

        cout << Node->key << endl;

        if (Node->rightSon) {
            cout << "RIGHT of " << Node->key << endl;
            postorder(Node->rightSon);
        }

    }



    void ImpulseSubstract(Tree *startLeaf)
    {
        Tree* current = startLeaf;
        Tree* toBalance=0; // Wskaźnik pokazujący pierwszy niezbalansowany wierzchołek





        while (current!=NULL && current->father!=NULL) // keep an eye on this
        {
            //current->DoBalance(current);
            if(current->key < current->father->key)
            {

                current->father->balance += 1;
                if(current->father->DoBalance(&toBalance))
                {
                    Tree* SonOfRot = toBalance->rotate(startLeaf); // Czy zadziałą ?  na szaro, bo 0 ??
                    ImpulseSubstract(SonOfRot->father);// Tu odejmowanie od ojca. rotacji
                    current=SonOfRot;
                    toBalance=0;
                }
            }
            else
            {
                current->father->balance -= 1;
                if(current->father->DoBalance(&toBalance))
                {
                    Tree* SonOfRot = toBalance->rotate(startLeaf); // Czy zadziałą ?  na szaro, bo 0 ??
                    ImpulseSubstract(SonOfRot->father);// Tu odejmowanie od ojca. rotacji
                    current=SonOfRot;
                    toBalance=0;
                }
            }

            current=current->father;
        }
        /*
        if(toBalance)
        {
            Tree* fatherOfRot = toBalance->rotate(startLeaf); // Czy zadziałą ?  na szaro, bo 0 ??
            ImpulseSubstract(fatherOfRot);// Tu odejmowanie od ojca. rotacji
        }
         */
    }


    void ImpulseAdd(Tree *startLeaf)
    {
        Tree* current = startLeaf;
        Tree* toBalance=0; // Wskaźnik pokazujący pierwszy niezbalansowany wierzchołek




        while (current!=NULL && current->father!=NULL) // keep an eye on this
        {
            //current->DoBalance(current);
            if(current->key<current->father->key)
            {

                current->father->balance -= 1;
                if(current->father->DoBalance(&toBalance))
                {
                    Tree* SonOfRot = toBalance->rotate(startLeaf); // Czy zadziałą ?  na szaro, bo 0 ??
                    ImpulseSubstract(SonOfRot->father);// Tu odejmowanie od ojca. rotacji
                    current=SonOfRot;
                    toBalance=0;
                }
            }
            else
            {
                current->father->balance += 1;
                if(current->father->DoBalance(&toBalance))
                {
                    Tree* SonOfRot = toBalance->rotate(startLeaf); // Czy zadziałą ?  na szaro, bo 0 ??
                    ImpulseSubstract(SonOfRot->father);// Tu odejmowanie od ojca. rotacji
                    current=SonOfRot;
                    toBalance=0;
                }
            }

            current=current->father;
        }
        /*
        if(toBalance)
        {
            Tree* fatherOfRot = toBalance->rotate(startLeaf); // Czy zadziałą ?  na szaro, bo 0 ??
            ImpulseSubstract(fatherOfRot);// Tu odejmowanie od ojca. rotacji
        }
         */
    }


    Tree* RRrot()
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


        if(b->father && b->father->key>b->key) // Gdy rotacja jest w środku drzewa, potrzeba ustanowić nowego syna dla najwyższego wezła.
            b->father->leftSon=b;
        if(b->father && b->father->key<b->key)
            b->father->rightSon=b;

        if(a==root)
        {
            b->root=b;
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

        return a;

    }
    Tree* LLrot()
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

        if(b->father && b->father->key>b->key)
            b->father->leftSon=b;
        if(b->father && b->father->key<b->key)
            b->father->rightSon=b;

        if(a==root)
        {
            b->root=b;
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

        return a;
    }

    Tree* RLrot()
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

        if(c->father && c->father->key>c->key)
            c->father->leftSon=c;
        if(c->father && c->father->key<c->key)
            c->father->rightSon=c;

        if(a==root)
        {
            c->root=c;
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

        return a;

    }
    Tree* LRrot()
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

        if(c->father && c->father->key>c->key)
            c->father->leftSon=c;
        if(c->father && c->father->key<c->key)
            c->father->rightSon=c;

        if(a==root)
        {
            c->root=c;
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

        return a;

    }

    Tree* rotate (Tree* addedLeaf)
    {
        cout << " wchodzę do rotate " << this->key << endl;
        // define which rotation, anker to the new cell
        if(this->balance<0 && this->leftSon->balance<=0)
        {
           Tree* fatherOfRot = LLrot();
           return fatherOfRot;
        }
        if(this->balance>0 && this->rightSon->balance>=0)
        {
            Tree* fatherOfRot = RRrot();
            return fatherOfRot;
        }
        if(this->balance>0 && this->rightSon->balance<0)
        {
            Tree* fatherOfRot = RLrot();
            return fatherOfRot;
        }
        if(this->balance<0 && this->leftSon->balance>0)
        {
            Tree* fatherOfRot = LRrot();
            return fatherOfRot;
        }

        return 0;

    }
    /*
    Tree* rotate (Tree* addedLeaf)
    {
        cout << " wchodzę do rotate " << this->key << endl;
        // define which rotation, anker to the new cell
        if(addedLeaf->key < this->key && this->leftSon && addedLeaf->key < this->leftSon->key)
        {
            Tree* fatherOfRot = LLrot();
            return fatherOfRot;
        }
        if(addedLeaf->key > this->key && this->rightSon && addedLeaf->key > this->rightSon->key)
        {
            Tree* fatherOfRot = RRrot();
            return fatherOfRot;
        }
        if(addedLeaf->key > this->key && this->rightSon && addedLeaf->key < this->rightSon->key)
        {
            Tree* fatherOfRot = RLrot();
            return fatherOfRot;
        }
        if(addedLeaf->key < this->key && this->leftSon && addedLeaf->key > this->leftSon->key)
        {
            Tree* fatherOfRot = LRrot();
            return fatherOfRot;
        }

        return 0;

    }
     */

    Tree* DoBalance (Tree** toBalance)
    {
        //this->balance=rightHeight-leftHeight;
        if (balance<-1||balance>1)
        {
            //cout << "robie rotacje od wezła "<< this->key<< endl;
           // rotate( addedLeaf);
            //cout << "robie rotacje od wezła "<< this->key<< endl;
            //Obsolite ^

            *toBalance=this;

            return *toBalance;
        }
        return 0;
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
            return true;
        }


        root=root->root;
        //newleaf->root=root->root;
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

        if (newleaf->key < curPar->key)
        {
            curPar->leftSon = newleaf;

            if(curPar->rightSon)
            {
                curPar->balance-=1;
                return true;
            }

            ImpulseAdd(newleaf);
        }
        else
        {
            curPar->rightSon = newleaf;

            if(curPar->leftSon)
            {
                curPar->balance+=1;
                return true;
            }

            ImpulseAdd(newleaf);
        }
        return true;
    }


    bool del (type keyToDel)
    {


        Tree* Node = searchFor(keyToDel,root);
        if(!Node)
        {
            cout << "coś nie tak !! " << endl;
            return false;
        }

        if(Node->rightSon||Node->leftSon)
        {
            cout << "This is not a leaf !! " << endl;
            return false;
        }


        if(Node->father->rightSon && Node->father->leftSon) // jeżeli wysokość sie nei zmienia
        {
            if(Node->key < Node->father->key)
            {

                Node->father->balance += 1;
                //Node->father->DoBalance(&toBalance);
                Node->father->leftSon=0;
                Node->father=0;
                delete Node;
            }
            else
            {
                Node->father->balance -= 1;
               // Node->father->DoBalance(&toBalance); // było current father
                Node->father->rightSon=0;
                Node->father=0;
                delete Node;


            }
            return true;
        }


        if(Node->father->key>Node->key)
        {
            Node->father->leftSon=0;
        }
        else
        {
            Node->father->rightSon=0;
        }


        ImpulseSubstract(Node);
        Node->father=0;
        delete Node;

        return true;

    }
    int GiveHeight(Tree* root)
    {
        if (!root)
        {
            return -1;
        }

        int leftH= GiveHeight(root->leftSon);
        int rightH= GiveHeight(root->rightSon);

        return ((rightH+leftH)/2)+ (abs(rightH-leftH)) +1; // return bigger one +1
    }
    Tree* searchFor(type key, Tree* Node)
    {
        while (Node!=NULL && Node->key!=key)
        {
            if(key<Node->key)
            {
                Node=Node->leftSon;

            }
            else
            {
                Node=Node->rightSon;
            }
            if(!Node)
                cout << "Don't have any !!!" << endl;


        }
        return Node;
    }
};