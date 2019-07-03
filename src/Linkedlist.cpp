#include "Linkedlist.h"
#include <cstddef>
#include <iostream>

Interval::Interval()
{   
    begin = 1;
    end = -1;
}

Interval::Interval(double begin_, double end_)
{
    begin = begin_;
    end = end_;
}

Interval::Interval(Linkedlist * list_of_intervals_to_intersect)
{   
    if (list_of_intervals_to_intersect->Empty())
    {
        begin=1;
        end=-1;
    }
    else
    {
        begin = list_of_intervals_to_intersect->Max();
        end = list_of_intervals_to_intersect->Min();
    }
}

bool Interval::IsEmpty_or_singleton()
{
    return begin >= end;  
}

void Interval::operator&=(Interval const& interval_to_intesect)
{
    //std::cout << begin << " " << end << "|" << interval_to_intesect.begin << " " << interval_to_intesect.end << "\n";
    begin = std::max(begin, interval_to_intesect.begin);
    end = std::min(end, interval_to_intesect.end);
}

bool Interval::Compare_begin(Interval const& interval1, Interval const& interval2)
{
    return interval1.begin<interval2.begin;
}
 
bool Interval::Compare_end(Interval const& interval1, Interval const& interval2)
{
    return interval1.end<interval2.end;
}

double Interval::Get_begin()
{
    return begin;
}

double Interval::Get_end()
{
    return end;
}

void Interval::Set_begin(double begin_)
{
    begin = begin_;
}

void Interval::Set_end(double end_)
{
    end = end_;
}

Node *split(Node *head)  
{  
    Node *fast = head,*slow = head;  
    while (fast->next && fast->next->next)  
    {  
        fast = fast->next->next;  
        slow = slow->next;  
    }  
    Node *temp = slow->next;  
    slow->next = NULL; 
    return temp;  
}  


Node *merge(Node *first, Node *second)  
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

Node * mergeSort(Node *head)  
{  
    if (!head || !head->next)
    {
        return head;
    }
    Node *second = split(head);  
  
    head = mergeSort(head);  
    second = mergeSort(second);  
    return merge(head,second);  
}  



Linkedlist::Linkedlist()
{
    head=NULL;
    tail=NULL;
    length=0;
}

Linkedlist::Linkedlist(Interval interval)
{
    length = 1;
    Node *temp = new Node;
    temp->interval = interval;
    temp->next = NULL;
    temp->previous = NULL;
    head = temp;
    tail = temp;
    temp = NULL;
}

void Linkedlist::Push_back(Interval interval)
{
    length++;
    Node *temp = new Node;
    temp->interval = interval;
    temp->next = NULL;
    temp->previous = NULL;

    if (head==NULL){
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else
    {
    
       tail->next = temp;
       temp->previous = tail;
       tail = temp;
       temp = NULL;
    }
}

Node *  Linkedlist::Front(){
    return head;
}

Node * Linkedlist::Back(){
    return tail;
}

bool Linkedlist::Empty(){
    return head==NULL;
}

double Linkedlist::Max(){
    Node * current_node = head;
    double temp_max{current_node->interval.Get_begin()};
    while (current_node->next){
        current_node=current_node->next;
        if (current_node->interval.Get_begin()>temp_max)
        {
            temp_max=current_node->interval.Get_begin();
        }
    }
    current_node = 0;
    return temp_max; 
}

double Linkedlist::Min(){
    Node * current_node = head;
    double temp_min{current_node->interval.Get_end()};
    while (current_node->next){
        current_node=current_node->next;
        if (current_node->interval.Get_end()<temp_min)
        {
            temp_min=current_node->interval.Get_end();
        }
    }
    current_node = 0;
    return temp_min; 
}

int Linkedlist::Size()
{
    return length;
}

void Linkedlist::Sort()
{
    head = mergeSort(head);
    this->Update_tail();
}


void Linkedlist::Merge()
{
    if (!this->Empty())
    {
        this->Sort();
        Node * current_node = head->next;
        while (current_node){
            if (current_node->previous->interval.Get_end() >= current_node->interval.Get_begin())
            {
                if (current_node->previous->interval.Get_end() < current_node->interval.Get_end())
                {
                    current_node->previous->interval.Set_end(current_node->interval.Get_end());
                    current_node = this->Erase(current_node);
                    length--;
                }
                else
                {
                    current_node = this->Erase(current_node);
                    length--;
                }
                
            }
            else
            {
                current_node = current_node->next;
            }
        }
        this->Update_tail(); //DANS LA BOUCLE ??
    }
}


Node* Linkedlist::Erase(Node * node_to_erased)
{
    if (!node_to_erased->previous & !node_to_erased->next)
    {
        tail=NULL;
        head=NULL;
        delete node_to_erased;
        return NULL;
    }
    if (node_to_erased->previous)
    {
        node_to_erased->previous->next = node_to_erased->next;
    }
    if (node_to_erased->next)
    {
        node_to_erased->next->previous = node_to_erased->previous;
    }
    Node * n = node_to_erased->next;
    delete node_to_erased;
    return n;
}


void Linkedlist::Update_tail(){
    tail = head;
    Node * current_node = head->next;
    while (current_node)
    {
        tail=current_node;
        current_node = current_node->next;   
    }
    current_node=NULL;
}

void Linkedlist::Update_head(){
    Node * current_node = tail->previous;
    if (!current_node)
    {
        head=tail;
    }
    while (current_node)
    {
        head=current_node;
        current_node = current_node->previous;   
    }
    current_node=NULL;
}

void Linkedlist::Print(){
    Node * n = head;
    while (n){
        std::cout << n->interval.Get_begin() <<";"<<n->interval.Get_end() << "\n";
        n = n->next;
    }
    std::cout << "\n";

}

void Linkedlist::Intersect_with(Interval & interval_to_intersect)
{
    Node * current_node = head;
    while(current_node)
    {
        tail=current_node;
        current_node->interval&=interval_to_intersect;
        if (current_node->interval.IsEmpty_or_singleton())
        {
            tail=current_node->previous;
            current_node = this->Erase(current_node);
            length--;
            
        }
        else
        {
            current_node=current_node->next;
        }
        
    }
    if (tail){
        this->Update_head();
    }
}

void Linkedlist::Complementary_in(Interval & d)
{
    if (this->Empty())
    {
        this->Push_back(d);
    }
    else
    {
        Linkedlist * list_of_complementary_intervals = new Linkedlist();
        this->Intersect_with(d);
        if (head->interval.Get_begin()>d.Get_begin())
        {
            list_of_complementary_intervals->Push_back(Interval(d.Get_begin(), head->interval.Get_begin()));
        }
        Node * current_node = head->next;
        while (current_node)
        {
            list_of_complementary_intervals->Push_back(Interval(current_node->previous->interval.Get_end(), current_node->interval.Get_begin()));
            current_node=current_node->next;
        }
        current_node=0;
        if (tail->interval.Get_end()<d.Get_end())
        {
            list_of_complementary_intervals->Push_back(Interval(tail->interval.Get_end(), d.Get_end()));
        }
        
        Linkedlist * list_of_interval_to_erased = new Linkedlist();
        list_of_interval_to_erased->head = head;
        head = list_of_complementary_intervals->head;
        tail = list_of_complementary_intervals->tail;
        length = list_of_complementary_intervals->length;
        list_of_complementary_intervals->head=0;
        list_of_complementary_intervals->tail=0;
        
        delete list_of_complementary_intervals;
        delete list_of_interval_to_erased;
        list_of_interval_to_erased=0;
        list_of_complementary_intervals=0;
    }
}

Linkedlist::~Linkedlist(){
    if (head)
    {
        Node * current_node = head->next;
        while (current_node)
        {
            delete current_node->previous;
            current_node = current_node->next;
        }
        delete tail;
        tail=0;
        head=0;
        length=0;
    }
}