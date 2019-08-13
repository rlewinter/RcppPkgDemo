#include <Rcpp.h>
using namespace Rcpp;

// Examples and information in this file are adapted from the following sources:
//   -Aditi Garg: http://heather.cs.ucdavis.edu/~matloff/158/RcppTutorial.pdf
//   -Hadley Wickham's "R Packages", website at http://r-pkgs.had.co.nz
//     -this is available on Safari Online through an NEU account
//   -Dirk Eddelbuettel: http://dirk.eddelbuettel.com/code/rcpp.html
//     -Rccp vignettes, accessible by running vignette("package-name")
//      in the R console, e.g. vignette("Rcpp-packages")
//   -Official R extensions manual:
//      https://cran.r-project.org/doc/manuals/R-exts.html
//
// You can learn more about package authoring with RStudio at:
//   http://r-pkgs.had.co.nz/
//
// Some useful keyboard shortcuts for package authoring:
//   Build and Reload Package:  'Ctrl + Shift + B'
//   Check Package:             'Ctrl + Shift + E'
//   Test Package:              'Ctrl + Shift + T'
//
// This project uses Rcpp to create an R package implemented in C++.
// Most of the behind-the-scenes work is done automatically by devtools.
//
// Never use library() or require(), since these modify the search path.
// Use the DESCRIPTION file to specify package requirements.
// Calling devtools::use_package() automatically updates DESCRIPTION.
//
// To make C++ classes available as reference classes in R with Rcpp modules,
// call Rcpp::loadRcppModules()
//
// I use Roxygen2 to manage documentation, which turns specially formatted
// comments into .Rd files. These are the help files displayed when you
// run ?foo() in the R console, where foo() is a function.
//
// Use devtools::build() to bundle up the package in a .tar.gz
// Use devtools::document() to process Roxygen2 comments
//
// Learn more about Rcpp at:
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//


// Here are some simple examples of exporting a C++ function to R and writing
// documentation with roxygen2

//' Prints "Hello, World!"
//'
//' @return None
//'
//' @examples
//' hello()
//'
// [[Rcpp::export]]
void hello() {
  Rprintf("Hello, world!\n");
}

//' Creates a list where keys are "foo" and "bar", and values are 0 and 1
//'
//' @return List("foo" = 0.0, "bar" = 1.0)
//'
//' @examples
//' hello2()
//'
// [[Rcpp::export]]
List hello2() {
  CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
  NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
  List z            = List::create( x, y ) ;

  return z ;
}

// Rcpp's functionality is provided through a set of C++ classes that wrap
// R data structures:
//   NumericVector, IntegerVector, CharacterVector, LogicalVector, int,
//   double, bool, String, IntegerMatrix, NumericMatrix, LogicalMatrix,
//   CharacterMatrix, List, DataFrame, etc.
//
// Rcpp knows how to convert from many STL data structures to their R
// equivalents, so you can return them from your functions without
// explicitly converting to R data structures.
//
// Rcpp also provides functions that work similarly to the equivalents in R:
//   any(), all(), head(), tail(), abs(), ceil(), choose(), factorial(),
//   mean(), sum(), sd(), cumsum(), match(), duplicated(), unique(), dnorm(),
//   runif(), etc.


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation. This is useful for testing.

/*** R
hello()
  hello2()
  */

// Since this project has to do with choosing algorithms for generating random
// numbers, I'll be using the R package microbenchmark to compare
// implementations.
// The next cpp chunks implement a sum function using a basic loop, and then
// using an iterator.
// In the chunk below that, the same function is implemented in R,
// and the performance results for a 1000 item vector are compared.

//' Sum NumericVector elements using C++
//'
//' @param x NumericVector to sum
//'
//' @return The sum of all elements of x as a double
//'
//' @examples
//' x <- runif(1e3)
//' print(sumC(x))
//'
// [[Rcpp::export]]
double sumC(NumericVector x) {
  int n = x.size();
  double total = 0;
  for (int i = 0; i < n; ++i) {
    total += x[i];
  }
  return total;
}

//' Sum NumericVector elements using C++ with an iterator
//'
//' @param x NumericVector to sum
//'
//' @return The sum of all elements of x as a double
//'
//' @examples
//' x <- runif(1e3)
//' print(sumI(x))
//'
// [[Rcpp::export]]
double sumI(NumericVector x) {
  double total = 0;

  NumericVector::iterator it;
  for (it = x.begin(); it != x.end(); ++it) {
    total += *it;
  }
  return total;
}

/*** R
sumR <- function(x) {
  total <- 0
  for (i in seq_along(x)) {
    total <- total + x[i]
  }
  total
}

x <- runif(1e3)
microbenchmark::microbenchmark(sumC(x), sumI(x), sumR(x))
*/















