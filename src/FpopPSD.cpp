#include <vector>
#include <iostream>
#include "FpopPSD.h"
#include "Candidate.h"
#include <algorithm>
#include <math.h>
#include <list>
#include <limits>
#include "Sampling.h"
#include "Ordered_list_of_intervals.h"
#include "Interval.h"


FpopPSD::FpopPSD(){};

FpopPSD::FpopPSD(std::vector<double> y_,
    double beta_,
    double alpha_,
    std::vector<int> (*sampling_method_)(int, int, int),
    int sampling_method_parameter_, 
    std::vector<double>  wt_)
{
    y = y_;
    n = y_.size();
    d = Interval(*std::min_element(y_.begin(), y_.end()), *std::max_element(y_.begin(), y_.end()));
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
    sampling_method = sampling_method_;
    sampling_method_parameter = sampling_method_parameter_;
    nb_candidates = std::vector<int> (y.size()-1, 0);
    nb_intervals = std::vector<int> (y.size()-1, 0);
}

void FpopPSD::Search()
{
    std::list<Candidate> list_of_candidates {Candidate(0,  Ordered_list_of_intervals (d), 0, 0, Quadratic())};
    double F;
    int t_hat;
    double min_candidate;
    int index;
    std::vector<int> chosen_candidates;
    std::vector<std::list<Candidate>::iterator> vector_of_it_candidates;

    

    for (int t {1}; t<y.size(); t++)
    {   
        /*
            On initialise un vecteur d'itérateurs.
            Chaque itérateur pointe vers un candidat contenu dans list_of_candidates.
            À cette étape, le dernier élément du vecteur ne pointe vers aucun candidat.
            Ce dernier élément est défini en vue de l'introduction du nouveau candidat.
        */
        
        std::vector<std::list<Candidate>::iterator> vector_of_it_candidates (list_of_candidates.size()+1);
        index = 0;
        for (auto it_candidate {list_of_candidates.begin()}; it_candidate != list_of_candidates.end(); ++it_candidate)
        {
            vector_of_it_candidates[index] = it_candidate;
            index+=1;
        }

        /*
            (1) On met à jour de la forme quadratique pour l'ensemble des candidats encore considérés.
            
            (2) On met à jour de la pénalité dépendante de la taille du dernier segment pour l'ensemble des candidats encore considérés.
            
            (3) on met à jour du coût minimum de ségmentation et sauvegarde candidat associé.
        */
        F = std::numeric_limits<double>::max();
        for (int i {0}; i<vector_of_it_candidates.size()-1; i++)
        {
            (*vector_of_it_candidates[i]).Add_quadratic(wt[t], y[t]); //1
            (*vector_of_it_candidates[i]).Set_penalty(-beta * std::log(t-(*vector_of_it_candidates[i]).Get_tau())); //(2)
            min_candidate = (*vector_of_it_candidates[i]).Minimum_of_cost_function(); 
            if (min_candidate < F) //(3)
            {
                F = min_candidate;
                t_hat = (*vector_of_it_candidates[i]).Get_tau();
            }
        }


        /*
            (1) On sauvegarde de la position de la dernière rupture du candidat qui minimise le coût de segmentation jusqu'au point t.
            
            (2) On introduit un nouveau candidat dont la dernière rupture correspond au point t.
            
            (3) Le dernier élément de array_of_candidates pointe désormais vers le dernier candidat introduit.
        */
        cp[t] = t_hat; //(1)
        list_of_candidates.push_back( Candidate(t, Ordered_list_of_intervals (d), F+alpha, 0, Quadratic())); //(2)
        vector_of_it_candidates[vector_of_it_candidates.size()-1] = --list_of_candidates.end(); //(3)

        
        /*
            (1) On sauvegarde de la somme des intervalles sur lesquels sont définies les fonctions de coût associées aux différents candidats.
            
            (2) On sauvegarde du nombre de candidats encore considérés. 
        */

        
        for (int i {0}; i<vector_of_it_candidates.size(); i++)
        {
            nb_intervals[t-1] += (*vector_of_it_candidates[i]).GetZ().size(); //(1)
        }
        nb_candidates[t-1] += list_of_candidates.size(); //(2)

 
        //On met à jour la zone de vie de la fonction de coût du dernier candidat.
        
        (*vector_of_it_candidates.back()).Compare_to_past_candidates(vector_of_it_candidates, d);

        /*
            (1) On échantillonne les candidats introduits après un certain candidat i pour les comparer avec ce dernier.

            (2) On met à jour la zone de vie de la fonction de coût du candidat i.
        */
        
        for (auto i{0}; i<vector_of_it_candidates.size()-2; i++) //
        {
            chosen_candidates = sampling_method(i, vector_of_it_candidates.size()-1, sampling_method_parameter); //(1)
            (*vector_of_it_candidates[i]).Compare_to_future_candidates(vector_of_it_candidates, chosen_candidates); //(2)
        }
    /*
        On élague les candidats dont la zone de vie de leur fonction de coût est vide.
    */
    
        list_of_candidates.erase(std::remove_if(list_of_candidates.begin(), list_of_candidates.end(), [](Candidate & a) {
            return a.GetZ().Is_empty();
        }), list_of_candidates.end());

     }

}

std::vector<int> FpopPSD::Retreive_changepoints()
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


std::vector<int> FpopPSD::Get_candidates()
{
    return nb_candidates;
}

std::vector<int> FpopPSD::Get_intervals()
{
    return nb_intervals;
}