#include "Ordered_list_of_intervals.h"
#include "Interval.h"
#include <list>
#include <iostream>


Ordered_list_of_intervals::Ordered_list_of_intervals(Interval interval)
{
    list_of_intervals.push_back(interval);
}

Ordered_list_of_intervals::Ordered_list_of_intervals(std::list<Interval> & list_of_intervals_to_merge)
{
    if (!list_of_intervals_to_merge.empty())
    {
        list_of_intervals_to_merge.sort(Interval::Compare_begin);

        list_of_intervals.push_back(list_of_intervals_to_merge.front());

        for (auto it_interval {++list_of_intervals_to_merge.begin()}; it_interval!=list_of_intervals_to_merge.end(); ++it_interval)
        {
            if (list_of_intervals.back().Get_end() >= (*it_interval).Get_begin())
            {   
                if (list_of_intervals.back().Get_end() < (*it_interval).Get_end())
                {
                    list_of_intervals.back().Set_end((*it_interval).Get_end());
                }
            }
            else
            {
                list_of_intervals.push_back((*it_interval));
            }
        }
    }
}

Ordered_list_of_intervals::Ordered_list_of_intervals()
{
    list_of_intervals = std::list<Interval> ();
}

void Ordered_list_of_intervals::Intersect_with(Interval & interval_to_intersect){

    for (auto it_interval {list_of_intervals.begin()}; it_interval!= list_of_intervals.end(); ++it_interval)
    {
        (*it_interval) &= interval_to_intersect;
        if ((*it_interval).IsEmpty_or_singleton())
        {
            --it_interval;
            list_of_intervals.erase(next(it_interval,1));
        }
    }
}

bool Ordered_list_of_intervals::Is_empty()
{
    return list_of_intervals.empty();
}

void Ordered_list_of_intervals::Complementary_in(Interval & d)
{
    /*
        On renvoie le complémentaire, dans D, des intervalles triés contenus dans list_of_intervals.
        (1) Si list_of_intervals est vide ou bien est composée d'un unique intervalle vide ou d'un singleton,
            on renvoie une liste comprenant uniquement l'intervalle D.
        (2) On intersecte D avec chaque intervalle contenus dans list_of_intervals qui est mofidiée sur place.
        (3) Si il existe une région non vide entre le debut de D et le debut du premier intervalle
            de la liste d'intervalles triés ou la fin du dernier intervalle de la liste d'intervalles triés et la fin de D,
            on ajoute cette dernière région à la liste des intervalles complémentaires.

    */
    if (list_of_intervals.empty()) //(1)
    {
        return list_of_intervals.push_back(d);
    }
    else
    {
        (*this).Intersect_with(d); //(2)
        std::list<Interval> list_of_complementary_intervals;
        if (list_of_intervals.front().Get_begin() > d.Get_begin()) //(3)
        {
            list_of_complementary_intervals.push_back( Interval(d.Get_begin(), list_of_intervals.front().Get_begin()) );
        }
        for (auto it_interval {list_of_intervals.begin()}; it_interval != --list_of_intervals.end(); it_interval++)
        {
            list_of_complementary_intervals.push_back( Interval((*it_interval).Get_end(), (*next(it_interval,1)).Get_begin()) );
        }
        if (list_of_intervals.back().Get_end() < d.Get_end()) //(3)
        {
            list_of_complementary_intervals.push_back(Interval(list_of_intervals.back().Get_end(), d.Get_end()));
        }
        list_of_intervals = list_of_complementary_intervals;
    }
}

void Ordered_list_of_intervals::Clean()
{
    for (auto it_interval {list_of_intervals.begin()}; it_interval!= list_of_intervals.end(); ++it_interval)
    {

        if ((*it_interval).IsEmpty_or_singleton())
        {
            --it_interval;
            list_of_intervals.erase(next(it_interval,1));
        }
    }
}

int Ordered_list_of_intervals::size()
{
    return list_of_intervals.size();
}


std::list<Interval> Ordered_list_of_intervals::Get_list()
{
    return list_of_intervals;
}