#include "Array_of_candidates.h"
#include "Candidate.h"
#include <iostream>

Array_of_candidates::Array_of_candidates(int max_length_, Candidate * candidate)
{
    max_length = max_length_;
    temp_max_length = max_length_;
    array_of_candidates = new Candidate*[max_length_];
    array_of_candidates[0] = candidate;
    last_active_candidate = 0;
}

Candidate*& Array_of_candidates::operator[](int indice){
    return array_of_candidates[indice];
}

void Array_of_candidates::operator+=(Candidate * pt_candidate){
    if (last_active_candidate+1==max_length)
    {   
        Candidate ** array_of_candidates_temp = new Candidate*[temp_max_length+max_length];
        for (int i{0}; i<max_length; i++)
        {
            array_of_candidates_temp[i] = array_of_candidates[i];
        }
        delete[] array_of_candidates;
        array_of_candidates = array_of_candidates_temp;
        array_of_candidates_temp=0;
        max_length = max_length+temp_max_length;
    }
    last_active_candidate++;
    array_of_candidates[last_active_candidate] = pt_candidate;
}

void Array_of_candidates::Remove_candidates(){
    int last_not_empty_candidate{-1};
    for (int i{0}; i<=last_active_candidate; i++){
        if (!(array_of_candidates[i]->GetZ().Is_empty())){
            last_not_empty_candidate++;
            array_of_candidates[last_not_empty_candidate] = array_of_candidates[i];
        }
        else
        {
            delete array_of_candidates[i];
            array_of_candidates[i]=0;
        }
    }
    last_active_candidate = last_not_empty_candidate;
}

int Array_of_candidates::Get_last_active_candidate()
{
    return last_active_candidate;
}

Array_of_candidates::~Array_of_candidates()
{
    for (int i=0;i<=last_active_candidate;i++)
    {
        delete array_of_candidates[i];
    }
    delete[] array_of_candidates;
}