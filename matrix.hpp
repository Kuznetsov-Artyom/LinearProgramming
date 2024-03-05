//
// Copyright (c) 2024 Kuznetsov Artyom
//
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

template <typename T>
class Matrix {
 private:
  std::vector<T> mMatr;
  size_t mRows;
  size_t mCols;

 public:
  using type = typename T;

  Matrix() = default;
  Matrix(size_t rows, size_t cols, T val = T());
  Matrix(const Matrix&) = default;
  Matrix(Matrix&&) = default;
  ~Matrix() = default;

  Matrix& operator=(const Matrix&) = default;
  Matrix& operator=(Matrix&&) = default;

  [[nodiscard]] T& operator()(size_t row, size_t col);
  [[nodiscard]] const T& operator()(size_t row, size_t col) const;

  [[nodiscard]] bool empty() const noexcept(noexcept(mMatr.empty()));
  [[nodiscard]] size_t getRows() const noexcept { return mRows; }
  [[nodiscard]] size_t getCols() const noexcept { return mCols; }

  void reset(size_t rows = 0, size_t cols = 0, T val = T());
  void fill(T val);
};

template <typename T>
inline Matrix<T>::Matrix(size_t rows, size_t cols, T val) : Matrix() {
  if (rows == 0 || cols == 0) return;

  mRows = rows;
  mCols = cols;
  
  mMatr.resize(mRows * mCols, val);
}

template<typename T>
[[nodiscard]] inline T& Matrix<T>::operator()(size_t row, size_t col) {
  return mMatr[row * mCols + col];
}
template<typename T>
[[nodiscard]] inline const T& Matrix<T>::operator()(size_t row, size_t col) const {
  return mMatr[row * mCols + col];
}

template<typename T>
[[nodiscard]] inline bool Matrix<T>::empty() const noexcept(noexcept(mMatr.empty())) {
  return mMatr.empty();
}

template<typename T>
inline void Matrix<T>::reset(size_t rows, size_t cols, T val) {
  if (rows == 0 || cols == 0) {
    mRows = mCols = 0;
    mMatr.clear();
  } else {
    mRows = rows;
    mCols = cols;
    mMatr.resize(mRows * mCols, val);
  }
}

template<typename T>
inline void Matrix<T>::fill(T val) {
  for (auto& elem : mMatr) elem = val;
}

#endif  // !MATRIX_HPP
