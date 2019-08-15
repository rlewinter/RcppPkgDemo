context("test-hello")

test_that("hello works", {
  expect_output(hello(), regexp="Hello, world!")
})

test_that("hello2 works", {
  expect_type(hello2(), "list")
  expect_identical(hello2(), list(c("foo", "bar"), c(0.0, 1.0)))
})
