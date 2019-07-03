#ifndef DEF_OPPSD
#define DEF_OPPSD

#include <vector>
//#include "Interval.h"
#include "Linkedlist.h"

class OpPSD
{
private:
    std::vector<double> y;
    int n;
    Interval d;
    double beta;
    double alpha;
    std::vector<double> wt;
    std::vector<int> cp;
    
public:
    /**
     * @param[in] y_ un vecteur de données ordonnées seulon un attribut
     * @param[in] beta_ coefficient utilisé dans le calcul de le la panalité
     * @param[in] alpha_ constante utilisée dans le calcul de la pénalité
     * @paraam[in] wt_ vecteur de poids associé à chaque point     
     */
    OpPSD(std::vector<double> y_, double beta_, double alpha_, std::vector<double> wt_ = {0});
    
    /**
     * @details Procédure de localisation des ruptures dans la série de données.
     */
    void Search();

    /**
     * @returns la localisation des ruptures inférées dans la série de données. 
     */
    std::vector<int> Retreive_changepoints();
};


#endif
