//
//  mySet.h
//  
//
//  Created by Taoran on 9/16/15.
//
//

#ifndef ____mySet__
#define ____mySet__

#include <stdio.h>
#include <iostream>

using namespace std;

template<typename T>
struct elemListNode{
    T elem;
    elemListNode *next;
};


template<typename T>
class mySet {
public:
    elemListNode<T> *elems;
    int size;
    
public:
    mySet();
    
    mySet(T);
    
    void add(T);
    
    void add_elems_of(mySet *);
    
    void remove(T );
    
    void removePos(int );

    void remove_elems_of(mySet<T> *);
    
    mySet* mySetIntersect(mySet *);
    
    mySet* mySetDifference(mySet *);
    
    mySet* mySetUnion(mySet *);
    
    mySet<mySet<T> > smallest_subset(mySet *, mySet *);
    
    bool operator >(const mySet<T>);
    
    bool operator <(const mySet<T>);
    
    friend ostream& operator<<(ostream& out, const mySet<T> &others)
    {
        out << "{";
        elemListNode<T> *temp = others.elems;
        while(temp != NULL)
        {
            out << temp->elem<<" ";
            temp = temp->next;
        }
        
        out << "}";
        
        return out;
    }
    
    void show();
    
};

#endif /* defined(____mySet__) */
