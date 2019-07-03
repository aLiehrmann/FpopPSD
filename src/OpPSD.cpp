#include <vector>
#include <iostream>
#include "OpPSD.h"
#include "Candidate.h"
#include <algorithm>
#include <math.h>
#include <limits>
#include <list> 
//#include "Ordered_list_of_intervals.h"
#include "Vector_of_candidates.h"
#include "Linkedlist.h"

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
    Vector_of_candidates array_of_candidates(10*log(n), new Candidate(0, new Linkedlist (d), 0, 0, Quadratic()));
    double F;
    int t_hat;
    double min_candidate;
    
    
    for (int t {1}; t<y.size(); t++)
    {   
        
        F = std::numeric_limits<double>::max();
        for (int i {0}; i<=array_of_candidates.Get_last_active_candidate(); i++)
        {
            array_of_candidates[i] -> Add_quadratic(wt[t], y[t]); //1
            array_of_candidates[i] -> Set_penalty(-beta * std::log(t-array_of_candidates[i] -> Get_tau())); //(2)
            min_candidate = array_of_candidates[i] -> Minimum_of_cost_function(); 
            if (min_candidate < F) //(3)
            {
                F = min_candidate;
                t_hat = array_of_candidates[i] -> Get_tau();
            }
        }
        cp[t] = t_hat; //(1)
        Candidate * c = new Candidate(t, new Linkedlist (d), F+alpha, 0, Quadratic());
        array_of_candidates += c;
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