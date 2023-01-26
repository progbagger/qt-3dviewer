#ifndef TESTS_TRANSFORMATION_MATRIX4D_TESTS_H_
#define TESTS_TRANSFORMATION_MATRIX4D_TESTS_H_

#include <gtest/gtest.h>

#include "transformation_matrix4d.h"

namespace {

using SizeType = model::TransformationMatrix4D::SizeType;

void CompareTransformationMatrices(
    const model::TransformationMatrix4D& matrix1,
    const model::TransformationMatrix4D& matrix2);

}  // namespace

#endif  // TESTS_TRANSFORMATION_MATRIX4D_TESTS_H_
