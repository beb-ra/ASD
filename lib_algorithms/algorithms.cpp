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