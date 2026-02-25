#pragma once

#include <cstdlib>
#include <ctime>
#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"

int island_counting(Matrix<int>& matrix);

Matrix<bool> generate(int x, int y, int n, int m);

void print_lab(Matrix<bool> walls, int n, int m, int ent, int exit);

void remove_extra_walls(int count_extra_walls, int& walls_removed, int n, int m, DSU& labyrinth, Matrix<bool>& walls);

void create_path(int& walls_removed, int x, int y, int n, int m, DSU& labyrinth, Matrix<bool>& walls);
