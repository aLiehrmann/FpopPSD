#include "Candidate.h"
#include "Quadratic.h"
#include "Interval.h"
#include <vector>
#include <array> 
#include <iostream> 
#include <list>
#include <math.h>
#include "Array_of_candidates.h"
#include "DoublyLinkedList.h"


Candidate::Candidate(int tau_, DoublyLinkedList * z_, double cost_up_to_tau_, double pen_, Quadratic quad_)
{

    tau = tau_;
    z = z_;
    cost_up_to_tau = cost_up_to_tau_;
    pen = pen_;
    quad = quad_;
}

Candidate::Candidate()
{
    tau=-1;
    z = new DoublyLinkedList();
    cost_up_to_tau=-1;
    pen=-1;
    quad = Quadratic();
}

double Candidate::Minimum_of_cost_function()
{   
    return quad.Minimum() + pen + cost_up_to_tau;
}

void Candidate::Set_penalty(double pen_)
{
    pen = pen_;
}

void Candidate::Add_quadratic(double wt, double y)
{
    quad.Add_coef(wt*pow(y,2), -2*wt*y, wt);
}

void Candidate::Compare_to_past_candidates (Array_of_candidates & array_of_it_candidates, Interval & D)
{

    DoublyLinkedList * list_of_intervals = new DoublyLinkedList();
    Interval interval;
    Quadratic new_quad;
    for (int i {0}; i<array_of_it_candidates.Get_last_active_candidate(); i++)
    {   

        new_quad = (*array_of_it_candidates[i]).quad - quad;
        new_quad.Add_coef((*array_of_it_candidates[i]).cost_up_to_tau - cost_up_to_tau,0,0);
        interval = new_quad.Negative_interval();
        /*
            Test qui garantit que list_of_interval n'est composée que d'intervalles non vides et qui ne sont pas des singletons.
            On peut considérer le singleton comme un intervalle vide car la fonction quadratique par morceau est continue et les zones de vies des fonctions de côut adjacentes au singleton s'intersectent en ce point.
            list_of_interval peut être vide.
        */
        if (!interval.IsEmpty_or_singleton())
        {
            list_of_intervals->AddInterval(interval); 
        }
    }
    list_of_intervals->Merge();
    list_of_intervals->ComplementaryIn(D); //leak_memory ICI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    delete z;
    z = list_of_intervals;
}

void Candidate::Compare_to_future_candidates (Array_of_candidates & array_of_it_candidates, std::vector<int> & chosen_future_candidates)
{
    DoublyLinkedList * list_of_intervals = new DoublyLinkedList();
    Interval intersection_of_intervals;
    Interval interval;
    Quadratic new_quad;
    for (int indexe_chosen_future_candidates: chosen_future_candidates)
    {
        new_quad = quad - (*array_of_it_candidates[indexe_chosen_future_candidates]).quad;
        new_quad.Add_coef(pen+cost_up_to_tau-((*array_of_it_candidates[indexe_chosen_future_candidates]).pen+(*array_of_it_candidates[indexe_chosen_future_candidates]).cost_up_to_tau),0,0);
        interval = new_quad.Negative_interval();
        /*
            Test qui garantit que list_of_interval n'est composée que d'intervalles non vides et qui ne sont pas des singletons.
            Si on trouve un intervalle vide ou un singleton, on met à jour la zone de de vie du candidat courant à vide en vue de son élaguage (propriété sur l'intersection).
            On peut considérer le singleton comme un intervalle vide car la fonction quadratique par morceau est continue et les zones de vies des fonctions de côut adjacentes au singleton s'intersectent en ce point.
        */
        if (!interval.IsEmpty_or_singleton())
        {
            list_of_intervals->AddInterval(interval);
        }
        else
        {
            delete z;
            z = new DoublyLinkedList();
            break;
        }
        
    }
    if (!(z->Empty())) 
    {
        intersection_of_intervals = list_of_intervals->Intersect();
        z->IntersectWith(intersection_of_intervals);
    }
    delete list_of_intervals;
}

int Candidate::Get_tau()
{
    return tau;
}

DoublyLinkedList * Candidate::GetZ()
{
    return z;
}
void Candidate::Set_wait()
{
    wait--;
}

int Candidate::Get_wait()
{
    return wait;
}

Candidate::~Candidate()
{
    delete z;
}