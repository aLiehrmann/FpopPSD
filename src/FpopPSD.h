#ifndef DEF_FPOPPSD
#define DEF_FPOPPSD

#include <vector>
#include "Linkedlist.h"
#include <random>

class FpopPSD
{
private:
    std::vector<double> y;
    int n; 
    Interval d;
    double beta;
    double alpha;
    std::vector<double> wt;
    std::vector<int> cp;
    std::vector<int> (*sampling_method)(int, int, int);
    int sampling_method_parameter;
    std::vector<int> nb_candidates;
    std::vector<int> nb_intervals;

    
public:
    /**
     * @param[in] y un vecteur de données ordonnées seulon un attribut
     * @param[in] beta coefficient utilisé dans le calcul de le la panalité
     * @param[in] alpha constante utilisée dans le calcul de la pénalité
     * @param[in] sampling_method méthode d'échantillonnage des candidats
     * @param[in] param_method paramètre utilisé par la méthode d'échantillonage
     * @paraam[in] wt vecteur de poids associé à chaque point     
     */
    FpopPSD(std::vector<double> y_,
        double beta_,
        double alpha_, 
        std::vector<int> (*sampling_method_)(int, int, int),
        int para_method_,
        std::vector<double> wt_ = {0});
    
    FpopPSD ();

    /**
     * @details Procédure de localisation des ruptures dans la série de données.
     */
    void Search();

    /**
     * @returns la localisation des ruptures inférées dans la série de données. 
     */
    std::vector<int> Retreive_changepoints();

    /**
     * @returns un vecteur qui contient le nombre total d'intervalles formant la zone de vie des différents candidats avant l'étape d'élaguage à chaque itération.
     */
    std::vector<int> Get_intervals();


    /**
     * @returns un vecteur qui contient le nombre total de candidats avant l'étape d'élaguage à chaque itération.
     */
    std::vector<int> Get_candidates();
};


#endif
