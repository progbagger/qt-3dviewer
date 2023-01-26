#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <array>

#include "parser.h"
#include "transformation_matrix4d.h"

namespace model {

// Facade class to rule the whole model
class Model {
 public:
  using ValueType = Figure::ValueType;

  Model();

  bool SetFigureByPath(const std::string& path);
  const Figure* GetFigure() const;

  void ResetTranslationMatrix();
  void ResetScalingMatrix();
  void ResetRotationMatrix();

  void SetTranslation(ValueType x, ValueType y, ValueType z);
  void SetScale(ValueType scale);
  void SetRotation(ValueType alpha, ValueType beta, ValueType gamma);
  void AddRotation(ValueType alpha, ValueType beta, ValueType gamma);

  const TransformationMatrix4D& GetTranslationMatrix() const;
  const TransformationMatrix4D& GetScalingMatrix() const;
  const TransformationMatrix4D& GetRotationMatrix() const;

  void CloseFigure();

 private:
  void SetPreviousRotationAngles(ValueType alpha, ValueType beta,
                                 ValueType gamma);
  void ResetPreviousRotationAngles();

  ValueType GetPreviousAlpha();
  ValueType GetPreviousBeta();
  ValueType GetPreviousGamma();

  Parser parser_;
  TransformationMatrix4D translation_matrix_;
  TransformationMatrix4D scaling_matrix_;
  TransformationMatrix4D rotation_matrix_;
  std::array<ValueType, 3> previous_rotation_angles_;
};

}  // namespace model

#endif  // MODEL_MODEL_H_
