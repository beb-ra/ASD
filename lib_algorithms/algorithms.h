#pragma once

#include <cstdlib>
#include <ctime>
#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"

int island_counting(Matrix<int>& matrix);

void generate(int x, int y, int n, int m);
