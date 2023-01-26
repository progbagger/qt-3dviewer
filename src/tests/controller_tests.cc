#include "controller_tests.h"

namespace {

void CompareMatrices(const model::TransformationMatrix4D& m1,
                     const model::TransformationMatrix4D& m2) {
  for (model::TransformationMatrix4D::SizeType i = 0; i < m1.GetSize();
       ++i) {
    for (model::TransformationMatrix4D::SizeType j = 0; j < m2.GetSize();
         ++j) {
      ASSERT_EQ(m1(i, j), m2(i, j));
    }
  }
}

TEST(Controller, SetFigureByPath) {
  model::Model m;
  controller::Controller c(&m);

  ASSERT_FALSE(c.SetFigureByPath("objects/cube_incorrect_facet.obj"));
  ASSERT_FALSE(c.SetFigureByPath("objects/cube_incorrect_vertex.obj"));
  ASSERT_FALSE(c.SetFigureByPath("objects/aboba.obj"));
  ASSERT_TRUE(c.SetFigureByPath("objects/cube.obj"));

  const model::Figure* figure = c.GetFigure();
  ASSERT_NE(figure->GetVertexes(), nullptr);
  ASSERT_NE(figure->GetFacets(), nullptr);

  c.CloseFigure();
}

TEST(Controller, GetFigure) {
  model::Model m;
  controller::Controller c(&m);

  ASSERT_TRUE(c.SetFigureByPath("objects/cube.obj"));
  const model::Figure* figure = c.GetFigure();
  ASSERT_EQ(figure->GetName(), "cube.obj");
}

TEST(Controller, Matrices) {
  model::Model m;
  controller::Controller c(&m);

  model::TransformationMatrix4D identity;
  CompareMatrices(c.GetTranslationMatrix(), identity);
  CompareMatrices(c.GetScalingMatrix(), identity);
  CompareMatrices(c.GetRotationMatrix(), identity);

  model::TranslationMatrix4D translation(5.5F, 7.2F, -92.89F);
  c.SetTranslation(5.5F, 7.2F, -92.89F);
  CompareMatrices(c.GetTranslationMatrix(), translation);

  model::ScalingMatrix4D scaling(6.2F);
  c.SetScale(6.2F);
  CompareMatrices(c.GetScalingMatrix(), scaling);

  model::RotationMatrix4D rotation(45.0F, 90.0F, 45.0F);
  c.SetRotation(45.0F, 90.0F, 45.0F);
  CompareMatrices(c.GetRotationMatrix(), rotation);

  c.ResetRotationMatrix();
  c.ResetTranslationMatrix();
  c.ResetScalingMatrix();

  CompareMatrices(c.GetTranslationMatrix(), identity);
  CompareMatrices(c.GetScalingMatrix(), identity);
  CompareMatrices(c.GetRotationMatrix(), identity);
}

TEST(Controller, AddRotation) {
  model::Model m;
  controller::Controller c(&m);

  model::RotationMatrix4D rotation(1.0F, 1.0F, 1.0F);
  model::TransformationMatrix4D compare;
  c.AddRotation(1.0F, 1.0F, 1.0F);
  compare = rotation * compare;
  CompareMatrices(c.GetRotationMatrix(), compare);

  c.AddRotation(2.0F, 2.0F, 2.0F);
  compare = rotation * compare;
  CompareMatrices(c.GetRotationMatrix(), compare);
}

}  // namespace
