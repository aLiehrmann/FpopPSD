#ifndef DEF_OPPSD
#define DEF_OPPSD

#include <vector>
#include "Interval.h"

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
     * @param[in] y a data vector ordered according to an attribute.
     * @param[in] beta a coefficient used in the calculation of the penalty.
     * @param[in] alpha a constant used in the calculation of the penalty.
     * @paraam[in] wt a vector of weight linked to the data.    
     */
    OpPSD(std::vector<double> y_, double beta_, double alpha_, std::vector<double> wt_ = {0});
    
    /**
* @details Procedure to infer the number of changepoints and their location in the data.
     */
    void Search();

    /**
     * @returns the location of inferred cghangepoints in the data.  
     */
    std::vector<int> Retreive_changepoints();
};


#endif
