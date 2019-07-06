#include <vector>
#include <iostream>
#include "FpopPSD.h"
#include "Candidate.h"
#include <algorithm>
#include <math.h>
#include <limits>
#include "Sampling.h"
#include "Array_of_candidates.h"
#include "DoublyLinkedList.h"
#include "Interval.h";


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
    double F;
    int t_hat;
    double min_candidate;
    int index;
    std::vector<int> chosen_candidates;
    Array_of_candidates array_of_candidates(3*log(n),new Candidate(0,  new DoublyLinkedList(d), 0, 0, Quadratic()));
    

    for (int t {1}; t<y.size(); t++)
    {   
        /*
            (1) On met à jour de la forme quadratique pour l'ensemble des candidats encore considérés.
            
            (2) On met à jour de la pénalité dépendante de la taille du dernier segment pour l'ensemble des candidats encore considérés.
            
            (3) on met à jour du coût minimum de ségmentation et sauvegarde candidat associé.
        */

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


        /*
            (1) On sauvegarde de la position de la dernière rupture du candidat qui minimise le coût de segmentation jusqu'au point t.
            
            (2) On introduit un nouveau candidat dont la dernière rupture correspond au point t.
            
            (3) Le dernier élément de array_of_candidates pointe désormais vers le dernier candidat introduit.
        */
        cp[t] = t_hat; //(1)
        Candidate * c = new Candidate(t, new DoublyLinkedList (d), F+alpha, 0, Quadratic());
        array_of_candidates += c;

        
        /*
            (1) On sauvegarde de la somme des intervalles sur lesquels sont définies les fonctions de coût associées aux différents candidats.
            
            (2) On sauvegarde du nombre de candidats encore considérés. 
        */

        
        for (int i {0}; i<=array_of_candidates.Get_last_active_candidate(); i++)
        {
            nb_intervals[t-1] += array_of_candidates[i] -> GetZ() -> Size(); //(1)
        }
        nb_candidates[t-1] += array_of_candidates.Get_last_active_candidate()+1; //(2)

 
        //On met à jour la zone de vie de la fonction de coût du dernier candidat.
        
        array_of_candidates[array_of_candidates.Get_last_active_candidate()] -> Compare_to_past_candidates(array_of_candidates, d); 

//        /*
//            (1) On échantillonne les candidats introduits après un certain candidat i pour les comparer avec ce dernier.
//
//            (2) On met à jour la zone de vie de la fonction de coût du candidat i.
//        */
//        
        //std::cout << "step: " <<t <<"\n";
        for (auto i{0}; i<array_of_candidates.Get_last_active_candidate()-1; i++) //
        {
            chosen_candidates = sampling_method(i, array_of_candidates.Get_last_active_candidate(), sampling_method_parameter); //(1)
            array_of_candidates[i] -> Compare_to_future_candidates(array_of_candidates, chosen_candidates); //(2)
        }
//    /*
//        On élague les candidats dont la zone de vie de leur fonction de coût est vide.
//    */
//    
              array_of_candidates.Remove_candidates();
//
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