#include "matrix.h"
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

const int N = 100;

Matrix createMatrix(int size) {
    Matrix m(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            m[i][j] = (i * j + i + j) % 100;
        }
    }
    return m;
}

Matrix standardMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main() {
    std::cout << "|| Test (N=" << N << ") \n";

    Matrix A = createMatrix(N);
    Matrix B = createMatrix(N);

    std::cout << "|| Running standard algorithm... ";
    auto startStd = std::chrono::high_resolution_clock::now();
    Matrix refC = standardMultiply(A, B);
    auto endStd = std::chrono::high_resolution_clock::now();
    double timeStd = std::chrono::duration<double>(endStd - startStd).count();
    std::cout << "Done: " << timeStd << " sec\n||\n";

    std::cout << "|| " << std::setw(8) << "Block" << std::setw(12) << "Threads"
        << std::setw(12) << "Time" << std::setw(18) << "Status" << "\n";
    std::cout << "|| --------------------------------------------------\n";

    int step = 1;
    if (step == 0)
        step = 1;

    for (int k = 1; k <= N; k += step) {
        if (k > N)
            k = N;

        int blocksPerDim = (N + k - 1) / k;
        int totalThreads = blocksPerDim * blocksPerDim;

        auto start = std::chrono::high_resolution_clock::now();
        Matrix result = parallelMultiply(A, B, k);
        auto end = std::chrono::high_resolution_clock::now();
        double timePar = std::chrono::duration<double>(end - start).count();

        bool isCorrect = (result == refC);

        std::cout << "||" << std::setw(8) << k << std::setw(12) << totalThreads
            << std::setw(15) << std::fixed << std::setprecision(6) << timePar
            << std::setw(14) << (isCorrect ? "OK" : "FAIL") << "\n";

        if (k == N)
            break;
    }

    return 0;
}
