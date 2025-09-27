// Copyright 2024 Marina Usova

#define POINT_CIRCLE
#ifdef POINT_CIRCLE

#include <iostream>
#include "../lib_point/point.h"
#include "../lib_circle/circle.h"
#include "../lib_algorithms/algorithms.h"

void output_result(int answer) {
    switch (answer) {
    case 0: std::cout << "intersect" << std::endl; break;
    case 1: std::cout << "touch" << std::endl; break;
    case 2: std::cout << "inside" << std::endl; break;
    case 3: std::cout << "not_intersect" << std::endl; break;
    }
}

int main() {
    Circle c1(1, 2, 3);
    Circle c2(2, 3, 1);

    int answer1 = figures_comparison(c1, c2);
    output_result(answer1);

    return 0;
}

#endif

//#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE
