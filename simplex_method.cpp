//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include "simplex_method.hpp"

namespace lp {

void testSimplexMethodMax(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits) {
    if (!lp::validateSimplexMethodMax(func, limits))
        return;

    size_t countLim = limits.size();
    size_t sizeFunc = func.size();
    size_t rows = countLim + 1;
    size_t cols = sizeFunc + countLim + 1;
    int numTests = factorial(sizeFunc);

    std::vector<std::vector<double>> colLimits = limits;

    for (int i = 0; i < colLimits.size(); ++i)
        colLimits[i].pop_back();

    colLimits = transpose(colLimits);

    for (int i = 0; i < colLimits.size(); ++i)
        colLimits[i].push_back(func[i]);

    /*std::cout << "limits" << std::endl;
    for (auto vec : limits) {
        for (auto elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "colLimits" << std::endl;
    for (auto vec : colLimits) {
        for (auto elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }*/

    std::vector<std::vector<std::vector<double>>> permutations;
    std::vector<std::vector<double>> permutationsFunc;
    permutations = generatePermutations(colLimits);

    /*std::cout << "permutations" << std::endl;
    for (int k = 0; k < permutations.size(); ++k) {
        for (int i = 0; i < permutations[k].size(); ++i) {
            for (int j = 0; j < permutations[k][i].size(); ++j) {
                std::cout << permutations[k][i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }*/

    for (int k = 0; k < permutations.size(); ++k) {
        permutations[k] = transpose(permutations[k]);
        permutationsFunc.push_back(permutations[k][permutations[k].size() - 1]);
        permutations[k].pop_back();
        for (int i = 0; i < permutations[k].size(); ++i) {
            permutations[k][i].push_back(limits[i][limits[i].size() - 1]);
        }
    }

    /*std::cout << "permutations (newLimits): " << std::endl;
    for (int k = 0; k < permutations.size(); ++k) {
        for (int i = 0; i < permutations[k].size(); ++i) {
            for (int j = 0; j < permutations[k][i].size(); ++j) {
                std::cout << permutations[k][i][j] << " ";
            }
            std::cout << "\n";
        }
        for (auto p : permutationsFunc[k]) {
            std::cout << p << " ";
        }
        std::cout << std::endl << std::endl;
    }*/

    /*std::cout << "permutations2: " << std::endl;
    for (auto& perm : permutations) {
        for (auto& vec : perm) {
            for (auto& elem : vec) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
    std::cout << "permutationsFunc: " << std::endl;
    for (auto& vec : permutationsFunc) {
        for (auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }*/

    for (int i = 0; i < numTests; ++i) {
        std::cout << "- - - - - - - - - - - - - TEST " << i + 1 << 
            " - - - - - - - - - - - - -" << std::endl;

        auto basis = lp::createBasisSimplexMethodMax(sizeFunc, countLim);
        auto matr = lp::createMatrixSimplexMethodMax(permutationsFunc[i], permutations[i], rows, cols, sizeFunc,
            countLim);

        lp::calculateSimplexMethodMax(matr, basis, countLim);

        auto result = lp::makeResult(matr, basis, sizeFunc);

        lp::printResultMaxSimplexMethod(result);
        std::cout << "- - - - - - - - - - - - - - - - -" <<
            " - - - - - - - - - - - - -" << std::endl;
    }
}

void printResultMaxSimplexMethod(
    const std::pair<double, std::vector<double>>& ans) {
  size_t sizeFunc = ans.second.size();

  for (int i = 0; i < sizeFunc; ++i)
    std::cout << 'x' << i + 1 << ": " << ans.second[i] << '\n';
  std::cout << "max: " << ans.first << '\n';
}

bool isEqual(double valueOne, double valueTwo, double eps) {
  return std::fabs(valueOne - valueTwo) <= eps;
}

void transformationRows(Matrix<double>& matr, size_t indRowBase,
                        size_t indColBase) {
  size_t rows = matr.getRows();
  size_t cols = matr.getCols();

  for (int i = 0; i < rows; ++i) {
    if (i != indRowBase) {
      double value = matr(i, indColBase);

      if (isEqual(value, 0.0)) continue;

      if (value > 0.0) {
        for (int j = 0; j < cols; ++j)
          matr(i, j) = matr(i, j) - value * matr(indRowBase, j);
      } else {
        value = std::fabs(value);

        for (int j = 0; j < cols; ++j)
          matr(i, j) = matr(i, j) + value * matr(indRowBase, j);
      }
    }
  }
}

std::pair<double, std::vector<double>> makeResult(const Matrix<double>& matr,
                                                  const std::vector<int>& basis,
                                                  size_t sizeFunc) {
  size_t rows = matr.getRows();
  size_t cols = matr.getCols();
  size_t countLim = basis.size();

  double max = matr(rows - 1, cols - 1);
  std::vector<double> result(sizeFunc, 0.0);

  for (int i = 0; i < countLim; ++i) {
    int ind = basis[i];

    if (ind < sizeFunc) result[ind] = matr(i, cols - 1);
  }

  return std::pair(max, result);
}

bool validateSimplexMethodMax(const std::vector<double>& func,
                              const std::vector<std::vector<double>>& limits) {
  size_t sizeFunc = func.size();

  if (func.empty() || limits.empty()) return false;

  for (const auto& row : limits)
    if (row.size() - 1 != sizeFunc) return false;

  return true;
}

Matrix<double> createMatrixSimplexMethodMax(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits, size_t rows, size_t cols,
    size_t sizeFunc, size_t countLim) {
  Matrix<double> matr(rows, cols, 0.0);

  for (int i = 0; i < countLim; ++i)
    for (int j = 0; j < sizeFunc; ++j) matr(i, j) = limits[i][j];

  for (int i = 0, j = sizeFunc; i < countLim; ++i, ++j) matr(i, j) = 1.0;
  for (int i = 0; i < sizeFunc; ++i) matr(rows - 1, i) = -func[i];
  for (int i = 0; i < rows - 1; ++i) matr(i, cols - 1) = limits[i][sizeFunc];

  return matr;
}

std::vector<int> createBasisSimplexMethodMax(size_t sizeFunc, size_t countLim) {
  std::vector<int> basis(countLim, 0);

  for (int i = 0; i < countLim; ++i) basis[i] = sizeFunc + i;

  return basis;
}

void calculateSimplexMethodMax(Matrix<double>& matr, std::vector<int>& basis,
                               size_t countLim) {
  size_t rows = matr.getRows();
  size_t cols = matr.getCols();

  while (true) {
    printVector(basis);
    printMatrix(matr);

    int indCol = -1;
    int indRow = -1;

    // Ищем первый попавшийся отрицательный элемент
    for (int i = 0; i < cols - 2; ++i) {
      if (matr(rows - 1, i) < 0.0) {
        indCol = i;
        break;
      }
    }

    // Если не нашли отр элемент, то план оптимален
    if (indCol == -1) {
      std::cout << "Found optimal plan.\n";
      break;
    }

    bool ratioExist = false;
    bool nearZero = false;
    int minBasisIndCol = -1;
    double minRatio = std::numeric_limits<double>::max();

    // Ищем базисный элемент по минимальному положительному отношению
    for (int i = 0; i < countLim; ++i) {
      double ratio = 0.0;

      // Если делимое не равно нулю, выполняем вычисление отношения
      if (!isEqual(matr(i, indCol), 0.0)) {
        if (isEqual(matr(i, cols - 1), 0.0) && matr(i, indCol) > 0.0)
          nearZero = true;

        ratio = matr(i, cols - 1) / matr(i, indCol);
      }

      if (ratio > 0.0 || nearZero) {
        ratioExist = true;
        nearZero = false;

        // Если есть одинаковые отношения, берем тот, у которого меньший индекс
        // базисной переменной
        if (isEqual(ratio, minRatio)) {
          int currBasisIndCol = basis[i];

          if (currBasisIndCol < minBasisIndCol) {
            minBasisIndCol = currBasisIndCol;
            indRow = i;
          }
        }

        if (ratio < minRatio) {
          minRatio = ratio;
          indRow = i;
          minBasisIndCol = basis[i];
        }
      }
    }

    // Если все отношения недопустимые, то оптимального плана нет
    if (!ratioExist) {
      std::cout << "Not found optimal plan.\n";
      break;
    }

    // Если выбранный элемент в качестве базисного != 1, то преобразуем всю
    // строку деля на этот элемент
    if (!isEqual(matr(indRow, indCol), 1.0)) {
      double value = matr(indRow, indCol);

      for (int i = 0; i < cols; ++i) matr(indRow, i) /= value;
    }

    // Записываем, какая переменная становится базисной на данном шаге
    basis[indRow] = indCol;

    // Выполняем преобразование строк
    transformationRows(matr, indRow, indCol);
  }
}

std::pair<double, std::vector<double>> simplexMethodMax(
    const std::vector<double>& func,
    const std::vector<std::vector<double>>& limits) {
  // Необходимые проверки (валидация)
  if (!validateSimplexMethodMax(func, limits))
    return std::pair(0.0, std::vector<double>());

  size_t countLim = limits.size();
  size_t sizeFunc = func.size();
  size_t rows = countLim + 1;
  size_t cols = sizeFunc + countLim + 1;

  // Создаем симплекс таблицу и массив для базиса
  auto matr = createMatrixSimplexMethodMax(func, limits, rows, cols, sizeFunc,
                                           countLim);
  auto basis = createBasisSimplexMethodMax(sizeFunc, countLim);

  calculateSimplexMethodMax(matr, basis, countLim);

  return makeResult(matr, basis, sizeFunc);
}
}  // namespace lp
