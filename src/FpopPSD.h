#ifndef DEF_FPOPPSD
#define DEF_FPOPPSD

#include <vector>
#include "Interval.h"
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
     * @param[in] y a data vector ordered according to an attribute.
     * @param[in] beta a coefficient used in the calculation of the penalty.
     * @param[in] alpha a constant used in the calculation of the penalty.
     * @param[in] sampling_method a sampling method for candidates.
     * @param[in] param_method a parameter used by the sampling method.
     * @paraam[in] wt a vector of weight linked to the data.    
     */
    FpopPSD(std::vector<double> y_,
        double beta_,
        double alpha_, 
        std::vector<int> (*sampling_method_)(int, int, int),
        int para_method_,
        std::vector<double> wt_ = {0});
    
    FpopPSD ();

    /**
     * @details Procedure for inferring the number of changepoints and their location in the data.
     */
    void Search();

    /**
     * @returns the location of inferred cghangepoints in the data . 
     */
    std::vector<int> Retreive_changepoints();

    /**
     * @returns a vector that contains the total number of intervals forming the area of life of the different candidates before the pruning step at each iteration.
     */
    std::vector<int> Get_intervals();


    /**
     * @returns a vector that contains the total number of candidates before the pruning step at each iteration.
     */
    std::vector<int> Get_candidates();
};


#endif
