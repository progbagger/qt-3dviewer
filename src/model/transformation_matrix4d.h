#ifndef MODEL_TRANSFORMATION_MATRIX4D_H_
#define MODEL_TRANSFORMATION_MATRIX4D_H_

#include <cmath>

#include "square_matrix.h"

namespace model {

// Prototype and adapter patterns used
// * Adapter for QMatrix4x4
class TransformationMatrix4D {
 public:
  using SizeType = SquareMatrix::SizeType;
  using ValueType = SquareMatrix::ValueType;

  // Creates identical 4x4 matrix
  TransformationMatrix4D();

  SizeType GetSize() const;
  const ValueType* GetRawData() const;

  ValueType& operator()(SizeType row, SizeType column);
  const ValueType& operator()(SizeType row, SizeType column) const;

  TransformationMatrix4D operator*(const TransformationMatrix4D& other) const;
  TransformationMatrix4D& operator*=(const TransformationMatrix4D& other);

 protected:
  SquareMatrix matrix_;
};

class TranslationMatrix4D : public TransformationMatrix4D {
 public:
  using Base = TransformationMatrix4D;

  TranslationMatrix4D() = delete;
  TranslationMatrix4D(ValueType x, ValueType y, ValueType z);
};

class ScalingMatrix4D : public TransformationMatrix4D {
 public:
  using Base = TransformationMatrix4D;

  ScalingMatrix4D() = delete;
  ScalingMatrix4D(ValueType scale);
};

class RotationMatrix4D : public TransformationMatrix4D {
 public:
  using Base = TransformationMatrix4D;

  RotationMatrix4D() = delete;
  RotationMatrix4D(ValueType alpha, ValueType beta, ValueType gamma);

 private:
  TransformationMatrix4D CreateXRotationMatrix(ValueType degrees);
  TransformationMatrix4D CreateYRotationMatrix(ValueType degrees);
  TransformationMatrix4D CreateZRotationMatrix(ValueType degrees);

  ValueType DegreesToRadians(ValueType value);
};

}  // namespace model

#endif  // MODEL_TRANSFORMATION_MATRIX4D_H_
