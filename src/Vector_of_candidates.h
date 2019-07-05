#ifndef DEF_VECTOR_OF_CANDIDATES 
#define DEF_VECTOR_OF_CANDIDATES

#include "Candidate.h"

class Vector_of_candidates
{
private:
    int last_active_candidate;
    Candidate ** vector_of_candidates;
    int max_length;
    int temp_max_length;
public:
    Vector_of_candidates(int max_length, Candidate * candidate);
    ~Vector_of_candidates();
    void Clean();
    Candidate*& operator[](int indice);
    void operator+=(Candidate * pt_candidate);
    int Get_last_active_candidate();
};
#endif