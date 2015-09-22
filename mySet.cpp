//
//  mySet.cpp
//  
//
//  Created by Taoran on 9/16/15.
//
//

#include "mySet.h"
#include <iostream>

using namespace std;

template<typename T>
mySet<T>::mySet(){
    elems = NULL;
    size = 0;
}


template<typename T>
mySet<T>::mySet(T newElem){
    elems = new elemListNode<T>;
    elems->elem = newElem;
    elems->next = NULL;
    size = 1;
}

template<typename T>
void mySet<T>::add(T newElem){
    
    elemListNode<T> *newElemNode = new elemListNode<T>;

    newElemNode->elem = newElem;
    
    if(elems == NULL)
    {
        elems = newElemNode;
        size = size + 1;
        return;
    }
    
    if(elems->elem > newElem)
    {
        newElemNode->next = elems;
        elems = newElemNode;
        size = size + 1;
        return;
    }
    
    elemListNode<T> *prev = elems;
    elemListNode<T> *temp = elems;
    
    for(int i=0; i< size; ++i)
    {
        if(temp->elem < newElem)
        {
            prev = temp;
            temp = temp->next;

        }
        else if(temp->elem > newElem)
        {
            prev->next = newElemNode;
            newElemNode->next = temp;
            size = size + 1;
            return;
        }
        else
        {
            return;
        }
    }

    if(temp == NULL)
    {
        prev->next = newElemNode;
        newElemNode->next = NULL;
    }
    size = size + 1;
    return;
}

template<typename T>
void mySet<T>::add_elems_of(mySet *others){
    
    elemListNode<T> *temp = new elemListNode<T>;
    temp = others->elems;
    while(temp!=NULL)
    {
        this->add(temp->elem);
        temp = temp->next;
    }
}

template<typename T>
void mySet<T>::remove(T oldElem){
    
    if(elems == NULL) return;
    if(elems->elem == oldElem)
    {
        elems = elems->next;
        size = size-1;
        return;
    }
    
    elemListNode<T> *prev = elems;
    elemListNode<T> *temp = elems->next;

    while(temp != NULL)
    {

        if(temp->elem == oldElem){
            prev->next = temp->next;
            size = size - 1;
            return;
        }
        prev = prev->next;
        temp = temp->next;
    }

}

template<typename T>
void mySet<T>::removePos(int pos){
    
    if(elems == NULL || pos >= size || pos < 0) return;

    if(pos == 0){
        elems = elems->next;
        size = size -1;
        return;
    }
    
    if(size == 1) return;
    
    elemListNode<T> *prev = elems;
    elemListNode<T> *temp = elems->next;

    for(int i=1; i<size; ++i)
    {
        if(pos == i)
        {
            prev->next = temp->next;
            size = size -1;
            return;
        }
        prev = prev->next;
        temp = temp->next;
    }
 }

template<typename T>
void mySet<T>::remove_elems_of(mySet<T> *others){
    
    elemListNode<T> *temp = others->elems;
    while(temp != NULL && elems != NULL){
        this->remove(temp->elem);

        temp = temp->next;
    }
    
}


template<typename T>
mySet<T>* mySet<T>::mySetIntersect(mySet<T> *others){
    mySet<T> *res = new mySet<T>();
    
    if(elems == NULL || others->elems == NULL)
    {
        return res;
    }
    
    elemListNode<T> *temp1;
    elemListNode<T> *temp2;
    elemListNode<T> *temp3;
    int sizeTemp1;
    int sizeTemp2;
    
    if(size < others->size)
    {
        temp2 = elems;
        sizeTemp2 = size;
        
        temp1 = others->elems;
        sizeTemp1 = others->size;
    }
    else
    {
        temp1 = elems;
        sizeTemp1 = size;
        
        temp2 = others->elems;
        sizeTemp2 = others->size;
    }
    
    temp3 = temp2;
    while(temp1 != NULL)
    {
        
        while(temp2 != NULL)
        {
            if(temp1->elem == temp2->elem)
            {
                
                res->add(temp1->elem);
                break;
            }
            temp2 = temp2->next;
        }

        temp2 = temp3;
        temp1 = temp1->next;
    }
    
    return res;
}


template<typename T>
mySet<T>* mySet<T>::mySetDifference(mySet<T> *others){
    
    mySet<T> *res = new mySet<T>;
    elemListNode<T> *temp;
    elemListNode<T> *temp1 = elems;
    elemListNode<T> *temp2 = others->elems;
    temp = temp2;
    bool exist = false;
    while(temp1!=NULL)
    {
        while(temp2!=NULL)
        {
            if(temp1->elem == temp2->elem)
            {
                exist = true;
                break;
            }
            temp2 = temp2->next;
        }
        if(!exist)
        {
            res->add(temp1->elem);
        }
        exist = false;
        temp2 = temp;
        temp1 = temp1->next;
    }
    return res;
}


template<typename T>
mySet<T> *mySet<T>::mySetUnion(mySet *others)
{
    mySet<T> *res = new mySet<T>();
    elemListNode<T> *temp = new elemListNode<T>;
    
    temp = elems;
    while(temp!=NULL)
    {
        res->add(temp->elem);
        temp = temp->next;
    }
    
    temp = others->elems;
    while(temp!=NULL)
    {
        res->add(temp->elem);
        temp = temp->next;
    }
    return res;
}

template<typename T>
mySet<mySet<T> > mySet<T>::smallest_subset(mySet<T> *s2, mySet<T> *s3){
    
    mySet<mySet<T> > res = mySet<mySet<T> >();
    
    mySet<T> *res0 = this->mySetIntersect(s2)->mySetIntersect(s3);
    mySet<T> *res1 = this->mySetIntersect(s2)->mySetDifference(res0);
    mySet<T> *res2 = this->mySetIntersect(s3)->mySetDifference(res0);
    mySet<T> *res3 = s2->mySetIntersect(s3)->mySetDifference(res0);
    mySet<T> *res4 = this->mySetDifference(s2)->mySetDifference(s3);
    mySet<T> *res5 = s2->mySetDifference(this)->mySetDifference(s3);
    mySet<T> *res6 = s3->mySetDifference(this)->mySetDifference(s2);
    res.add(*res0);
    res.add(*res1);
    res.add(*res2);
    res.add(*res3);
    res.add(*res4);
    res.add(*res5);
    res.add(*res6);
    
    return res;
    
}

template<typename T>
bool mySet<T>::operator >(const mySet<T> others){
    return true;
}

template<typename T>
bool mySet<T>::operator <(const mySet<T> others){
    return false;
}


template<typename T>
void mySet<T>::show(){
    
    elemListNode<T> *temp = elems;
    for(int i=0; i<size; ++i)
    {
        if(temp != NULL)
        {
            cout<< temp->elem<< " ";
        }
        temp = temp->next;
    }
    cout << endl;
}

int main(int argc,char** argv)
{
    
    mySet<int> *s1 = new mySet<int>(0);
    mySet<int> *s2 = new mySet<int>(0);
    mySet<int> *s3 = new mySet<int>(0);
    mySet<mySet<int> > s4;
    
    
    s1->add(1);
    s1->add(2);
    s1->add(4);
    
    cout<< "s1: "<< *s1<< endl;
    
    s2->add(1);
    s2->add(3);
    s2->add(6);
    
    cout<< "s1: "<< *s2<< endl;
    
    s3->add(2);
    s3->add(3);
    s3->add(5);
    
    cout<< "s1: "<< *s3<< endl;
    
    s4 = s1->smallest_subset(s2, s3);
    
    cout<< "s4: "<< s4<< endl;
    
    delete s1;
    delete s2;
    delete s3;
    
    
    return 0;
    
}
