#pragma once

#include <cstdlib>
#include <ctime>
#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"
//#include "../lib_list/list.h"
#include "../lib_graph_on_list_adj/graph_on_list_adj.h"

int island_counting(Matrix<int>& matrix);

Matrix<bool> generate(int x, int y, int n, int m);

void print_lab(Matrix<bool> walls, int n, int m, int ent, int exit);

void remove_extra_walls(int count_extra_walls, int& walls_removed, int n, int m, DSU& labyrinth, Matrix<bool>& walls);

void create_path(int& walls_removed, int x, int y, int n, int m, DSU& labyrinth, Matrix<bool>& walls);

List<int> find_shortest_path_in_lab(Matrix<bool>& matrix_walls, int n, int m, int start, int end);

void print_lab_with_shortest_path(Matrix<bool> walls, int n, int m, int ent, int exit);