#ifndef DEF_ARRAY_OF_CANDIDATES 
#define DEF_ARRAY_OF_CANDIDATES

#include "Candidate.h"

class Array_of_candidates
{
private:
    int last_active_candidate;
    Candidate ** array_of_candidates;
    int max_length;
    int temp_max_length;
public:
    Array_of_candidates(int max_length, Candidate * candidate);
    ~Array_of_candidates();
    void Remove_candidates();
    Candidate*& operator[](int indice);
    void operator+=(Candidate * pt_candidate);
    int Get_last_active_candidate();
};
#endif