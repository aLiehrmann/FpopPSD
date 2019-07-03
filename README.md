# FpopPSD

### array_of_candidates
```{r}
b1 <- microbenchmark(fpopPSD(rnorm(10^5), 2.5, 10+2.5*log(10^5), "rand_one", 1, rep(1,10^5)), times=10)
```
```
Unit: seconds
                                                                          expr      min       lq    mean
fpopPSD(rnorm(10^5), 2.5, 10 + 2.5 * log(10^5), "rand_one", 1,    rep(1, 10^5)) 1.869383 1.885619 1.932418

   median       uq      max neval
 1.941556 1.962582 1.994283    10
```