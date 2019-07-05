#include "DoublyLinkedList.h"
#include "Interval.h"
#include <iostream>

//####### Sort #######////####### Sort #######////####### Sort #######//
//####### Sort #######////####### Sort #######////####### Sort #######//


Node2 *split(Node2 *head)  
{  
    Node2 *fast = head,*slow = head;  
    while (fast->next && fast->next->next)  
    {  
        fast = fast->next->next;  
        slow = slow->next;  
    }  
    Node2 *temp = slow->next;  
    slow->next = NULL; 
    return temp;  
}  


Node2 *merge(Node2 *first, Node2 *second)  
{
    if (!first)
        return second;  
  
    if (!second)
        return first;  

    if (first->interval.Get_begin() < second->interval.Get_begin())  
    {  
        first->next = merge(first->next,second);  
        first->next->previous = first;  
        first->previous = NULL;  
        return first;  
    }  
    else
    {  
        second->next = merge(first,second->next); 
        second->next->previous = second;  
        second->previous = NULL;  
        return second;  
    }  
}  

Node2 * mergeSort(Node2 *head)  
{  
    if (!head || !head->next)
    {
        return head;
    }
    Node2 *second = split(head);  
  
    head = mergeSort(head);  
    second = mergeSort(second);  
    return merge(head,second);  
}


void DoublyLinkedList::Sort()
{
    sentinel->previous->next=NULL;
    sentinel->previous=NULL;
    mergeSort(sentinel);
    this->InitializeCurrentPosition();
    for (int i=0; i<length-1; i++)
    {
        this->Move();
    }
    sentinel->previous = current_node;
    current_node->next=sentinel;
}


//####### constructor #######////####### constructor #######////####### constructor #######//
//####### constructor #######////####### constructor #######////####### constructor #######//
 
DoublyLinkedList::DoublyLinkedList()
{
  sentinel = new Node2();
  sentinel->next = sentinel;
  sentinel->previous = sentinel;
  sentinel->interval = Interval(INT32_MIN,INT32_MAX);
  current_node = sentinel;
  length = 0;
}


//####### Constructor #######////####### Constructor #######////####### Constructor #######//
//####### Constructor #######////####### Constructor #######////####### Constructor #######//


DoublyLinkedList::DoublyLinkedList(Interval interval)
{
    sentinel = new Node2();
    sentinel->interval = Interval(INT32_MIN,INT32_MAX);
    Node2 * n = new Node2();
    n->interval = interval;
    length=1;
    n->next = sentinel;
    sentinel->next = n;
    current_node = n;
}


//####### addNode #######////####### addNode #######////####### addNode #######//
//####### addNode #######////####### addNode #######////####### addNode #######//


void DoublyLinkedList::AddInterval(Interval i)
{   
    Node2 * n = new Node2();
    n->interval = i;
    sentinel->previous->next = n;
    n->previous = sentinel->previous;
    sentinel->previous = n;
    n->next = sentinel;
    length++;
}


//####### deleteNextNodeAndMove #######////####### deleteNextNodeAndMove #######////####### deleteNextNodeAndMove #######//
//####### deleteNextNodeAndMove #######////####### deleteNextNodeAndMove #######////####### deleteNextNodeAndMove #######//


void DoublyLinkedList::DeleteNextIntervalAndMove()
{
    Node2 * n = current_node -> next;
    current_node->next = n->next; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    n->next->previous = current_node;
    delete n;
    length--;
}


//####### initializeCurrentPosition #######////####### initializeCurrentPosition #######////####### initializeCurrentPosition #######//
//####### initializeCurrentPosition #######////####### initializeCurrentPosition #######////####### initializeCurrentPosition #######//


void DoublyLinkedList::InitializeCurrentPosition()
{
    current_node = sentinel->next;
}


//####### moveToNextNode #######////####### moveToNextNode #######////####### moveToNextNode #######//
//####### moveToNextNode #######////####### moveToNextNode #######////####### moveToNextNode #######//


void DoublyLinkedList::Move()
{
  current_node = current_node -> next;
}


//####### SizeOfList #######////####### SizeOfList #######////####### SizeOfList #######//
//####### SizeOfList #######////####### SizeOfList #######////####### SizeOfList #######//


int DoublyLinkedList::Size()
{
  return length;
}


//####### Destructor #######////####### Destructor #######////####### Destructor #######//
//####### Destructor #######////####### Destructor #######////####### Destructor #######//


DoublyLinkedList::~DoublyLinkedList()
{
  for(int i = 0; i < length+1; i++)
  {
    Node2* n = sentinel;
    sentinel = sentinel -> next;
    delete(n);
  }
}


//####### DisplayList #######////####### DisplayList #######////####### DisplayList #######//
//####### DisplayList #######////####### DisplayList #######////####### DisplayList #######//


void DoublyLinkedList::Print()
{
    this->InitializeCurrentPosition();
    for (int i=0; i<length; i++)
    {
        std::cout <<"["<<current_node->interval.Get_begin() <<";"<<current_node->interval.Get_end()<<"]" << "\n";
        this->Move();
    }
}


//####### GetLength #######////####### GetLength #######////####### GetLength #######//
//####### GetLength #######////####### GetLength #######////####### GetLength #######//


bool DoublyLinkedList::Empty()
{
    return length==0;
}


//####### Max #######////####### Max #######////####### Max #######//
//####### Max #######////####### Max #######////####### Max #######//


double DoublyLinkedList::Max()
{
    this->InitializeCurrentPosition();
    double max_temp = INT32_MIN;
    for (int i=0; i<length; i++)
    {
        if (current_node->interval.Get_begin() > max_temp)
        {
            max_temp = current_node->interval.Get_begin();
        }
        this->Move();
    }
    return max_temp;
}


//####### Min #######////####### Min #######////####### Min #######//
//####### Min #######////####### Min #######////####### Min #######//


double DoublyLinkedList::Min()
{
    this->InitializeCurrentPosition();
    double min_temp = INT32_MAX;
    for (int i=0; i<length; i++)
    {
        if (current_node->interval.Get_end() < min_temp)
        {
            min_temp = current_node->interval.Get_end();
        }
        this->Move();
    }
    return min_temp;
}


//####### SortAndMergeInterval #######////####### SortAndMergeInterval #######////####### SortAndMergeInterval #######//
//####### SortAndMergeInterval #######////####### SortAndMergeInterval #######////####### SortAndMergeInterval #######//


void DoublyLinkedList::Merge()
{
    if (!this->Empty())
    {
        this->Sort();
        this->InitializeCurrentPosition();
        int n = length;
        for (int i=0; i<n-1; i++)
        {
            if (current_node->interval.Get_end()>= current_node->next->interval.Get_begin())
            {
                if (current_node->interval.Get_end()< current_node->next->interval.Get_end())
                {
                    current_node->interval.Set_end(current_node->next->interval.Get_end());
                    this->DeleteNextIntervalAndMove();
                }
                else
                {
                    this->DeleteNextIntervalAndMove();
                }
            }
            else
            {
                this->Move();
            }
            
        }
    }
}


//####### IntersectEachElementWith #######////####### IntersectEachElementWith #######////####### IntersectEachElementWith #######//
//####### IntersectEachElementWith #######////####### IntersectEachElementWith #######////####### IntersectEachElementWith #######//


void DoublyLinkedList::IntersectWith(Interval & interval_to_intersect)
{
    current_node = sentinel;
    int n=length;
    for (int i=0; i<n; i++)
    {
        current_node->next->interval &= interval_to_intersect;
        if (current_node->next->interval.IsEmpty_or_singleton())
        {
            this -> DeleteNextIntervalAndMove();
        }
        else
        {
            this -> Move();
        }
    }
}

//####### ComplementaryIn #######////####### ComplementaryIn #######////####### ComplementaryIn #######//
//####### ComplementaryIn #######////####### ComplementaryIn #######////####### ComplementaryIn #######//


void DoublyLinkedList::ComplementaryIn(Interval & d)
{
    if (this->Empty())
    {
        this->AddInterval(d);
    }
    else
    {
        DoublyLinkedList * list_of_complementary_intervals = new DoublyLinkedList();
        this->IntersectWith(d);
        this->InitializeCurrentPosition();
        if (current_node->interval.Get_begin() > d.Get_begin())
        {
            list_of_complementary_intervals->AddInterval(Interval(d.Get_begin(), current_node->interval.Get_begin()));
        }
        for (int i=0; i<length-1; i++)
        {
            list_of_complementary_intervals->AddInterval(Interval(current_node->interval.Get_end(), current_node->next->interval.Get_begin()));
            this->Move();
        }
        if (current_node->interval.Get_end()<d.Get_end())
        {
            list_of_complementary_intervals->AddInterval(Interval(current_node->interval.Get_end(), d.Get_end()));
        }
        for(int i = 0; i < length+1; i++)
        {
        Node2* n = sentinel;
        sentinel = sentinel -> next;
        delete(n);
        }
        sentinel = list_of_complementary_intervals->sentinel;
        length = list_of_complementary_intervals->length;
        list_of_complementary_intervals->sentinel=0;
        list_of_complementary_intervals->length=-1;
        delete list_of_complementary_intervals;
    }
}

Interval DoublyLinkedList::Intersect()
{   
    if (this->Empty())
    {
        return Interval(1,-1);
    }
    else
    {
        return Interval(this->Max(), this->Min());
    }
}