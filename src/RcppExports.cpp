// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// fpopPSD
List fpopPSD(std::vector<double> y, double beta, double alpha, std::string sampling_method, int sampling_method_parameter, std::vector<double> wt);
RcppExport SEXP _FpopPSD_fpopPSD(SEXP ySEXP, SEXP betaSEXP, SEXP alphaSEXP, SEXP sampling_methodSEXP, SEXP sampling_method_parameterSEXP, SEXP wtSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type y(ySEXP);
    Rcpp::traits::input_parameter< double >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::string >::type sampling_method(sampling_methodSEXP);
    Rcpp::traits::input_parameter< int >::type sampling_method_parameter(sampling_method_parameterSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type wt(wtSEXP);
    rcpp_result_gen = Rcpp::wrap(fpopPSD(y, beta, alpha, sampling_method, sampling_method_parameter, wt));
    return rcpp_result_gen;
END_RCPP
}
// opPSD
List opPSD(std::vector<double> y, double beta, double alpha, std::vector<double> wt);
RcppExport SEXP _FpopPSD_opPSD(SEXP ySEXP, SEXP betaSEXP, SEXP alphaSEXP, SEXP wtSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type y(ySEXP);
    Rcpp::traits::input_parameter< double >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type wt(wtSEXP);
    rcpp_result_gen = Rcpp::wrap(opPSD(y, beta, alpha, wt));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_FpopPSD_fpopPSD", (DL_FUNC) &_FpopPSD_fpopPSD, 6},
    {"_FpopPSD_opPSD", (DL_FUNC) &_FpopPSD_opPSD, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_FpopPSD(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}