#include "Sampling.h"
#include "Candidate.h"
#include <iterator>
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>


//####### Rand_one #######////####### Rand_one #######////####### Rand_one #######//
//####### Rand_one #######////####### Rand_one #######////####### Rand_one #######//


std::vector<int> Sampling::Rand_one(int p, int n, int nb)
{   
    return std::vector<int> {std::rand()%(n-p-1)+1+p};
}


//####### Rand_with_replacement #######////####### Rand_with_replacement #######////####### Rand_with_replacement #######//
//####### Rand_with_replacement #######////####### Rand_with_replacement #######////####### Rand_with_replacement #######//


std::vector<int> Sampling::Rand_with_replacement(int p, int n, int nb)
{   
    int s;
    std::vector<int> chosen_candidates;

    for (int i {0}; i<nb; i++)
    {
        s = (std::rand()%(n-p-1))+1+p;
        chosen_candidates.push_back(s);
    }
    return chosen_candidates;
}


//####### Rand_without_replacement #######////####### Rand_without_replacement #######////####### Rand_without_replacement #######//
//####### Rand_without_replacement #######////####### Rand_without_replacement #######////####### Rand_without_replacement #######//


std::vector<int> Sampling::Rand_without_replacement(int p, int n, int nb)
{   
    int i {0};
    int s;
    std::vector<int> chosen_candidates;
    if (nb+p>= n)
    {
        for(int j {n-1}; j>p ; j--)
        {
            chosen_candidates.push_back(j);
        }
    }
    else
    {
        while (i < nb)
        {
            s = (std::rand()%(n-p-1))+1+p;
            if (find(chosen_candidates.begin(), chosen_candidates.end(), s) == chosen_candidates.end())
            {
                chosen_candidates.push_back(s);
                i+=1;
            }
        }
    }
    return chosen_candidates;
}


//####### All #######////####### All #######////####### All #######//
//####### All #######////####### All #######////####### All #######//


std::vector<int> Sampling::All(int p, int n, int nb)
{   
    std::vector<int> chosen_candidates;
    for (int i {n-1}; i>p; i--)
    {
        chosen_candidates.push_back(i);
    }
    return chosen_candidates;
}


//####### Last #######////####### Last #######////####### Last #######//
//####### Last #######////####### Last #######////####### Last #######//


std::vector<int> Sampling::Last(int p, int n, int nb)
{
    std::vector<int> chosen_candidates;
    if (nb+p >= n)
    {
        for(int j {n-1}; j>p ; j--)
        {
            chosen_candidates.push_back(j);
        }
    }
    else
    {
        for (int j {n-1}; j>=n-nb; j--)
        {
            chosen_candidates.push_back(j);
        }
    }
    return chosen_candidates;
}


//####### Only #######////####### Only #######////####### Only #######//
//####### Only #######////####### Only #######////####### Only #######//

std::vector<int> Sampling::Only(int p, int n, int nb)
{
    std::vector<int> chosen_candidates;
    if (n-nb>p)
    {
        chosen_candidates.push_back(n-nb);
    }
    else
    {
        chosen_candidates.push_back(n-1);
    }
    return chosen_candidates;
}
