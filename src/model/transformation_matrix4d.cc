#include "transformation_matrix4d.h"

namespace model {

// TransformationMatrix4D

TransformationMatrix4D::TransformationMatrix4D() : matrix_(4) {
  for (SizeType i = 0; i < GetSize(); ++i) matrix_(i, i) = 1.0;
}

TransformationMatrix4D::SizeType TransformationMatrix4D::GetSize() const {
  return matrix_.GetSize();
}

const TransformationMatrix4D::ValueType* TransformationMatrix4D::GetRawData()
    const {
  return matrix_.GetRawData();
}

TransformationMatrix4D::ValueType& TransformationMatrix4D::operator()(
    SizeType row, SizeType column) {
  return matrix_(row, column);
}

const TransformationMatrix4D::ValueType& TransformationMatrix4D::operator()(
    SizeType row, SizeType column) const {
  return matrix_(row, column);
}

TransformationMatrix4D TransformationMatrix4D::operator*(
    const TransformationMatrix4D& other) const {
  TransformationMatrix4D result;
  result.matrix_ = std::move(matrix_ * other.matrix_);
  return result;
}

TransformationMatrix4D& TransformationMatrix4D::operator*=(
    const TransformationMatrix4D& other) {
  *this = std::move(*this * other);
  return *this;
}

// TranslationMatrix4D

TranslationMatrix4D::TranslationMatrix4D(ValueType x, ValueType y, ValueType z)
    : Base() {
  (*this)(0, GetSize() - 1) = x;
  (*this)(1, GetSize() - 1) = y;
  (*this)(2, GetSize() - 1) = z;
}

// ScalingMatrix4D

ScalingMatrix4D::ScalingMatrix4D(ValueType scale) : Base() {
  for (SizeType i = 0; i < GetSize() - 1; ++i) (*this)(i, i) = scale;
}

// RotationMatrix4D

RotationMatrix4D::RotationMatrix4D(ValueType alpha, ValueType beta,
                                   ValueType gamma)
    : Base(CreateYRotationMatrix(beta) * CreateXRotationMatrix(alpha) *
           CreateZRotationMatrix(gamma)) {}

TransformationMatrix4D RotationMatrix4D::CreateXRotationMatrix(
    ValueType degrees) {
  TransformationMatrix4D result;
  ValueType radians = DegreesToRadians(degrees);
  result(1, 1) = cos(radians);
  result(1, 2) = -sin(radians);
  result(2, 1) = sin(radians);
  result(2, 2) = cos(radians);
  return result;
}

TransformationMatrix4D RotationMatrix4D::CreateYRotationMatrix(
    ValueType degrees) {
  TransformationMatrix4D result;
  ValueType raidans = DegreesToRadians(degrees);
  result(0, 0) = cos(raidans);
  result(0, 2) = sin(raidans);
  result(2, 0) = -sin(raidans);
  result(2, 2) = cos(raidans);
  return result;
}

TransformationMatrix4D RotationMatrix4D::CreateZRotationMatrix(
    ValueType degrees) {
  TransformationMatrix4D result;
  ValueType radians = DegreesToRadians(degrees);
  result(0, 0) = cos(radians);
  result(0, 1) = -sin(radians);
  result(1, 0) = sin(radians);
  result(1, 1) = cos(radians);
  return result;
}

RotationMatrix4D::ValueType RotationMatrix4D::DegreesToRadians(
    ValueType value) {
  return value / 180.0 * M_PI;
}

}  // namespace model
