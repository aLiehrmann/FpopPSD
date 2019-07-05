#ifndef DEF_INTERVAL
#define DEF_INTERVAL

#include <vector>
#include <array> 

class Interval
{
private:
    double begin;
    double end;
public:
    /**
     * @details Instancie un intervalle vide. 
     * Tout intervalle de la forme [a,b] tel que a>b est considéré comme un intervalle vide (par default [+1,-1]).
     */
    Interval();

    /**
     * Instancie un intervalle de la forme [begin_,end_].
     */
    Interval(double begin_, double end_);

    /**
     * @details Met à jour l'intervalle courant en l'intersectant avec un autre intervalle.
     * @param[in] interval_to_intesect Un intervalle qui peut être vide ou prendre la forme d'un singleton.
     */
    void operator&=(Interval const& interval_to_intesect);

    /**
     * @details Compare le début de deux intervalles.
     * @returns TRUE si le début de l'intervalle 'interval1' est inférieur au début de l'intervalle 'interval2', FALSE sinon.
     */
    static bool Compare_begin(Interval const& interval1, Interval const& interval2);

    /**
     * @details Compare la fin de deux intervalles.
     * @returns TRUE si la fin de l'intervalle 'interval1' est inférieure à la fin de l'intervalle 'interval2', FALSE sinon.
     */
    static bool Compare_end(Interval const& interval1, Interval const& interval2);

    /**
     * @returns TRUE si l'intervalle courant est vide ([a,b] tel que a>b) prend la forme d'un singleton ([a,a]), FALSE sinon. 
     */
    bool IsEmpty_or_singleton();

    /**
     * @returns Renvoie le debut de l'intervalle courant.
     */
    double Get_begin();

    /**
     * @returns Renvoie la fin de l'intervalle courant.
     */
    double Get_end();

    /**
     * @details Met à jour le debut de l'intervalle courant.
     */
    void Set_begin(double begin_);

    /**
     * @details Met à jour la fin de l'intervalle courant.
     */
    void Set_end(double end_);

    
};

#endif 