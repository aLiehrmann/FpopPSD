#include "SinglyLinkedList.h"
#include "Interval.h"
#include <iostream>


//####### SortList #######////####### SortList #######////####### SortList #######//
//####### SortList #######////####### SortList #######////####### SortList #######//


SinglyNode* SortedMerge(SinglyNode* a, SinglyNode* b); 
void FrontBackSplit(SinglyNode* source, SinglyNode** frontRef, SinglyNode** backRef); 
  
void MergeSort(SinglyNode ** headRef) 
{ 
    SinglyNode* head = *headRef; 
    SinglyNode* a; 
    SinglyNode* b; 
  
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
    FrontBackSplit(head, &a, &b); 
    MergeSort(&a); 
    MergeSort(&b); 
    *headRef = SortedMerge(a, b); 
}

SinglyNode* SortedMerge(SinglyNode* a, SinglyNode* b) 
{ 
    SinglyNode* result = NULL; 
  
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    if (a->interval.Get_begin() <= b->interval.Get_begin()) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return (result); 
} 

void FrontBackSplit(SinglyNode* source, 
                    SinglyNode** frontRef, SinglyNode** backRef) 
{ 
    SinglyNode* fast; 
    SinglyNode* slow; 
    slow = source; 
    fast = source->next; 
  
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 

void SinglyLinkedList::Sort()
{
    MergeSort(&sentinel);
}


//####### Constructor #######////####### Constructor #######////####### Constructor #######//
//####### Constructor #######////####### Constructor #######////####### Constructor #######//


SinglyLinkedList::SinglyLinkedList()
{
    sentinel = new SinglyNode();
    sentinel->next = NULL;
    sentinel->interval = Interval(INT32_MIN,0);
    length=0;
    current_node = sentinel;
}


//####### Constructor #######////####### Constructor #######////####### Constructor #######//
//####### Constructor #######////####### Constructor #######////####### Constructor #######//


SinglyLinkedList::SinglyLinkedList(Interval interval)
{
    sentinel = new SinglyNode();
    sentinel->next = NULL;
    sentinel->interval = Interval(INT32_MIN,0);
    SinglyNode * n = new SinglyNode();
    n->interval = interval;
    length=1;
    n->next = sentinel->next;
    sentinel->next = n;
    current_node = n;
    n=0;
}


//####### AddInterval #######////####### AddInterval #######////####### AddInterval #######//
//####### AddInterval #######////####### AddInterval #######////####### AddInterval #######//


void SinglyLinkedList::AddInterval(Interval interval)
{
    SinglyNode * n = new SinglyNode();
    n->interval = interval;
    length++;
    n->next = sentinel->next;
    sentinel->next = n;
    n=0;
}


//####### PrintList #######////####### PrintList #######////####### PrintList #######//
//####### PrintList #######////####### PrintList #######////####### PrintList #######//


void SinglyLinkedList::Print()
{
    SinglyNode * n = sentinel->next;
    while (n){
        std::cout << "["<<n->interval.Get_begin() <<";"<<n->interval.Get_end() << "]"<<  "\n";
        n = n->next;
    }
    std::cout << "\n";
}


//####### DeleteNxtNode #######////####### DeleteNxtNode #######////####### DeleteNxtNode #######//
//####### DeleteNxtNode #######////####### DeleteNxtNode #######////####### DeleteNxtNode #######//


void SinglyLinkedList::DeleteNextIntervalAndMove()
{
    SinglyNode * n = current_node->next;
    current_node->next = current_node->next->next;
    length--;
    delete n;
}


//####### MoveToNxtNode #######////####### MoveToNxtNode #######////####### MoveToNxtNode #######//
//####### MoveToNxtNode #######////####### MoveToNxtNode #######////####### MoveToNxtNode #######//


void SinglyLinkedList::Move()
{
   current_node = current_node->next;
}


//####### InitializeCurrentPosition #######////####### InitializeCurrentPosition #######////####### InitializeCurrentPosition #######//
//####### InitializeCurrentPosition #######////####### InitializeCurrentPosition #######////####### InitializeCurrentPosition #######//


void SinglyLinkedList::InitializeCurrentPosition()
{
    current_node = sentinel->next;
}


//####### ListisEmpty #######////####### ListisEmpty #######////####### ListisEmpty #######//
//####### ListisEmpty #######////####### ListisEmpty #######////####### ListisEmpty #######//


bool SinglyLinkedList::Empty()
{
    return length==0;
}


//####### SortAndMergeInterval #######////####### SortAndMergeInterval #######////####### SortAndMergeInterval #######//
//####### SortAndMergeInterval #######////####### SortAndMergeInterval #######////####### SortAndMergeInterval #######//


void SinglyLinkedList::Merge()
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


//####### Destructor #######////####### Destructor #######////####### Destructor #######//
//####### Destructor #######////####### Destructor #######////####### Destructor #######//


SinglyLinkedList::~SinglyLinkedList()
{
    for (int i=0; i<length+1; i++)
    {
        SinglyNode * nodeToDelete = sentinel;
        sentinel = sentinel->next;
        delete nodeToDelete;
    }
}


//####### Max #######////####### Max #######////####### Max #######//
//####### Max #######////####### Max #######////####### Max #######//


double SinglyLinkedList::Max()
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


double SinglyLinkedList::Min()
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


//####### IntersectEachElementWith #######////####### IntersectEachElementWith #######////####### IntersectEachElementWith #######//
//####### IntersectEachElementWith #######////####### IntersectEachElementWith #######////####### IntersectEachElementWith #######//


void SinglyLinkedList::IntersectWith(Interval & interval_to_intersect)
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


void SinglyLinkedList::ComplementaryIn(Interval & d)
{
    if (this->Empty())
    {
        this->AddInterval(d);
    }
    else
    {
        SinglyLinkedList * list_of_complementary_intervals = new SinglyLinkedList();
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
            SinglyNode * n = sentinel;
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


//####### size #######////####### size #######////####### size #######//
//####### size #######////####### size #######////####### size #######//


int SinglyLinkedList::Size()
{
    return length;
}



Interval SinglyLinkedList::Intersect()
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