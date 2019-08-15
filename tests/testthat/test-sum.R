context("test-sum")

test_that("sum examples work", {
  expect_equal(sumC(1:10), 55)
  expect_equal(sumI(1:10), 55)
})
