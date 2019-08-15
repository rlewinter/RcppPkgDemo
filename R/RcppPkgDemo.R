### THESE TAGS ARE SUPER IMPORTANT FOR PACKAGES AUTHORED WITH RCPP
#' @importFrom Rcpp sourceCpp
#' @useDynLib RcppPkgDemo
NULL

#' RcppPkgDemo: An Example of Creating an R Package with Functions Implemented in C++ using Rcpp
#'
#' This project uses Rcpp to create an R package implemented in C++.
#'     I use Roxygen2 to manage documentation, which turns specially formatted
#'     comments into .Rd files. These are the help files displayed when you
#'     run ?foo() in the R console, where foo() is a function.
#'     The package consists of templated C++ functions for generating random
#'     combinatorial objects and random numbers from different distributions
#'     using algorithms described in the book Non-Uniform Random Variate Generation
#'     by Luc Devroye.
#'     Random number generators for various distributions are needed for many
#'     applications, such as sampling or modeling stochastic processes.
#'     This package provides multiple implementations of generators that come with
#'     performance trade-offs, so users can choose the implementation best suited
#'     to their needs.
#'
#' @section RcppPkgDemo functions:
#' The foo functions ...
#'
#' @docType package
#' @name RcppPkgDemo
NULL
