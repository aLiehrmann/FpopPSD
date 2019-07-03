#include "Vector_of_candidates.h"
#include "Candidate.h"
#include <iostream>

Vector_of_candidates::Vector_of_candidates(int max_length_, Candidate * candidate)
{
    max_length = max_length_;
    temp_max_length = max_length_;
    vector_of_candidates = new Candidate*[max_length_];
    vector_of_candidates[0] = candidate;
    last_active_candidate = 0;
}

Candidate*& Vector_of_candidates::operator[](int indice){
    return vector_of_candidates[indice];
}

void Vector_of_candidates::operator+=(Candidate * pt_candidate){
    if (last_active_candidate+1==max_length)
    {   
        Candidate ** vector_of_candidates_temp = new Candidate*[max_length+temp_max_length];
        for (int i{0}; i<max_length; i++)
        {
            vector_of_candidates_temp[i] = vector_of_candidates[i];
        }
        delete[] vector_of_candidates;
        vector_of_candidates = vector_of_candidates_temp;
        vector_of_candidates_temp = 0;
        max_length = max_length+temp_max_length;
    }
    last_active_candidate++;
    vector_of_candidates[last_active_candidate] = pt_candidate;
}

void Vector_of_candidates::Clean(){
    int last_not_empty_candidate{-1};
    for (int i{0}; i<=last_active_candidate; i++){
        if (!(vector_of_candidates[i]->GetZ().Is_empty())){
            last_not_empty_candidate++;
            vector_of_candidates[last_not_empty_candidate] = vector_of_candidates[i];
        }
        else
        {
            delete vector_of_candidates[i];
            vector_of_candidates[i]=0;
        }
    }
    last_active_candidate = last_not_empty_candidate;
}

int Vector_of_candidates::Get_last_active_candidate()
{
    return last_active_candidate;
}