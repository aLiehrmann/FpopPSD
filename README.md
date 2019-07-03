# FpopPSD


### standard
```{r}
microbenchmark(fpopPSD(rnorm(10^5), 2.5, 10+2.5*log(10^5), "rand_one", 1, rep(1,10^5)), times=10)
```
```
Unit: seconds
                                                                          expr      min       lq     mean
fpopPSD(rnorm(10^5), 2.5, 10 + 2.5 * log(10^5), "rand_one", 1,    rep(1, 10^5)) 1.728959 1.775428 1.823862

   median       uq      max neval
 1.833681 1.859221 1.894165    10
```

### array_of_candidates
```{r}
microbenchmark(fpopPSD(rnorm(10^5), 2.5, 10+2.5*log(10^5), "rand_one", 1, rep(1,10^5)), times=10)
```
```
Unit: seconds
                                                                          expr      min       lq    mean
fpopPSD(rnorm(10^5), 2.5, 10 + 2.5 * log(10^5), "rand_one", 1,    rep(1, 10^5)) 1.869383 1.885619 1.932418

   median       uq      max neval
 1.941556 1.962582 1.994283    10
```

### Doubly_Linked_List
```{r}
microbenchmark(fpopPSD(rnorm(10^5), 2.5, 10+2.5*log(10^5), "rand_one", 1, rep(1,10^5)), times=10)
```
```
Unit: seconds
                                                                          expr      min       lq     mean
fpopPSD(rnorm(10^5), 2.5, 10 + 2.5 * log(10^5), "rand_one", 1,    rep(1, 10^5)) 1.657636 1.707535 1.733779
   median       uq      max neval
 1.729532 1.756049 1.813154    10
```