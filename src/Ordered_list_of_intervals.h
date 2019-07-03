#ifndef DEF_ORDERED_LIST_OF_INTERVALS
#define DEF_ORDERED_LIST_OF_INTERVALS

#include <list>
#include "Interval.h"


class Ordered_list_of_intervals
{
private:
    std::list<Interval> list_of_intervals;
public:
    /**
     * @details Instancie l'union triée des intervalles contenus dans une liste d'intervalles.
     * @param[in] list_of_intervals_to_merge Une liste d'intrvales non vides, ne contenant pas de singletons, non ordonnée. Cette liste peut être vide.
     */
    Ordered_list_of_intervals(std::list<Interval> & list_of_intervals_to_merge);
    
    /**
     * @details Instancie une liste ordonnée d'intervalles avec l'intervalle 'interval'.
     */
    Ordered_list_of_intervals(Interval interval);
    
    /**
     * @details Instancie une liste ordonnée d'intervalles à vide.
     */
    Ordered_list_of_intervals();

    /**
     * @details Met à jour la liste ordonnée d'intervalles courante en intersectant chaque intervalle contenu dans cette liste avec un l'intervalle 'interval_to_intersect'.
     */    
    void Intersect_with(Interval & interval_to_intersect);

    /**
     * @details Met à jour la liste ordonée d'intervalles avec son complémentaire dans l'intervalle 'D'. Si la liste est vide, elle est mise à jour avec l'intervalle D.
     */
    void Complementary_in(Interval & d);

    /**
     * @returns TRUE si la liste triée d'intervalles est vide, FALSE sinon.
     */
    bool Is_empty();

    /**
     * @details Met à jour la liste triée d'intervalles en supprimant les intervalles vides et les singletons.
     */
    void Clean();

    /**
     * @returns La taille de la liste triée d'intervalles.
     */
    int size();

    /**
     * @returns La liste triée d'intervalles.
     */
    std::list<Interval> Get_list();
};


#endif