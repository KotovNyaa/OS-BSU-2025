#include "matrix.h"
#include <algorithm>
#include <thread>
#include <vector>

const int kBlockT = 64;

struct ThreadData {
  const Matrix *A;
  const Matrix *B_transposed;
  Matrix *C;
  int rowStart, rowEnd;
  int colStart, colEnd;
  int N;
};

void transposeMatrix(const Matrix &src, Matrix &dst) {
  int N = src.size();
  for (int i = 0; i < N; i += kBlockT) {
    for (int j = 0; j < N; j += kBlockT) {
      int iLimit = std::min(i + kBlockT, N);
      int jLimit = std::min(j + kBlockT, N);
      for (int ii = i; ii < iLimit; ++ii) {
        for (int jj = j; jj < jLimit; ++jj) {
          dst[jj][ii] = src[ii][jj];
        }
      }
    }
  }
}

void computeBlock(ThreadData *data) {
  const Matrix &A = *data->A;
  const Matrix &BT = *data->B_transposed;
  Matrix &C = *data->C;
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
}

Matrix parallelMultiply(const Matrix &A, const Matrix &B, int blockSize) {
  int N = A.size();
  Matrix C(N, std::vector<int>(N));
  Matrix B_T(N, std::vector<int>(N));

  transposeMatrix(B, B_T);

  std::vector<std::thread> threads;
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
      task.rowEnd = std::min(i + blockSize, N);
      task.colStart = j;
      task.colEnd = std::min(j + blockSize, N);
      task.N = N;

      tasks.push_back(task);
      threads.emplace_back(computeBlock, &tasks.back());
    }
  }

  for (auto &thread : threads) {
    thread.join();
  }

  return C;
}
