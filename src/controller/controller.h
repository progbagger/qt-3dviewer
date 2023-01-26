#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "model.h"

namespace controller {

class Controller {
 public:
  Controller() = delete;
  explicit Controller(model::Model* model);

  bool SetFigureByPath(const std::string& path);

  void ResetTranslationMatrix();
  void ResetScalingMatrix();
  void ResetRotationMatrix();

  void SetTranslation(model::Model::ValueType x, model::Model::ValueType y,
                      model::Model::ValueType z);
  void SetScale(model::Model::ValueType scale);
  void SetRotation(model::Model::ValueType alpha, model::Model::ValueType beta,
                   model::Model::ValueType gamma);
  void AddRotation(model::Model::ValueType alpha, model::Model::ValueType beta,
                   model::Model::ValueType gamma);

  const model::TransformationMatrix4D& GetTranslationMatrix() const;
  const model::TransformationMatrix4D& GetScalingMatrix() const;
  const model::TransformationMatrix4D& GetRotationMatrix() const;

  const model::Figure* GetFigure() const;
  void CloseFigure();

 private:
  model::Model* model_;
};

}  // namespace controller

#endif  // CONTROLLER_CONTROLLER_H_
