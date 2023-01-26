#include "transformation_matrix4d_tests.h"

namespace {

void CompareTransformationMatrices(
    const model::TransformationMatrix4D& matrix1,
    const model::TransformationMatrix4D& matrix2) {
  ASSERT_EQ(matrix1.GetSize(), matrix2.GetSize());
  for (SizeType i = 0; i < matrix1.GetSize() * matrix1.GetSize(); ++i) {
    ASSERT_EQ(matrix1.GetRawData()[i], matrix2.GetRawData()[i]);
  }
}

TEST(TransformationMatrix4D, DefaultConstructor) {
  const model::TransformationMatrix4D matrix;
  ASSERT_EQ(matrix.GetSize(), 4);
  for (SizeType i = 0; i < matrix.GetSize(); ++i) {
    for (SizeType j = 0; j < matrix.GetSize(); ++j) {
      if (i == j)
        ASSERT_EQ(matrix(i, j), 1.0F);
      else
        ASSERT_EQ(matrix(i, j), 0.0F);
    }
  }
}

TEST(TransformationMatrix4D, MultiplyOperator) {
  model::TransformationMatrix4D matrix1;
  model::TransformationMatrix4D matrix2;
  matrix2(3, 2) = 18.9F;
  matrix2(1, 2) = 5.6F;
  CompareTransformationMatrices(matrix1 * matrix2, matrix2);
  CompareTransformationMatrices(matrix2 * matrix1, matrix2);
}

TEST(TransformationMatrix4D, MultiplyEqualOperator) {
  model::TransformationMatrix4D matrix1;
  model::TransformationMatrix4D matrix2;
  matrix2(3, 2) = 18.9F;
  matrix2(1, 2) = 5.6F;
  CompareTransformationMatrices(matrix1 *= matrix2, matrix2);
  auto compare = matrix1 * matrix2;
  CompareTransformationMatrices(compare, matrix2 *= matrix1);
}

TEST(TranslationMatrix4D, Constructor) {
  model::TranslationMatrix4D matrix(1.1F, 5.7F, -18.89F);
  model::TransformationMatrix4D compare;
  compare(0, 3) = 1.1F;
  compare(1, 3) = 5.7F;
  compare(2, 3) = -18.89F;
  CompareTransformationMatrices(matrix, compare);
}

TEST(ScalingMatrix4D, Constructor) {
  model::ScalingMatrix4D matrix(77.0F);
  model::TransformationMatrix4D compare;
  compare(0, 0) = 77.0F;
  compare(1, 1) = 77.0F;
  compare(2, 2) = 77.0F;
  CompareTransformationMatrices(matrix, compare);
}

TEST(RotationMatrix4D, Constructor) {
  float alpha = 45.0F, beta = 37.8F, gamma = 115.0F;
  float r_alpha = alpha / 180.0F * M_PI;
  float r_beta = beta / 180.0F * M_PI;
  float r_gamma = gamma / 180.0F * M_PI;

  model::TransformationMatrix4D rotation_y;
  rotation_y(0, 0) = cos(r_beta);
  rotation_y(0, 2) = sin(r_beta);
  rotation_y(2, 0) = -sin(r_beta);
  rotation_y(2, 2) = cos(r_beta);

  model::TransformationMatrix4D rotation_x;
  rotation_x(1, 1) = cos(r_alpha);
  rotation_x(1, 2) = -sin(r_alpha);
  rotation_x(2, 1) = sin(r_alpha);
  rotation_x(2, 2) = cos(r_alpha);

  model::TransformationMatrix4D rotation_z;
  rotation_z(0, 0) = cos(r_gamma);
  rotation_z(0, 1) = -sin(r_gamma);
  rotation_z(1, 0) = sin(r_gamma);
  rotation_z(1, 1) = cos(r_gamma);

  model::TransformationMatrix4D compare =
      rotation_y * rotation_x * rotation_z;

  model::RotationMatrix4D rotation(alpha, beta, gamma);
  CompareTransformationMatrices(rotation, compare);
}

}  // namespace
