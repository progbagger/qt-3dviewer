#include "controller.h"

namespace controller {

Controller::Controller(model::Model* model) : model_(model) {}

bool Controller::SetFigureByPath(const std::string& path) {
  return model_->SetFigureByPath(path);
}

void Controller::ResetTranslationMatrix() { model_->ResetTranslationMatrix(); }

void Controller::ResetScalingMatrix() { model_->ResetScalingMatrix(); }

void Controller::ResetRotationMatrix() { model_->ResetRotationMatrix(); }

void Controller::SetTranslation(model::Model::ValueType x,
                                model::Model::ValueType y,
                                model::Model::ValueType z) {
  model_->SetTranslation(x, y, z);
}

void Controller::SetScale(model::Model::ValueType scale) {
  model_->SetScale(scale);
}

void Controller::SetRotation(model::Model::ValueType alpha,
                             model::Model::ValueType beta,
                             model::Model::ValueType gamma) {
  model_->SetRotation(alpha, beta, gamma);
}

void Controller::AddRotation(model::Model::ValueType alpha,
                             model::Model::ValueType beta,
                             model::Model::ValueType gamma) {
  model_->AddRotation(alpha, beta, gamma);
}

const model::TransformationMatrix4D& Controller::GetTranslationMatrix() const {
  return model_->GetTranslationMatrix();
}

const model::TransformationMatrix4D& Controller::GetScalingMatrix() const {
  return model_->GetScalingMatrix();
}

const model::TransformationMatrix4D& Controller::GetRotationMatrix() const {
  return model_->GetRotationMatrix();
}

void Controller::CloseFigure() { model_->CloseFigure(); }

const model::Figure* Controller::GetFigure() const {
  return model_->GetFigure();
}

}  // namespace controller
