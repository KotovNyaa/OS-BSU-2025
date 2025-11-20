#include "matrix.h"
#include <algorithm>
#include <vector>
#include <windows.h>

const int kBlockT = 64;

struct ThreadData {
    const Matrix* A;
    const Matrix* B_transposed;
    Matrix* C;
    int rowStart, rowEnd;
    int colStart, colEnd;
    int N;
};

void transposeMatrix(const Matrix& src, Matrix& dst) {
    int N = static_cast<int>(src.size());
    for (int i = 0; i < N; i += kBlockT) {
        for (int j = 0; j < N; j += kBlockT) {
            int iLimit = (((i + kBlockT) < (N)) ? (i + kBlockT) : (N));
            int jLimit = (((j + kBlockT) < (N)) ? (j + kBlockT) : (N));
            for (int ii = i; ii < iLimit; ++ii) {
                for (int jj = j; jj < jLimit; ++jj) {
                    dst[jj][ii] = src[ii][jj];
                }
            }
        }
    }
}

DWORD WINAPI computeBlock(LPVOID arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    const Matrix& A = *data->A;
    const Matrix& BT = *data->B_transposed;
    Matrix& C = *data->C;
    int N = data->N;

    for (int i = data->rowStart; i < data->rowEnd; ++i) {
        for (int j = data->colStart; j < data->colEnd; ++j) {
            int sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * BT[j][k];
            }
            C[i][j] = sum;
        }
    }
    return 0;
}

Matrix parallelMultiply(const Matrix& A, const Matrix& B, int blockSize) {
    int N = A.size();
    Matrix C(N, std::vector<int>(N));
    Matrix B_T(N, std::vector<int>(N));

    transposeMatrix(B, B_T);

    std::vector<HANDLE> threads;
    std::vector<ThreadData> tasks;

    int blocksCount = (N + blockSize - 1) / blockSize;
    int totalTasks = blocksCount * blocksCount;

    tasks.reserve(totalTasks);
    threads.reserve(totalTasks);

    for (int i = 0; i < N; i += blockSize) {
        for (int j = 0; j < N; j += blockSize) {
            ThreadData task;
            task.A = &A;
            task.B_transposed = &B_T;
            task.C = &C;
            task.rowStart = i;
            task.rowEnd = (((i + blockSize) < (N)) ? (i + blockSize) : (N));
            task.colStart = j;
            task.colEnd = (((j + blockSize) < (N)) ? (j + blockSize) : (N));
            task.N = N;

            tasks.push_back(task);

            HANDLE hThread =
                CreateThread(NULL, 0, computeBlock, &tasks.back(), 0, NULL);
            if (hThread != NULL) {
                threads.push_back(hThread);
            }
        }
    }

    for (HANDLE h : threads) {
        WaitForSingleObject(h, INFINITE);
        CloseHandle(h);
    }

    return C;
}
