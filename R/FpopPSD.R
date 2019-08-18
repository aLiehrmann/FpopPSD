#' fpopPSD
#' @description fpopPSD is an extension of Fpop, an exact data segmentation algorithm based on functionnal pruning. This extension implements a penalty that depends on the size of the segments.
#' @param y a vector of data ordered according to an attribute
#' @param beta a coefficient used in the calculation of the penalty (recommended: 2.5)
#' @param alpha a constant used in the calculation of the penalty (recommended: 10+2.5*log(length(y)))
#' @param sampling_method a sampling method for candidates ("rand_one", "last", "rand_with_replacement", "rand_without_replacement", "all", "only")
#' @param sampling_method_parameter a parameter used by the sampling method
#' @param wt a vector of weight linked to the data
#' @examples
#' path_to_FpopPSD <- path.package("FpopPSD")
#' df <- read.table(paste0(path_to_FpopPSD,"/wellLogData.txt"), header = TRUE)
#' n <- length(df$y)
#' beta <- 2.5
#' alpha <- 10 + beta * log(n)
#' res <- FpopPSD::fpopPSD(df$y, beta, alpha)
#' res$changepoints
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
#' @param y a vector of data ordered according to an attribute
#' @param beta a coefficient used in the calculation of the penalty (recommended: 2.5)
#' @param alpha a constant used in the calculation of the penalty (recommended: 10+2.5*log(length(y)))
#' @param wt a vector of weight linked to the data
#' @examples
#' path_to_FpopPSD <- path.package("FpopPSD")
#' df <- read.table(paste0(path_to_FpopPSD,"/wellLogData.txt"), header = TRUE)
#' n <- length(df$y)
#' beta <- 2.5
#' alpha <- 10 + beta * log(n)
#' res <- FpopPSD::opPSD(df$y, beta, alpha)
#' res$changepoints
#' @return a list with the changepoints and the number of intervals/candidates at each step


opPSD <- function(y, beta, alpha, wt=-1)
    {
        if (wt==-1)
        {
            wt = rep(1,length(y));
        }
        return (opPSD_cpp(y, beta, alpha, wt))
    }


#' plot_seg
#' @description plot the changepoints and the mean of the segments on the data.
#' @param cp a vector of changepoints
#' @param y a vector of data
#' @param x a vector of data abscissa
#' @examples
#' library(ggplot2)
#' path_to_FpopPSD <- path.package("FpopPSD")
#' df <- read.table(paste0(path_to_FpopPSD,"/wellLogData.txt"), header = TRUE)
#' n <- length(df$y)
#' beta <- 2.5
#' alpha <- 10 + beta * log(n)
#' res <- FpopPSD::fpopPSD(df$y, beta, alpha)
#' FpopPSD::plot_seg(res$changepoints, df$y, df$time)

plot_seg <- function(cp, y, x){
  cp_temp <- c(1, cp, length(y))
  mean_seg <- unlist(lapply(2:length(cp_temp), function(i){mean(y[cp_temp[i-1]:cp_temp[i]])}))
  df_mean_of_infered_segments <- data.frame(x = cp_temp[-length(cp_temp)], y=mean_seg, xend=cp_temp[-1], yend=mean_seg)
  df <- data.frame(y=y, x=x)
  ggplot(data = df, aes(y=y, x=x)) +
    geom_point(size=0.5) +
    geom_segment(data = df_mean_of_infered_segments, aes(x=x, y=y, xend=xend, yend=yend), colour="blue", size=1.5) +
    geom_vline(xintercept = cp, colour="red") +
    theme_bw()
}
