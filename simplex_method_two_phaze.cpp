//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include "simplex_method_two_phaze.hpp"

namespace lp {

Matrix<double> createMatrixSimplexMethodMaxTwoPhaze(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits,
    const std::vector<OpCompare>& op, size_t rows, size_t cols, size_t sizeFunc,
    size_t countLim, size_t countMoreEq, std::vector<int>& basis) {
  Matrix<double> matr(rows, cols, 0.0);

  for (int i = 0; i < countLim; ++i)
    for (int j = 0; j < sizeFunc; ++j) matr(i, j) = limits[i][j];

  size_t indColA = sizeFunc + countLim;

  for (int i = 0, j = sizeFunc, k = indColA; i < countLim; ++i, ++j) {
    if (op[i] == OpCompare::MORE_EQ) {
      matr(i, j) = -1.0;
      matr(i, k) = 1.0;
      basis[i] = k;
      ++k;
    } else {
      matr(i, j) = 1.0;
    }
  }

  for (int i = indColA; i < indColA + countMoreEq; ++i) matr(rows - 1, i) = 1.0;
  for (int i = 0; i < rows - 1; ++i) matr(i, cols - 1) = limits[i][sizeFunc];

  return matr;
}

void firstPhaze(Matrix<double>& matr, std::vector<int>& basis,
                const std::vector<double>& func, size_t countMoreEq) {
  size_t countLim = basis.size();
  size_t sizeFunc = func.size();
  size_t rows = matr.getRows();

  if (countMoreEq != 0) {
    for (int i = 0; i < countLim; ++i)
      if (basis[i] >= sizeFunc + countLim)
        transformationRows(matr, i, basis[i]);

    calculateSimplexMethodMax(matr, basis, countLim);
  }

  for (int i = 0; i < sizeFunc; ++i) matr(rows - 1, i) = -func[i];
}

void checkBasis(Matrix<double>& matr, const std::vector<int>& basis) {
  for (int i = 0; i < basis.size(); ++i) {
    transformationRows(matr, i, basis[i]);
  }
}

std::pair<double, std::vector<double>> simplexMethodMaxTwoPhaze(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits,
    const std::vector<OpCompare>& op) {
  if (!validateSimplexMethodMax(func, limits) || limits.size() != op.size())
    return std::pair(0.0, std::vector<double>());

  size_t countMoreEq = std::count(op.begin(), op.end(), OpCompare::MORE_EQ);
  size_t countLim = limits.size();
  size_t sizeFunc = func.size();
  size_t rows = countLim + 1;
  size_t cols = sizeFunc + countLim + countMoreEq + 1;
  int indColA = -1;
  int indRowA = -1;

  auto basis = createBasisSimplexMethodMax(sizeFunc, countLim);
  auto matr = createMatrixSimplexMethodMaxTwoPhaze(
      func, limits, op, rows, cols, sizeFunc, countLim, countMoreEq, basis);

  firstPhaze(matr, basis, func, countMoreEq);
  calculateSimplexMethodMax(matr, basis, countLim);
  checkBasis(matr, basis);

  printVector(basis);
  printMatrix(matr);

  return makeResult(matr, basis, sizeFunc);
}
}  // namespace lp
