#' fpopPSD
#' @description fpopPSD is an extension of Fpop, an exact data segmentation algorithm based on functionnal pruning. This extension implements a penalty that depends on the size of the segments.
#' @param y a vector of data ordered according to an attribute
#' @param beta a coefficient used in the calculation of the penalty (recommended: 2.5)
#' @param alpha a constant used in the calculation of the penalty (recommended: 10+2.5*log(length(y)))
#' @param sampling_method a sampling method for candidates ("rand_one", "last", "rand_with_replacement", "rand_without_replacement", "all", "only")
#' @param param_method a parameter used by the sampling method
#' @param wt a vector of weight linked to the data
#' @return a list with the changepoints and the number of intervals/candidates at each step

fpopPSD <- function(y, beta, alpha, sampling_method="rand_one", sampling_method_parameter=1, wt=-1)
    {
        if (wt==-1)
        {
            wt = rep(1,length(y));
        }
        return (fpopPSD_cpp(y, beta, alpha, sampling_method, sampling_method_parameter, wt))
    }

#' opPSD
#' @description opPSD is the same method as fpopPSD without the pruning step.
#' @param y a vactor of data ordered according to an attribute
#' @param beta a coefficient used in the calculation of the penalty (recommended: 2.5)
#' @param alpha a constant used in the calculation of the penalty (recommended: 10+2.5*log(length(y)))
#' @param wt a vector of weight linked to the data
#' @return a list with the changepoints and the number of intervals/candidates at each step


opPSD <- function(y, beta, alpha, wt=-1)
    {
        if (wt==-1)
        {
            wt = rep(1,length(y));
        }
        return (opPSD_cpp(y, beta, alpha, wt))
    }
