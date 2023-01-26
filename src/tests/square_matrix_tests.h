#ifndef TESTS_SQUARE_MATRIX_TESTS_H_
#define TESTS_SQUARE_MATRIX_TESTS_H_

#include <gtest/gtest.h>

#include <vector>

#include "square_matrix.h"

using ValueType = model::SquareMatrix::ValueType;
using SizeType = model::SquareMatrix::SizeType;

void CompareSquareMatrix(const model::SquareMatrix& matrix,
                         const std::vector<ValueType>& compare);

#endif  // TESTS_SQUARE_MATRIX_TESTS_H_
