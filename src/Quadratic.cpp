#include "Quadratic.h"
#include <math.h> 
#include <array>
#include <limits> 
#include <iostream>
#include "Interval.h"


Quadratic::Quadratic()
{
    coef[0] = 0;
    coef[1] = 0;
    coef[2] = 0;
}


Quadratic::Quadratic(double a0, double a1, double a2)
{
    coef[0] = a0;
    coef[1] = a1;
    coef[2] = a2;
}

void Quadratic::Add_coef( double a0, double a1, double a2)
{
    coef[0] += a0;
    coef[1] += a1;
    coef[2] += a2;
    
}

double Quadratic::Minimum()
{
    double argmin { -coef[1] / (2*coef[2]) };
    return coef[2] * pow(argmin, 2) + coef[1] * argmin + coef[0];
}

Interval Quadratic::Negative_interval()
{
    double delta { pow(coef[1], 2) -4*coef[2]*coef[0] };
    double x1 {(-coef[1]-sqrt(delta))/(2*coef[2])};
    double x2 {(-coef[1]+sqrt(delta))/(2*coef[2])};
    if (delta > 0) 
    {
        if (x1 < x2) // on vérifie la borne inférieure et la borne supérieure avant instanciation de l'intervalle
        {
            return Interval (x1, x2);
        }
        else
        {
            return Interval (x2, x1);
        }
    }
    else
    {
        return Interval ();
    }
}

Quadratic Quadratic::operator-(Quadratic const& quadratic_to_subtract)
{
    return Quadratic(coef[0]-quadratic_to_subtract.coef[0], coef[1]-quadratic_to_subtract.coef[1], coef[2]-quadratic_to_subtract.coef[2]);
}