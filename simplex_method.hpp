//
// Copyright (c) 2024 Kuznetsov Artyom
//
#ifndef SIMPLEX_METHOD_HPP
#define SIMPLEX_METHOD_HPP

#include <cmath>
#include <limits>

#include "matrix.hpp"
#include "print_functions.hpp"

namespace lp {

void printResultMaxSimplexMethod(
    const std::pair<double, std::vector<double>>& ans);

bool isEqual(double valueOne, double valueTwo, double eps = 0.01);

void transformationRows(Matrix<double>& matr, size_t indRowBase,
                        size_t indColBase);

std::pair<double, std::vector<double>> makeResult(const Matrix<double>& matr,
                                                  const std::vector<int>& basis,
                size_t sizeFunc);

bool validateSimplexMethodMax(const std::vector<double>& func,
                              const std::vector<std::vector<double>>& limits);

Matrix<double> createMatrixSimplexMethodMax(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits, size_t rows, size_t cols,
    size_t sizeFunc, size_t countLim);

std::vector<int> createBasisSimplexMethodMax(size_t sizeFunc, size_t countLim);

void calculateSimplexMethodMax(Matrix<double>& matr, std::vector<int>& basis,
                               size_t countLim);

std::pair<double, std::vector<double>> simplexMethodMax(const std::vector<double>& func,
                      const std::vector<std::vector<double>>& limits);
}  // namespace lp

#endif  // SIMPLEX_METHOD_HPP

