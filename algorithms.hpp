//
// Copyright (c) 2024 Nogin Denis
//
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <functional>
#include <vector>

int factorial(int n);

std::vector<std::vector<std::vector<double>>> generatePermutations(
    const std::vector<std::vector<double>>& limits);

std::vector<std::vector<double>> transpose(
    const std::vector<std::vector<double>>& matrix);

#endif  // !ALGORITHMS_HPP
