//
// Copyright (c) 2024 Kuznetsov Artyom
//
#include <iostream>

#include "lp.hpp"

int main(int argc, char* argv[], char** env) {
  auto ansOne = lp::simplexMethodMax(
      {6, 2, 2.5, 4},
      {{5, 1, 0, 2, 1000}, {1, 0, 2, 1, 150}, {4, 2, 2, 1, 600}});
  lp::printResultMaxSimplexMethod(ansOne);

  auto ansTwo = lp::simplexMethodMaxTwoPhaze(
      {6, 2, 2.5, 4},
      {{5, 1, 0, 2, 1000}, {4, 2, 2, 1, 600}, {1, 0, 2, 1, 150}},
      {lp::OpCompare::LESS_EQ, lp::OpCompare::LESS_EQ, lp::OpCompare::LESS_EQ});
  lp::printResultMaxSimplexMethod(ansTwo);


  auto ans = lp::fillBackpack({4, 5, 3, 7, 6}, {5, 7, 4, 9, 8}, 16);
  lp::printResultFillBackpack(ans);

  return 0;
}
