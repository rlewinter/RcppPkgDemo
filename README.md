
## About

This project uses Rcpp to create an R package implemented in C++.
I use Roxygen2 to manage documentation, which turns specially formatted
comments into .Rd files. These are the help files displayed when you
run ?foo() in the R console, where foo() is a function. 

The package consists of C++ functions for generating random numbers from the Poisson
distribution using algorithms described in the book Non-Uniform Random Variate Generation 
by Luc Devroye.

Random number generators for various distributions are needed for many 
applications, such as sampling or modeling stochastic processes. 

This project is intended as an exercise in package development with C++ for R.
It is also a good reference and reusable foundation, since the options and setup
reflect the type of requirements I'll most likely encounter in future projects.

RcppPkgDemo uses standard R Documentation accessible at the console with the
? prefix, e.g. ?hello displays documentation for hello()

### Package Development Tips

Some useful keyboard shortcuts for package authoring:

* Build and Reload Package:  'Ctrl + Shift + B'

* Check Package:             'Ctrl + Shift + E'

* Test Package:              'Ctrl + Shift + T'

This project uses Rcpp to create an R package implemented in C++.
Most of the behind-the-scenes work is done automatically by devtools.

Note: after creating a project with initial files for making a package,
run usethis::use_rcpp() to set up the package for Rcpp.

To set up the package for testing with testthat, run usethis::use_testthat().

To create a skeleton test file, run usethis::use_test("name").

To run all tests for the package, run devtools::test().

Never use library() or require(), since these modify the search path.

Use the DESCRIPTION file to specify package requirements.

Calling usethis::use_package() automatically updates DESCRIPTION.

To make C++ classes available as reference classes in R with Rcpp modules,
call Rcpp::loadRcppModules().

I use roxygen2 to manage documentation, which turns specially formatted
comments into .Rd files. These are the help files displayed when you
run ?foo() in the R console, where foo() is a function.

Use devtools::document() to process roxygen2 comments.

Run Rcpp::compileAttributes() whenever functions are added, removed, or
have their signatures changed. This is automatically done when the package
is built if you are building with RStudio or devtools.

Use devtools::build() to bundle up the package in a .tar.gz

Rcpp's functionality is provided through a set of C++ classes that wrap
R data structures:
  NumericVector, IntegerVector, CharacterVector, LogicalVector, int,
  double, bool, String, IntegerMatrix, NumericMatrix, LogicalMatrix,
  CharacterMatrix, List, DataFrame, etc.

Rcpp knows how to convert from many STL data structures to their R
equivalents, so you can return them from your functions without
explicitly converting to R data structures.

Rcpp also provides functions that work similarly to the equivalents in R:
  any(), all(), head(), tail(), abs(), ceil(), choose(), factorial(),
  mean(), sum(), sd(), cumsum(), match(), duplicated(), unique(), dnorm(),
  runif(), etc.

Learn more about Rcpp at:

* http://www.rcpp.org/

* http://adv-r.had.co.nz/Rcpp.html

* http://gallery.rcpp.org/

Some examples and information in this demo are adapted from the following sources:

* Aditi Garg: http://heather.cs.ucdavis.edu/~matloff/158/RcppTutorial.pdf

* Hadley Wickham's "R Packages", website at http://r-pkgs.had.co.nz --- book available on Safari Online through an NEU account

* Dirk Eddelbuettel: http://dirk.eddelbuettel.com/code/rcpp.html --- Rcpp vignettes, accessible by running vignette("package-name") in the R console, e.g. vignette("Rcpp-packages")

* Official R extensions manual:
  https://cran.r-project.org/doc/manuals/R-exts.html

## Installation

The package is available for download from GitHub, which is easily done with
devtools (see code chunk below).

Since this project has to do with choosing algorithms for generating random
numbers, I'll be using the R package microbenchmark to compare implementations,
so the following code chunk also installs and loads the microbenchmark package.

```{r install, results='hide', message=FALSE, warning=FALSE}
if (!"devtools" %in% rownames(installed.packages())) {
  install.packages("devtools")
}
devtools::install_github("rlewinter/RcppPkgDemo")
library(RcppPkgDemo)

if (!"microbenchmark" %in% rownames(installed.packages())) {
  install.packages("microbenchmark")
}
library(microbenchmark)
```

## Example comparison of vector summation functions

In RcppPkgDemo, I've implemented 2 versions of a function that loops through
a numeric vector and returns the sum of all items.

- sumC is implemented in C++ and uses a standard loop 

- sumI is implemented in C++ and uses an iterator

Now let's write a function sumR in R that uses the same strategy as sumC:

```{r sumR}
sumR <- function(x) {
  total <- 0
  for (i in seq_along(x)) {
    total <- total + x[i]
  }
  total
}
```

And now compare the performance results on a 1000 item vector:

```{r sum_comparisons}
x <- runif(1e3)
knitr::kable(summary(microbenchmark(sumC(x), sumI(x), sumR(x))), caption="Comparison of Vector Summations (Microseconds)")
```

## Comparison of RcppPkgDemo functions for generating Poisson values

Functions:

* pois_knuth - For each value generated, algorithmic complexity is proportional to parameter lambda. Underflow occurs for lambda greater than 103.972, resulting in junk data.

* pois_junhao - Based on Knuth. This algorithm can handle values of lambda up to 88.722,
after which point it fails to terminate. This is strange because it is intended to handle larger
lambda than Knuth.

* pois_iss - Uses inversion by sequential search. Fails to terminate for lambda greater than 102.873.

* pois_mult - Uses multiplication of uniform random variates.
Underflows for lambda greater than 103.972, resulting in junk data.

* pois_eit - Uses exponential inter-arrival times. Works for large values of lambda,
presumably due to use of an exponential random variate instead of uniform, like every
other function, since this does not require storage of very small numbers.

```{r poisson_comparisons}
knitr::kable(summary(microbenchmark(pois_mult(1, 100000), pois_knuth(1, 100000), pois_eit(1, 100000), pois_iss(1, 100000), pois_junhao(1, 100000))), caption = "Comparison of Poisson Generators (Milliseconds)")
```




