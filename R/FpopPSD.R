fpopPSD <- function(y, beta, alpha, sampling_method="rand_one", sampling_method_parameter=1, wt=-1)
    {
        if (wt==-1)
        {
            wt = rep(1,length(y));
        }
        return (fpopPSD_cpp(y, beta, alpha, sampling_method, sampling_method_parameter, wt))
    }

opPSD <- function(y, beta, alpha, wt=-1)
    {
        if (wt==-1)
        {
            wt = rep(1,length(y));
        }
        return (opPSD_cpp(y, beta, alpha, wt))
    }
