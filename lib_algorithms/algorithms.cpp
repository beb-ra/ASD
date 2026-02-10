#include "algorithms.h"

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

void generate(int x, int y, int n, int m) {
    //if (n == m) throw...
    DSU labyrinth(n * m);
    int rand_int;
    srand(static_cast<unsigned int>(time(0)));
    int u = x, w = y;
    while (u != w) {
        if (u < w) {
            rand_int = rand() % 2;
            if (rand_int && u % m != m-1) {
                //вправо
                labyrinth.unite(u, u+1);
                u = u + 1;
            }
            else if (u / m < n - 1) {
                //вниз
                labyrinth.unite(u, u + m);
                u = u + m;
            }
            rand_int = rand() % 4;
            if (rand_int == 0 && u % m != 0) {
                //влево
                labyrinth.unite(u, u - 1);
            }
            if (rand_int == 1 && u > m) {
                // вверх
                labyrinth.unite(u, u - m);
            }
        }
        if (u > y) {
            //???
            int c = u;
            u = w;
            w = c;
        }
    }
    for (int i = 0; i < n * m; i++) {
        std::cout << i << ": " << labyrinth.find(i) << " ";
    }
}
