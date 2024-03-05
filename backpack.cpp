//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include "backpack.hpp"

namespace lp {

void printResultFillBackpack(const std::pair<int, std::vector<int>>& p) {
  std::cout << "max: " << p.first << '\n';

  for (int i = 0; i < p.second.size(); ++i) {
    std::cout << 'x' << i + 1 << ": " << p.second[i] << '\n';
  }
}

std::pair<int, std::vector<int>> fillBackpack(const std::vector<int>& weight,
                                              const std::vector<int>& price,
                                              int capacity) {
  if (weight.size() != price.size() || weight.size() <= 1 || capacity < 1)
    return std::pair(0, std::vector<int>());

  int countElem = weight.size();
  Matrix<int> matr(countElem, capacity);

  for (int i = 0; i < capacity; ++i)
    matr(0, i) = price[0] * ((i + 1) / weight[0]);

  for (int i = 1; i < countElem; ++i) {
    for (int j = 0; j < capacity; ++j) {
      int tmp = j + 1 - weight[i];
      matr(i, j) =
          std::max(matr(i - 1, j), tmp == 0  ? price[i]
                                   : tmp > 0 ? matr(i, tmp - 1) + price[i]
                                             : 0);
    }
  }

  printMatrix(matr);

  int max = matr(countElem - 1, capacity - 1);
  std::vector<int> ansX(countElem, 0);

  for (int i = countElem - 1, j = capacity - 1; i > 0 && j > 0;) {
    if (matr(i - 1, j) != matr(i, j)) {
      ++ansX[i];
      j -= weight[i];
    } else {
      --i;
      if (i == 0) ansX[i] = (j + 1) / weight[i];
    }
  }

  return std::pair(max, ansX);
}
}  // namespace lp
