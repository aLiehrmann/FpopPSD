#include <vector>
#include <iostream>
#include "OpPSD.h"
#include "Candidate.h"
#include <algorithm>
#include <math.h>
#include <limits>
#include <list> 
#include "Ordered_list_of_intervals.h"

OpPSD::OpPSD(std::vector<double> y_, double beta_, double alpha_, std::vector<double>  wt_)
{
    y = y_;
    n = y_.size();
    d = Interval(*std::min_element(y.begin(), y.end()), *std::max_element(y.begin(), y.end()));
    y.insert(y.begin(), 0);
    beta = beta_;
    alpha = alpha_;
    if (wt_.size()==1 && wt_[0] == 0)
    {
        wt = std::vector<double> (y.size(), 1);
    }
    else
    {
       wt = wt_;
       wt.insert(wt.begin(), 0); 
    }
    cp = std::vector<int> (y.size(), 0);
}

void OpPSD::Search()
{
    std::list<Candidate> list_of_candidates {Candidate(0, Ordered_list_of_intervals (d), 0, 0, Quadratic())};
    double F;
    int t_hat;
    double min_candidate;
    
    
    for (int t {1}; t<y.size(); t++)
    {   
        F = std::numeric_limits<double>::max();
        for (auto it_candidate {list_of_candidates.begin()}; it_candidate != list_of_candidates.end(); ++it_candidate)
        {   
            (*it_candidate).Add_quadratic(wt[t], y[t]);
            (*it_candidate).Set_penalty(-beta * std::log(t-(*it_candidate).Get_tau()));
            min_candidate = (*it_candidate).Minimum_of_cost_function();
            if (min_candidate < F)
            {
                F = min_candidate;
                t_hat = (*it_candidate).Get_tau();
            }
        }
        cp[t] = t_hat;
        list_of_candidates.push_back( Candidate(t, Ordered_list_of_intervals (d), F+alpha, 0, Quadratic()));
    }
}

std::vector<int> OpPSD::Retreive_changepoints()
{
    std::vector<int> list_of_changepoints;
    int i (y.size()-1);
    while (cp[i] != 0)
    {
        list_of_changepoints.push_back(cp[i]);
        i = cp[i];
    }
    std::reverse(list_of_changepoints.begin(), list_of_changepoints.end());
    return list_of_changepoints;
}