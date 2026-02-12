#include "algorithms.h"
#define DEBUG

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

Matrix<bool> generate(int x, int y, int n, int m) {
    //if (x == y) throw...
    DSU labyrinth(n * m);
    Matrix<bool> walls(2 * n - 1, m);
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < m; j++) {
            walls[i][j] = 1;
        }
    }
    int rand_int;
    srand(static_cast<unsigned int>(time(0)));
    int current = x, finish = y;
    while (current != finish) {
        if (current < finish) {
            rand_int = rand() % 2;
            if (rand_int && current % m != m-1) {  // вправо
                labyrinth.unite(current, current +1);
                walls[current / m][current % m] = 0;
                current += 1;
            }
            else if (current / m < n - 1) {  // вниз
                labyrinth.unite(current, current + m);
                walls[current / m + n][current % m] = 0;
                current += m;
            }
            rand_int = rand() % 3;
            if (rand_int == 0 && current % m != 0 
                && labyrinth.find(current) != labyrinth.find(current - 1)) {  // влево
                labyrinth.unite(current, current - 1);
                walls[(current - 1) / m][(current - 1) % m] = 0;
            }
            if (rand_int == 1 && current > m 
                && labyrinth.find(current) != labyrinth.find(current - m)) {  // вверх
                labyrinth.unite(current, current - m);
                walls[(current - m) / m + n][current % m] = 0;
            }
        }
        if (current > y) {
            //???
            int c = current;
            current = finish;
            finish = c;
        }
    }
    int count_extra_walls = n * m / 3;
    for (int i = 0; i < count_extra_walls * 2; i++) {
        int cell = rand() % (n * m);
        int wall_num = rand() % 4;

        if (wall_num == 0 && cell % m != m - 1 
            && labyrinth.find(cell) != labyrinth.find(cell + 1)) { // вправо
            labyrinth.unite(cell, cell + 1);
            walls[cell / m][cell % m] = 0;
        }
        else if (wall_num == 1 && cell / m < n - 1 
            && labyrinth.find(cell) != labyrinth.find(cell + m)) { // вниз
            labyrinth.unite(cell, cell + m);
            walls[cell / m + n][cell % m] = 0;
        }
        else if (wall_num == 2 && cell % m != 0 
            && labyrinth.find(cell) != labyrinth.find(cell - 1)) { // влево
            labyrinth.unite(cell, cell - 1);
            walls[(cell - 1) / m][(cell - 1) % m] = 0;
        }
        else if (wall_num == 3 && cell >= m 
            && labyrinth.find(cell) != labyrinth.find(cell - m)) { // вверх
            labyrinth.unite(cell, cell - m);
            walls[(cell - m) / m + n][cell % m] = 0;
        }
    }

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

void print_lab(Matrix<bool> walls, int n, int m) {
    for (int j = 0; j < m; j++) {
        std::cout << "+---";
    }
    std::cout << "+\n";
    for (int i = 0; i < n; i++) {
        std::cout << "|";
        for (int j = 0; j < m; j++) {
            std::cout << "   ";
            if (walls[i][j]) std::cout << "|";
            else std::cout << " ";
        }
        std::cout << "\n";
        if (i < n - 1) {
            std::cout << "+";
            for (int j = 0; j < m; j++) {
                if (walls[i + n][j]) std::cout << "---+";
                else std::cout << "   +";
            }
            std::cout << "\n";
        }
    }
    for (int j = 0; j < m; j++) {
        std::cout << "+---";
    }
    std::cout << "+\n";
}