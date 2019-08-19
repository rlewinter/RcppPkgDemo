#include <Rcpp.h>
using namespace Rcpp;

//' pois_knuth(lambda, size)
//'
//' Generate a vector of Poisson random values (Knuth).
//'
//' @details
//' For each value generated, algorithmic complexity is proportional to
//'   parameter lambda. Underflow occurs for lambda greater than 103.972,
//'   resulting in junk data.
//'
//' @param lambda expected value
//'
//' @param size number of elements
//'
//' @return a vector of Poisson integers
//'
//' @examples
//' pois_knuth(1, 10)
//'
//' @export
// [[Rcpp::export]]
IntegerVector pois_knuth(float lambda, unsigned int size) {
  IntegerVector res(size);

  for (unsigned int i = 0; i < size; i++) {
    unsigned int k = 0;
    double p = 1.0;
    double limit = std::exp(-lambda);

    do {
      k++;
      p *= R::runif(0, 1);
    } while (p > limit);

    res[i] = k - 1;
  }

  return res;
}

//' pois_junhao(lambda, size)
//'
//' Generate a vector of Poisson random values (Junhao, based on Knuth).
//'
//' @details
//' This algorithm can handle values of lambda up to 88.722,
//'   after which point it fails to terminate.
//'
//' @param lambda expected value
//'
//' @param size number of elements
//'
//' @return a vector of Poisson integers
//'
//' @examples
//' pois_junhao(1,10)
//'
//' @export
// [[Rcpp::export]]
IntegerVector pois_junhao(float lambda, unsigned int size) {
  unsigned int STEP = 500;
  IntegerVector res(size);

  for (unsigned int i = 0; i < size; i++) {
    float left = lambda;
    unsigned int k = 0;
    double p = 1.0;

    do {
      k++;
      p *= R::runif(0, 1);

      while (p < 1 && left > 0) {
        if (left > STEP) {
          p *= std::exp(STEP);
          left -= STEP;
        } else {
          p *= std::exp(left);
          left = 0;
        }
      }

      Rcpp::checkUserInterrupt();
    } while (p > 1);

    res[i] = k - 1;
  }

  return res;
}

//' pois_iss(lambda, size)
//'
//' Generate a vector of Poisson random values using inversion by sequential
//'   search (Devroye).
//'
//' @details
//' Fails to terminate for lambda greater than 102.873.
//'
//' @param lambda expected value
//'
//' @param size number of elements
//'
//' @return a vector of Poisson integers
//'
//' @examples
//' pois_iss(1, 10)
//'
//' @export
// [[Rcpp::export]]
IntegerVector pois_iss(float lambda, unsigned int size) {
  IntegerVector res(size);

  for (unsigned int i = 0; i < size; i++) {
    unsigned int k = 0;
    double p = std::exp(-lambda);
    double s = p;
    double u = R::runif(0, 1);

    while (u > s) {
      k++;
      p *= lambda / k;
      s += p;
      Rcpp::checkUserInterrupt();
    }

    res[i] = k;
  }

  return res;
}

//' pois_mult(lambda, size)
//'
//' Generate a vector of Poisson random values using multiplication
//'   of uniform random variates (Devroye).
//'
//' @details
//' Underflows for lambda greater than 103.972, resulting in junk data.
//'
//' @param lambda expected value
//'
//' @param size number of elements
//'
//' @return a vector of Poisson integers
//'
//' @examples
//' pois_mult(1, 10)
//'
//' @export
// [[Rcpp::export]]
IntegerVector pois_mult(float lambda, unsigned int size) {
  IntegerVector res(size);
  double limit = std::exp(-lambda);

  for (unsigned int i = 0; i < size; i++) {
    unsigned int k = 0;
    double prod = 1.0;

    while (1) {
      prod *= R::runif(0, 1);

      if (prod > limit) {
        k++;
      } else {
        res[i] = k;
        break;
      }
    }
  }

  return res;
}

//' pois_eit(lambda, size)
//'
//' Generate a vector of Poisson random values based upon exponential
//'   inter-arrival times (Devroye).
//'
//' @details
//' Works for large values of lambda.
//'
//' @param lambda expected value
//'
//' @param size number of elements
//'
//' @return a vector of Poisson integers
//'
//' @examples
//' pois_eit(1, 10)
//'
//' @export
// [[Rcpp::export]]
IntegerVector pois_eit(double lambda, unsigned int size) {
  IntegerVector res(size);

  for (unsigned int i = 0; i < size; i++) {
    unsigned int k = 0;
    double sum = 0.0;

    while (1) {
      sum += R::rexp(1);

      if (sum < lambda) {
        k++;
      } else {
        res[i] = k;
        break;
      }
    }
  }

  return res;
}

