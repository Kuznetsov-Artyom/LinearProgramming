//
// Copyright (c) 2024 Kuznetsov Artyom
//
#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <utility>
#include <vector>

#include "matrix.hpp"
#include "print_functions.hpp"

namespace lp {

void printResultFillBackpack(const std::pair<int, std::vector<int>>& p);
std::pair<int, std::vector<int>> fillBackpack(const std::vector<int>& weight,
                                              const std::vector<int>& price,
                                              int capacity);
}  // namespace lp

#endif  // BACKPACK_HPP
