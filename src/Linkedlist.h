#ifndef DEF_LINKEDLIST
#define DEF_LINKEDLIST

#include "Interval.h"

struct Node
{
    Interval interval;
    Node *next;
    Node *previous;    
};

class Linkedlist
{
private:
    Node *head, *tail;
    int length;
public:
    Linkedlist();
    Linkedlist(Interval l);
    ~Linkedlist();
    //static Node * mergeSort(Node * head);
    void Push_back(Interval interval);
    int Size();
    void Sort();
    Node * Front();
    Node * Back();
    double Max();
    double Min();
    bool Empty();
    void Merge();
    Node * Erase(Node * node_to_erased);
    void Update_tail();
    void Update_head();
    void Print();
    void Intersect_with(Interval & interval_to_intersect);
    void Complementary_in(Interval & d);
    Interval Intersect();
};

#endif