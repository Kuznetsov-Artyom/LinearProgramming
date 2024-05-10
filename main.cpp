//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include <iostream>

#include "lp.hpp"

int main(int argc, char* argv[], char** env) {
  // Примеры с обычным симплекс методом

  std::cout << "- - - - - Examples with the usual simplex method - - - - -" << std::endl;

  auto ansOne = lp::simplexMethodMax({3, 2}, {{1, 1, 4}, {1, 3, 6}});
  lp::printResultMaxSimplexMethod(ansOne);

  std::cout << "- - - - - - - - - -" << std::endl;

  auto ansTwo = lp::simplexMethodMax(
      {4, 5, 3}, {{2, 3, 1, 20}, {1, 2, 3, 25}, {2, 1, 3, 15}});
  lp::printResultMaxSimplexMethod(ansTwo);

  std::cout << "- - - - - - - - - -" << std::endl;

  auto ansThree = lp::simplexMethodMax(
      {6, 2, 2.5, 4},
      {{5, 1, 0, 2, 1000}, {1, 0, 2, 1, 150}, {4, 2, 2, 1, 600}});
  lp::printResultMaxSimplexMethod(ansThree);

  std::cout << std::endl;

  // Примеры с двухфазным симплекс методом

  std::cout << "- - - - - Examples with the two-phase simplex method - - - - -" << std::endl;

  auto ansOneTwoPhazeNotFound = lp::simplexMethodMaxTwoPhaze(
      {3, -4}, {{-2, 1, 10}, {1, 3, 12}, {3, -1, 7}},
      {lp::OpCompare::LESS_EQ, lp::OpCompare::MORE_EQ, lp::OpCompare::MORE_EQ});
  lp::printResultMaxSimplexMethod(ansOneTwoPhazeNotFound);

  std::cout << "- - - - - - - - - -" << std::endl;

  auto ansTwoTwoPhaze = lp::simplexMethodMaxTwoPhaze(
      {5, -3}, {{2, -1, 4}, {-1, 2, 1}, {2, 1, 5}},
      {lp::OpCompare::MORE_EQ, lp::OpCompare::LESS_EQ, lp::OpCompare::MORE_EQ});
  lp::printResultMaxSimplexMethod(ansTwoTwoPhaze);

  std::cout << "- - - - - - - - - -" << std::endl;

  auto ansThreeTwoPhaze = lp::simplexMethodMaxTwoPhaze(
      {6, 2, 2.5, 4},
      {{5, 1, 0, 2, 1000}, {4, 2, 2, 1, 600}, {1, 0, 2, 1, 150}},
      {lp::OpCompare::LESS_EQ, lp::OpCompare::MORE_EQ, lp::OpCompare::LESS_EQ});
  lp::printResultMaxSimplexMethod(ansThreeTwoPhaze);

  std::cout << std::endl;

  // Примеры с задачей о рюкзакe

  std::cout << "- - - - - Examples with the backpack problem - - - - -" << std::endl;

  auto ansOneBackpack = lp::fillBackpack({4, 5, 3, 7, 6}, {5, 7, 4, 9, 8}, 16);
  lp::printResultFillBackpack(ansOneBackpack);

  std::cout << "- - - - - - - - - -" << std::endl;

  auto ansTwoBackpack = lp::fillBackpack({3, 4, 6}, {2, 3, 5}, 17);
  lp::printResultFillBackpack(ansTwoBackpack);

  std::cout << std::endl;

  // Тест с обычным симплекс методом

  std::cout << "- - - - - Test with the usual simplex method - - - - -" << std::endl;

  lp::testSimplexMethodMax({ 6, 2, 2.5, 4 },
                          { {5, 1, 0, 2, 1000}, {1, 0, 2, 1, 150}, {4, 2, 2, 1, 600} });

  std::cout << std::endl;

  return 0;
}
