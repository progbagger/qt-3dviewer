#include "square_matrix_tests.h"

void CompareSquareMatrix(const model::SquareMatrix& matrix,
                         const std::vector<ValueType>& compare) {
  ASSERT_EQ(matrix.GetSize() * matrix.GetSize(), compare.size());
  for (SizeType i = 0; i < compare.size(); ++i) {
    ASSERT_EQ(matrix.GetRawData()[i], compare.at(i));
  }
}

TEST(SquareMatrix, ParametrizedConstructor) {
  model::SquareMatrix matrix1(1);
  CompareSquareMatrix(matrix1, {0.0F});

  model::SquareMatrix matrix2(66);
  CompareSquareMatrix(matrix2, std::vector(66 * 66, 0.0F));
}

TEST(SquareMatrix, BracketsOperator) {
  model::SquareMatrix matrix(5);
  ASSERT_THROW(matrix(5, 0), std::exception);
  ASSERT_THROW(matrix(0, 5), std::exception);

  ASSERT_EQ(matrix(1, 2), 0.0);

  matrix(0, 0) = 15.7F;
  ASSERT_EQ(matrix(0, 0), 15.7F);

  const model::SquareMatrix cmatrix(4);
  ASSERT_EQ(cmatrix(3, 3), 0.0F);
}

#include <iostream>

TEST(SquareMatrix, MultiplyOperator) {
  model::SquareMatrix matrix1(2);
  matrix1(0, 0) = 2.0F;
  matrix1(0, 1) = 3.0F;
  matrix1(1, 0) = 1.0F;
  matrix1(1, 1) = 5.0F;

  model::SquareMatrix matrix2(2);
  CompareSquareMatrix(matrix1 * matrix2, std::vector(2 * 2, 0.0F));

  matrix2(0, 0) = 15.0F;
  matrix2(1, 1) = 3.0F;

  CompareSquareMatrix(matrix1 * matrix2, {30.0F, 9.0F, 15.0F, 15.0F});
}

TEST(SquareMatrix, EqualMultiplyOperator) {
  model::SquareMatrix matrix(2);
  matrix(0, 0) = 1.0F;
  matrix(0, 1) = 4.0F;
  matrix(1, 0) = 17.0F;
  matrix(1, 1) = 35.0F;

  model::SquareMatrix matrix_incorrect(3);
  ASSERT_THROW(matrix *= matrix_incorrect, std::exception);

  model::SquareMatrix matrix2(2);
  matrix2(1, 1) = 1.0F / 35.0F;
  ASSERT_NO_THROW(matrix *= matrix2);
  CompareSquareMatrix(matrix,
                      {0, 4.0F * (1.0F / 35.0F), 0.0F, 35.0F * (1.0F / 35.0F)});
}
