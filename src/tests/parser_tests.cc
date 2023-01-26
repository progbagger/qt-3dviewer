#include "parser_tests.h"

namespace {

TEST(Parser, DefaultConstructor) {
  model::Parser parser;
  ASSERT_EQ(parser.GetFigure(), nullptr);
}

TEST(Parser, SetIncorrectFigure) {
  std::string path1 = "objects/cube_incorrect_facet.obj";
  model::Parser parser1;
  model::Figure* figure1 = parser1.GetFigureByPath(path1);
  ASSERT_EQ(figure1, nullptr);

  std::string path2 = "objects/cube_incorrect_vertex.obj";
  model::Parser parser2;
  model::Figure* figure2 = parser2.GetFigureByPath(path2);
  ASSERT_EQ(figure2, nullptr);

  std::string path3 = "aboba";
  model::Parser parser3;
  model::Figure* figure3 = parser3.GetFigureByPath(path3);
  ASSERT_EQ(figure3, nullptr);
}

TEST(Parser, CorrectFigure) {
  std::string path = "objects/cube.obj";
  model::Parser parser;
  model::Figure* figure = parser.GetFigureByPath(path);
  ASSERT_NE(figure, nullptr);
  ASSERT_EQ(figure->GetPath(), path);
  ASSERT_EQ(figure->GetName(), "cube.obj");
  ASSERT_EQ(figure->GetVertexCount(), 8);
  ASSERT_EQ(figure->GetFacetsCount(), 6);
  ASSERT_EQ(figure->GetFacetsIndexCount(), 48);
  ASSERT_EQ(figure->GetEdgesCount(), 24);
  ASSERT_EQ(figure->GetRectangle().GetLeftTop(),
            model::Point3D(-1.0F, 1.0F, 1.0F));
  ASSERT_EQ(figure->GetRectangle().GetRightBottom(),
            model::Point3D(1.0F, -1.0F, -1.0F));
}

TEST(Parser, FigureVolume) {
  model::Parser parser;
  model::Figure* figure = parser.GetFigureByPath("objects/cube.obj");
  ASSERT_NEAR(figure->GetRectangle().Volume(), 8.0F, 1e-6);
}

}  // namespace
