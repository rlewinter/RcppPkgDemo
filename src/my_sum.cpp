#include <Rcpp.h>
using namespace Rcpp;

// Since this project has to do with choosing algorithms for generating random
// numbers, I'll be using the R package microbenchmark to compare
// implementations.
// The next cpp chunks implement a sum function using a basic loop, and then
// using an iterator.
// In the chunk below that, the same function is implemented in R,
// and the performance results for a 1000 item vector are compared.

//' sumC
//' Sum vector elements using C++
//'
//' @param x vector to sum
//'
//' @return The sum of all elements of x as a double
//'
//' @examples
//' x <- runif(1e3)
//' print(sumC(x))
//'
//' @export
// [[Rcpp::export(rng=false)]]
double sumC(NumericVector x) {
  int n = x.size();
  double total = 0;
  for (int i = 0; i < n; ++i) {
    total += x[i];
  }
  return total;
}

//' sumI
//'
//' Sum vector elements using C++ with an iterator
//'
//' @param x vector to sum
//'
//' @return The sum of all elements of x as a double
//'
//' @examples
//' x <- runif(1e3)
//' print(sumI(x))
//'
//' @export
// [[Rcpp::export(rng=false)]]
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
