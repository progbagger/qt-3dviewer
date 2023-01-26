#include "model.h"

namespace model {

Model::Model()
    : parser_(),
      translation_matrix_(),
      scaling_matrix_(),
      rotation_matrix_(),
      previous_rotation_angles_{0.0F, 0.0F, 0.0F} {}

bool Model::SetFigureByPath(const std::string& path) {
  const Figure* prev = parser_.GetFigure();
  parser_.GetFigureByPath(path);
  if (parser_.GetFigure() == prev) return false;
  return parser_.GetFigure();
}

const Figure* Model::GetFigure() const { return parser_.GetFigure(); }

void Model::ResetTranslationMatrix() {
  translation_matrix_ = TransformationMatrix4D();
}

void Model::ResetScalingMatrix() { scaling_matrix_ = TransformationMatrix4D(); }

void Model::ResetRotationMatrix() {
  rotation_matrix_ = TransformationMatrix4D();
}

void Model::SetTranslation(ValueType x, ValueType y, ValueType z) {
  translation_matrix_ = TranslationMatrix4D(x, y, z);
}

void Model::SetScale(ValueType scale) {
  scaling_matrix_ = ScalingMatrix4D(scale);
}

void Model::SetRotation(ValueType alpha, ValueType beta, ValueType gamma) {
  rotation_matrix_ = RotationMatrix4D(alpha, beta, gamma);
  SetPreviousRotationAngles(alpha, beta, gamma);
}

void Model::AddRotation(ValueType alpha, ValueType beta, ValueType gamma) {
  rotation_matrix_ =
      RotationMatrix4D(alpha - GetPreviousAlpha(), beta - GetPreviousBeta(),
                       gamma - GetPreviousGamma()) *
      rotation_matrix_;
  SetPreviousRotationAngles(alpha, beta, gamma);
}

const TransformationMatrix4D& Model::GetTranslationMatrix() const {
  return translation_matrix_;
}

const TransformationMatrix4D& Model::GetScalingMatrix() const {
  return scaling_matrix_;
}

const TransformationMatrix4D& Model::GetRotationMatrix() const {
  return rotation_matrix_;
}

void Model::CloseFigure() {
  parser_.CloseFigure();
  ResetTranslationMatrix();
  ResetScalingMatrix();
  ResetRotationMatrix();
  ResetPreviousRotationAngles();
}

void Model::SetPreviousRotationAngles(ValueType alpha, ValueType beta,
                                      ValueType gamma) {
  previous_rotation_angles_.at(0) = alpha;
  previous_rotation_angles_.at(1) = beta;
  previous_rotation_angles_.at(2) = gamma;
}

void Model::ResetPreviousRotationAngles() {
  SetPreviousRotationAngles(0.0F, 0.0F, 0.0F);
}

Model::ValueType Model::GetPreviousAlpha() {
  return previous_rotation_angles_.at(0);
}

Model::ValueType Model::GetPreviousBeta() {
  return previous_rotation_angles_.at(1);
}

Model::ValueType Model::GetPreviousGamma() {
  return previous_rotation_angles_.at(2);
}

}  // namespace model
