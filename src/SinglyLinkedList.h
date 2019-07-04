#ifndef DEF_SINGLY_LINKED_LIST
#define DEF_SINGLY_LINKED_LIST

#include "Interval.h"

struct SinglyNode
{
    Interval interval;
    SinglyNode *next;
};

class SinglyLinkedList
{
    private:
        SinglyNode * sentinel;
        SinglyNode * current_node;
        int length;
    
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();
        SinglyLinkedList(Interval interval);
        void AddInterval(Interval interval);
        void DeleteNextIntervalAndMove();
        void InitializeCurrentPosition();
        void Print();
        void Sort();
        void Move();
        bool Empty();
        void Merge();
        double Max();
        double Min();
        void IntersectWith(Interval & interval_to_intersect);
        void ComplementaryIn(Interval & d);
        int Size();
        Interval Intersect();
};


#endif