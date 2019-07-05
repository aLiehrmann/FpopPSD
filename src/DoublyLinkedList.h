#ifndef DEF_DOUBLY_LINKED_LIST
#define DEF_DOUBLY_LINKED_LIST

#include "Interval.h"

struct Node2
{
    Interval interval;
    Node2 *next;
    Node2 *previous;    
};

class DoublyLinkedList
{
    private:
        Node2 * sentinel;
        Node2 * current_node;
        int length;
    
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();
        DoublyLinkedList(Interval interval);
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