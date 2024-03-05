//
// Copyright (c) 2024 Kuznetsov Artyom
//
#ifndef PRINT_FUNCTIONS_HPP
#define PRINT_FUNCTIONS_HPP

#include <iostream>
#include <iomanip>
#include "matrix.hpp"

template <typename T>
void printMatrix(const Matrix<T>& matr) {
  size_t rows = matr.getRows();
  size_t cols = matr.getCols();

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j)
      std::cout << matr(i, j) << '\t';
    std::cout << '\n';
  }

  std::cout << '\n';
}

template <typename T>
void printVector(const std::vector<T>& elems) {
  for (const auto& elem : elems) std::cout << elem << ' ';
  std::cout << '\n';
}

#endif  // !PRINT_FUNCTIONS_HPP
