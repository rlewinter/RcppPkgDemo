% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{pois_junhao}
\alias{pois_junhao}
\title{pois_junhao(lambda, size)}
\usage{
pois_junhao(lambda, size)
}
\arguments{
\item{lambda}{expected value}

\item{size}{number of elements}
}
\value{
a vector of Poisson integers
}
\description{
Generate a vector of Poisson random values (Junhao, based on Knuth).
}
\details{
This algorithm can handle values of lambda up to 88.722,
  after which point it fails to terminate.
}
\examples{
pois_junhao(1,10)

}
