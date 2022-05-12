cmake_minimum_required(VERSION 3.10)
project(gene_gpio)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  include/gene_gpio
)

add_executable(gene_gpio src/gpio_test.cpp
  src/gene_gpio.cpp
)
