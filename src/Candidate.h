#ifndef DEF_CANDIDATE
#define DEF_CANDIDATE

//#include "Interval.h"
#include <vector>
#include "Quadratic.h"
#include <list>
#include "Linkedlist.h"
class Vector_of_candidates;

class Candidate
{
private:
    double cost_up_to_tau;
    int tau;
    Linkedlist * z;
    Quadratic quad;
    double pen;
    int wait;

public:
    /**
     * @details Instancie un candidat.
     * @param[in] tau_ position de la dernière rupture du candidat
     * @param[in] z_ la liste triée des intervalles formant la zone de vie de la fonction de coût du candidat.
     * @param[in] cost_up_to_tau_ coût de la meilleure segmentation des données jusqu'au point tau
     * @param[in] pen_ pénalité dépendante de la taille du segment formé par les points situés après tau
     * @param[in] quad_ forme quadratique construite à partir des points situés après tau
     */
    Candidate(int tau_, Linkedlist * z_, double cost_up_to_tau_, double pen_, Quadratic quad_);
    
    /** 
     * @details Constructeur par défaut.
    */
    Candidate();
    /**
     * @returns le minimum de la fonction de coût.
     */
    double Minimum_of_cost_function();
    
    /**
     * @details Met à jour la pénalité dépendante de la taille du segment formé par les points situés après tau.
     */
    void Set_penalty(double pen_);

    /**
     * @details Recherche les intervalles sur lesquels la fonction de coût du dernier candidat est battue par la fonction de coût des candidats passés.
     * Met à jour la zone de vie de la fonction de coût du dernier candidat avec le complémentaire de l'union des intervalles trouvés.
     */
    void Compare_to_past_candidates (Vector_of_candidates & past_candidates, Interval & D);

    /**
     * @details Recherche les intervalles sur lesquels la fonction de coût du candidat courant est bat par la fonction de coût des candidats futures au candidat courant.
     * Met à jour la zone de vie du candidat courant en l'intersectant avec l'intersection des intervalles trouvés.
     */
    void Compare_to_future_candidates (Vector_of_candidates & future_candidates, std::vector<int> & chosen_candidates);
    
    /**
     * @details Met à jour la forme quadratique du candidat courant en lui additionnant la quadratique (y-X)^2 pondérée par wt.
     */
    void Add_quadratic(double wt, double y);
    
    /**
     * @returns la liste triée des intervalles formant la zone de vie de la fonction de coût du candidat courant.
     */
    Linkedlist * GetZ();

    /**
     * @returns tau du candidat courant.
     */
    int Get_tau();

    void Set_wait();
    int Get_wait();
    ~Candidate();
};


#endif