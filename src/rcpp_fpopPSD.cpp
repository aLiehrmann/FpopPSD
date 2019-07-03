#include <Rcpp.h>
#include "FpopPSD.h"
#include "OpPSD.h"
#include <string>
#include <vector>
#include "Sampling.h"
#include <map>
using namespace Rcpp;


// [[Rcpp::export]]
List fpopPSD(std::vector<double> y, double beta, double alpha, std::string sampling_method, int sampling_method_parameter, std::vector<double>  wt)
{   
    FpopPSD f;
    typedef std::vector<int> (*fun)(int, int, int);
    std::map<std::string, fun> map_sampling_method;
    map_sampling_method["rand_one"] = Sampling::Rand_one;
    map_sampling_method["last"] = Sampling::Last;
    map_sampling_method["all"] = Sampling::All;
    map_sampling_method["only"] = Sampling::Only;
    map_sampling_method["rand_with_replacement"] = Sampling::Rand_with_replacement;
    map_sampling_method["rand_without_replacement"] = Sampling::Rand_without_replacement;
    
    if (map_sampling_method.find(sampling_method)!= map_sampling_method.end())
    {
      
      f = FpopPSD (y, 
          beta, 
          alpha, 
          (*map_sampling_method[sampling_method]), 
          sampling_method_parameter,
          wt);
      
      f.Search();
      
      List l = List::create(
    	_["changepoints"] = f.Retreive_changepoints(),
      _["intervals"] = f.Get_intervals(),
      _["candidates"] = f.Get_candidates()
      );
      
      return l;
    }
    else
    { 
      std::cout << "This sampling method is not found.";
      return List ();
    }
}


// [[Rcpp::export]]
List opPSD(std::vector<double> y, double beta, double alpha, std::vector<double>  wt)
{
  OpPSD f (y, beta, alpha, wt);
  f.Search();
  List l = List::create(
    _["changepoints"] = f.Retreive_changepoints()
  );
  return l;
}
