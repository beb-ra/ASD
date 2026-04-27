#include "algorithms.h"
//#define DEBUG
#define MAX_ITERATIONS 1000

int island_counting(Matrix<int>& matrix) {
    int N = matrix.get_n();
    int M = matrix.get_m();

    DSU dsu(N * M);
    int count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] == 1) {
                count++;
                int current = i * M + j;

                if (i > 0 && matrix[i - 1][j] == 1) {
                    int top = (i - 1) * M + j;
                    if (dsu.find(current) != dsu.find(top)) {
                        dsu.unite(current, top);
                        count--;
                    }
                }

                if (j > 0 && matrix[i][j - 1] == 1) {
                    int left = i * M + (j - 1);
                    if (dsu.find(current) != dsu.find(left)) {
                        dsu.unite(current, left);
                        count--;
                    }
                }
            }
        }
    }

    return count;
}

void create_path(int& walls_removed, int x, int y, int n, int m, DSU& labyrinth, Matrix<bool>& walls) {
    int current = x, finish = y;
    float rand_val;
    for (int i = 0; current != finish; i++) {
        if (current < finish) {
            rand_val = (float)rand() / RAND_MAX;
            float prob_right = 0.35;
            float prob_down = 0.35;
            float prob_left = 0.15;
            float prob_up = 0.15;

            if (rand_val < prob_right && current % m != m - 1) {  // вправо
                if (labyrinth.find(current) != labyrinth.find(current + 1)) {
                    labyrinth.unite(current, current + 1);
                    walls[current / m][current % m] = 0;
                    walls_removed++;
                }
                current += 1;
            }
            else if (rand_val < prob_right + prob_down && current / m < n - 1) {  // вниз
                if (labyrinth.find(current) != labyrinth.find(current + m)) {
                    labyrinth.unite(current, current + m);
                    walls[current / m + n][current % m] = 0;
                    walls_removed++;
                }
                current += m;
            }
            else if (rand_val < prob_right + prob_down + prob_left && current % m != 0) {  // влево
                if (labyrinth.find(current) != labyrinth.find(current - 1)) {
                    labyrinth.unite(current, current - 1);
                    walls[(current - 1) / m][(current - 1) % m] = 0;
                    walls_removed++;
                }
            }
            else if (rand_val > 1 - prob_up && current > m) {  // вверх
                if (labyrinth.find(current) != labyrinth.find(current - m)) {
                    labyrinth.unite(current, current - m);
                    walls[(current - m) / m + n][current % m] = 0;
                    walls_removed++;
                }
            }
        }
        if (current > y) {
            int c = current;
            current = finish;
            finish = c;
        }
        if (i > MAX_ITERATIONS) {
            current = x, finish = y;
            i = 0;
        }
    }
}

void remove_extra_walls(int count_extra_walls, int& walls_removed, int n, int m, DSU& labyrinth, Matrix<bool>& walls) {
    for (int i = 0; walls_removed < count_extra_walls; i++) {
        int cell = rand() % (n * m);
        int wall_num = rand() % 4;

        if (wall_num == 0 && cell % m != m - 1
            && labyrinth.find(cell) != labyrinth.find(cell + 1)) { // вправо
            labyrinth.unite(cell, cell + 1);
            walls[cell / m][cell % m] = 0;
            walls_removed++;
        }
        else if (wall_num == 1 && cell / m < n - 1
            && labyrinth.find(cell) != labyrinth.find(cell + m)) { // вниз
            labyrinth.unite(cell, cell + m);
            walls[cell / m + n][cell % m] = 0;
            walls_removed++;
        }
        else if (wall_num == 2 && cell % m != 0
            && labyrinth.find(cell) != labyrinth.find(cell - 1)) { // влево
            labyrinth.unite(cell, cell - 1);
            walls[(cell - 1) / m][(cell - 1) % m] = 0;
            walls_removed++;
        }
        else if (wall_num == 3 && cell >= m
            && labyrinth.find(cell) != labyrinth.find(cell - m)) { // вверх
            labyrinth.unite(cell, cell - m);
            walls[(cell - m) / m + n][cell % m] = 0;
            walls_removed++;
        }
        if (i > MAX_ITERATIONS) break;
    }
}

Matrix<bool> generate(int x, int y, int n, int m) {
    if (n <= 2) throw std::invalid_argument("Ўирина лабиринта должна быть больше");
    if (m <= 2) throw std::invalid_argument("ƒлина лабиринта должна быть больше");
    if (x == y) throw std::invalid_argument("¬ход и выход должны быть в разных клетках");
    if (!((x / m == 0 || x / m == n - 1 || x % m == 0 || x % m == m - 1) &&
        (y / m == 0 || y / m == n - 1 || y % m == 0 || y % m == m - 1))) {
        throw std::invalid_argument("¬ход и выход должны быть на границе лабиринта");
    }
    if (x < 0 || y < 0 || x >= n * m || y >= n * m) {
        throw std::invalid_argument("¬ход и выход не должны быть за пределами лабиринта");
    }
    DSU labyrinth(n * m);
    Matrix<bool> walls(2 * n - 1, m);
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < m; j++) {
            walls[i][j] = 1;
        }
    }
    srand(static_cast<unsigned int>(time(0)));
    int walls_removed = 0;

    create_path(walls_removed, x, y, n, m, labyrinth, walls);

    int count_extra_walls = n * m;
    remove_extra_walls(count_extra_walls, walls_removed, n, m, labyrinth, walls);

#ifdef DEBUG
    for (int i = 0; i < n * m; i++) {
        std::cout << i << ": " << labyrinth.find(i) << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << walls[i][j] << " ";
        }
        std::cout << "\n";
        for (int j = 0; j < m; j++) {
            std::cout << walls[i+n][j] << " ";
        }
        std::cout << "\n";
    }
    for (int j = 0; j < m; j++) {
        std::cout << walls[n-1][j] << " ";
    }
    std::cout << "\n";
#endif

    return walls;
}

void print_lab(Matrix<bool> walls, int n, int m, int ent, int exit) {
    bool is_ent = false;
    bool is_exit = false;
    std::cout << "+";
    for (int j = 0; j < m; j++) {
        if (ent == j && ent / m == 0) {
            std::cout << "   +";
            is_ent = true;
        }
        else if (exit == j && exit / m == 0) {
            std::cout << "   +";
            is_exit = true;
        }
        else {
            std::cout << "---+";
        }
    }
    std::cout << "\n";

    if (exit / m == n - 1) {
        is_exit = true;
    }
    if (ent / m == n - 1) {
        is_ent = true;
    }

    for (int i = 0; i < n; i++) {
        // лево
        if (ent == i * m && ent % m == 0 && ent / m != 0 && !is_ent ||
            exit == i * m && exit % m == 0 && exit / m != 0 && !is_exit) {
            std::cout << " ";
        }
        else {
            std::cout << "|";
        }

        for (int j = 0; j < m; j++) {
            if (i * m + j < 10) std::cout << " " << i * m + j << " ";
            else std::cout << i * m + j << " ";

            if (j < m - 1) {
                if (walls[i][j]) std::cout << "|";
                else std::cout << " ";
            }
            else {
                // право
                if (exit == i * m + j && exit % m == m - 1 && exit / m != n - 1 && !is_exit 
                    || ent == i * m + j && ent % m == m - 1 && ent / m != n - 1 && !is_ent) {
                    std::cout << " ";
                }
                else {
                    std::cout << "|";
                }
            }
        }
        std::cout << "\n";

        // снизу
        if (i < n - 1) {
            std::cout << "+";
            for (int j = 0; j < m; j++) {
                if (exit == i * m + j + m && exit / m == i + 1 && !is_exit ||
                    ent == i * m + j + m && ent / m == i + 1 && !is_ent) {
                    std::cout << "   +";
                }
                else {
                    if (walls[n + i][j]) 
                        std::cout << "---+";
                    else 
                        std::cout << "   +";
                }
            }
            std::cout << "\n";
        }
    }

    std::cout << "+";
    for (int j = 0; j < m; j++) {
        if (exit == (n - 1) * m + j && exit / m == n - 1 ||
            ent == (n - 1) * m + j && ent / m == n - 1) {
            std::cout << "   +";
        }
        else {
            std::cout << "---+";
        }
    }
    std::cout << "\n";
}

List<int> find_shortest_path_in_lab(Matrix<bool>& matrix_walls, int n, int m, int start, int end) {
    std::vector<std::pair<int, int>> edges;

    //std::cout << matrix_walls;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix_walls[i][j] == false) {
                int cell1 = i * m + j;
                int cell2 = i * m + j + 1;
                edges.push_back({ cell1, cell2 });
            }

        }
    }
    for (int i = n; i < 2 * n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix_walls[i][j] == false) {
                int cell1 = (i - n) * m + j;
                int cell2 = (i - n + 1) * m + j;
                edges.push_back({ cell1, cell2 });
            }
        }
    }


    LGraph<int> graph(edges, true);
    //std::cout << graph;

    return graph.find_min_way(start, end);
}