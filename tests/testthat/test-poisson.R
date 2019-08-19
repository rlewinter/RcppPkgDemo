context("test-poisson")

test_that("poisson generators return properly sized vector", {
  expect_length(pois_knuth(1, 10), 10)
  expect_length(pois_junhao(1, 10), 10)
  expect_length(pois_iss(1, 10), 10)
  expect_length(pois_eit(1, 10), 10)
  expect_length(pois_mult(1, 10), 10)
})
