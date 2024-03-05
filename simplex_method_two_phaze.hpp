//
// Copyright (c) 2024 Kuznetsov Artyom
//
#ifndef SIMPLEX_METHOD_TWO_PHAZE_HPP
#define SIMPLEX_METHOD_TWO_PHAZE_HPP

#include "simplex_method.hpp"

enum class test;

namespace lp {

enum class OpCompare { LESS_EQ, MORE_EQ };

Matrix<double> createMatrixSimplexMethodMaxTwoPhaze(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits,
    const std::vector<OpCompare>& op, size_t rows, size_t cols, size_t sizeFunc,
    size_t countLim, size_t countMoreEq, std::vector<int>& basis);

void firstPhaze(Matrix<double>& matr, std::vector<int>& basis,
                const std::vector<double>& func, size_t countMoreEq);

void checkBasis(Matrix<double>& matr, const std::vector<int>& basis);

std::pair<double, std::vector<double>> simplexMethodMaxTwoPhaze(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits,
    const std::vector<OpCompare>& op);
}  // namespace lp

#endif  // SIMPLEX_METHOD_TWO_PHAZE_HPP
