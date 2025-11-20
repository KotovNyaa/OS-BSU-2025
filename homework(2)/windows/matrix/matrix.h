#pragma once
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix parallelMultiply(const Matrix& A, const Matrix& B, int blockSize);
