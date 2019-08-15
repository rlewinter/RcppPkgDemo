#include <Rcpp.h>
using namespace Rcpp;

// Here are some simple examples of exporting a C++ function to R and writing
// documentation with roxygen2

//' hello
//'
//' hey hi hello
//'
//' @return "Hello, world!"
//'
//' @examples
//' hello()
//'
//' @export
// [[Rcpp::export(rng=false)]]
void hello() {
  Rprintf("Hello, world!\n");
}

//' hello2
//'
//' Creates a list where keys are "foo" and "bar", and values are 0 and 1
//'
//' @return List("foo" = 0.0, "bar" = 1.0)
//'
//' @examples
//' hello2()
//'
//' @export
// [[Rcpp::export(rng=false)]]
List hello2() {
  CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
  NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
  List z            = List::create( x, y ) ;

  return z ;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation. This is useful for testing.

/*** R
hello()
hello2()
*/















