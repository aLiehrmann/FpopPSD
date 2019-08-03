# FpopPSD
### Arnaud Liehrmann
#### Paris Saclay University

> [Introduction](#intro)

> [Installation Notes](#instal)

> [Quick Start](#qs)

<a id="intro"></a>

## Introduction

FpopPSD is an extension of FPOP, an exact data segmentation algorithm based on functional pruning. This extension implements a penalty that depends on the size of the segments. the algorithmic objective is to solve the following optimization problem:

$$
    {{\Large{\boldsymbol{\tau}}}}_{n}^{*}=\operatorname*{arg\,min}_{{\Large{\boldsymbol{\tau}}}_{n}\in \bigcup_{0<K<n} \mathcal{M}^{K}_{1:n}}\ \left[ \displaystyle\sum_{j=1}^{K+1}  \min_{\mu} \left[ \displaystyle\sum_{i=\tau_{j-1}+1}^{\tau{j}} (y_{i} -\mu)^2 -\beta g(\tau_{j}-\tau_{j-1})\right] + \alpha |{\Large{\boldsymbol{\tau}}}_{n}|\right]
$$

<a id="instal"></a>

## Installation notes 

#### Step 1: Install the devtools package

```
install.packages("devtools")
```

#### Step 2: Install the `FpopPSD` package from GitHub

```
library(devtools)
install_github("aLiehrmann/FpopPSD")
```

#### Step 3: Load the package

```
library(FpopPSD)
```

<a id="qs"></a>

## Quick Start

#### 1) Import data 
```{r}
df <- read.table("quickstart_data/wellLogData.txt", header = T)
ggplot(df, aes(x=time, y=y))+
  geom_point(size=0.5)+
  theme_bw()
```

![ ](doc/img/data.png)

#### 2) Search the optimal changepoints for the given penalty
```
n = length(df$y)
beta <- 2.5
alpha <- 10 + beta * log(n)
res <- FpopPSD::fpopPSD(df$y, beta, alpha)
res$changepoints
```

```
 [1]    3   32   39   45   82   89   93  111  155  167  251
[12]  254  262  286  293  297  315  369  375  376  433  439
[23]  471  474  512  522  595  596  613  623  635  695  698
[34]  699  741  749  753  793  797  887  975  978 1035 1037
[45] 1098 1158 1185
```

#### 3) Plot the changepoints and the mean of segments on data
```
FpopPSD::plot_seg(res$changepoints, df$y, df$time)
```
![ ](doc/img/seg.png)

[Back to Top](#top)