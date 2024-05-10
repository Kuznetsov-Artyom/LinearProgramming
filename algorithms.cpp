//
// Copyright (c) 2024 Nogin Denis
//
#include "algorithms.hpp"

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

std::vector<std::vector<std::vector<double>>> generatePermutations(
    const std::vector<std::vector<double>>& limits) {
    std::vector<std::vector<std::vector<double>>> result;

    // Рекурсивная функция для генерации перестановок
    std::function<void(std::vector<std::vector<double>>, size_t)> permute =
        [&](std::vector<std::vector<double>> current, size_t index) {
        if (index == current.size()) {
            result.push_back(current);
            return;
        }

        for (size_t i = index; i < current.size(); ++i) {
            std::swap(current[index], current[i]);
            permute(current, index + 1);
            std::swap(current[index], current[i]);
        }
        };

    // Вызов рекурсивной функции для начального вектора
    permute(limits, 0);

    return result;
}

std::vector<std::vector<double>> transpose(
    const std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<double>> transposed;
    if (matrix.empty())
        return transposed;

    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();

    transposed.resize(cols, std::vector<double>(rows));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}
