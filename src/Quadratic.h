#ifndef DEF_QUADRATIC
#define DEF_QUADRATIC

#include <array>
#include "Linkedlist.h"

class Quadratic
{
private:
    std::array<double, 3> coef;    
public:
    
    /**
     * @details Instancie une forme quadratique dont la valeur des coefficients est nulle.
     */ 
    Quadratic();
    
    /**
     * @details Instancie la forme quadratique a0 + a1*X +a2*X^2 .
     */
    Quadratic(double a0, double a1, double a2);
    
    /**
     * @details Additione les coefficients a0, a1, a2 aux coefficients de la forme quadratique courante.
     */
    void Add_coef(double a0, double a1, double a2);

    /**
     *  @returns le minimum de la forme quadratique.
     */
    double Minimum();

    /**
     *  @details Calcule les racines de la forme quadratique.
     *  @returns l'intervalle sur lequel la forme quadratique est négative, un intervalle vide sinon.
     */
    Interval Negative_interval();

    /**
     * @returns une forme quadratique dont les coeffcients sont égaux à la différence des coeffcients de deux formes quadratiques.
     */
    Quadratic operator-(Quadratic const& quadratic_to_subtract);

};




#endif