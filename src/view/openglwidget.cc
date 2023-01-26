#include "openglwidget.h"

namespace view {

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      controller_(nullptr),
      vertex_buffer_(QOpenGLBuffer::VertexBuffer),
      facet_buffer_(QOpenGLBuffer::IndexBuffer) {}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::SetController(controller::Controller *controller) {
  controller_ = controller;
}

void OpenGLWidget::SetPerspective(bool perspective) {
  is_perspective_ = perspective;
  update();
}

void OpenGLWidget::SetBackgroundColor(float red, float green, float blue) {
  background_color_.setX(red);
  background_color_.setY(green);
  background_color_.setZ(blue);
  update();
}

void OpenGLWidget::SetVerticesColor(float red, float green, float blue) {
  vertices_color_.setX(red);
  vertices_color_.setY(green);
  vertices_color_.setZ(blue);
  update();
}

void OpenGLWidget::SetVerticesType(int type) {
  if (type == 0) {
    vertices_type_ = VerticesType::kNone;
  } else if (type == 1) {
    vertices_type_ = VerticesType::kRound;
  } else {
    vertices_type_ = VerticesType::kSquare;
  }
  update();
}

void OpenGLWidget::SetVerticesSize(float size) {
  vertices_size_ = size;
  update();
}

void OpenGLWidget::SetEdgesColor(float red, float green, float blue) {
  edges_color_.setX(red);
  edges_color_.setY(green);
  edges_color_.setZ(blue);
  update();
}

void OpenGLWidget::SetEdgesType(int type) {
  if (type == 0) {
    edges_type_ = LinesType::kNormal;
  } else if (type == 1) {
    edges_type_ = LinesType::kStripped;
  }
  update();
}

void OpenGLWidget::SetEdgesSize(float size) {
  edges_size_ = size;
  update();
}

void OpenGLWidget::ResetTranslate() {
  controller_->ResetTranslationMatrix();
  translation_.setToIdentity();
  update();
}

void OpenGLWidget::SetTranslate(float x, float y, float z) {
  controller_->SetTranslation(x, y, z);
  translation_ = QMatrix4x4(controller_->GetTranslationMatrix().GetRawData());
  update();
}

void OpenGLWidget::ResetScale() {
  controller_->ResetScalingMatrix();
  scaling_.setToIdentity();
  update();
}

void OpenGLWidget::SetScale(float scale) {
  controller_->SetScale(scale);
  scaling_ = QMatrix4x4(controller_->GetScalingMatrix().GetRawData());
  update();
}

void OpenGLWidget::ResetRotation() {
  controller_->ResetRotationMatrix();
  rotation_.setToIdentity();
  update();
}

void OpenGLWidget::SetRotation(float alpha, float beta, float gamma) {
  controller_->AddRotation(alpha, beta, gamma);
  rotation_ = QMatrix4x4(controller_->GetRotationMatrix().GetRawData());
  update();
}

bool OpenGLWidget::LoadFigureByPath(const QString &path) {
  bool is_parsed = controller_->SetFigureByPath(path.toStdString());
  if (!is_parsed) return false;

  auto figure = controller_->GetFigure();

  vertex_buffer_.destroy();
  facet_buffer_.destroy();

  program_.link();
  program_.bind();

  vertex_buffer_.create();
  vertex_buffer_.bind();

  facet_buffer_.create();
  facet_buffer_.bind();

  vertex_buffer_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vertex_buffer_.allocate(figure->GetVertexes(),
                          sizeof(GLfloat) * 3 * figure->GetVertexCount());

  facet_buffer_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  facet_buffer_.allocate(figure->GetFacets(),
                         sizeof(GLuint) * figure->GetFacetsIndexCount());

  vertex_buffer_.release();
  facet_buffer_.release();

  offset_.setToIdentity();
  offset_.translate(0, 0, -figure->GetRectangle().Depth() * 200);

  update();
  return true;
}

void OpenGLWidget::CloseFigure() {
  program_.bind();
  facet_buffer_.destroy();
  vertex_buffer_.destroy();
  program_.release();
  controller_->CloseFigure();
  update();
}

bool OpenGLWidget::GetPerspective() { return is_perspective_; }

QColor OpenGLWidget::GetBackgroundColor() {
  return QColor::fromRgbF(background_color_.x(), background_color_.y(),
                          background_color_.z());
}

SceneObjectSettings OpenGLWidget::GetPointsSettings() {
  SceneObjectSettings result;
  result.type = vertices_type_;
  result.size = vertices_size_;
  result.color = QColor::fromRgbF(vertices_color_.x(), vertices_color_.y(),
                                  vertices_color_.z());
  return result;
}

SceneObjectSettings OpenGLWidget::GetLineSettings() {
  SceneObjectSettings result;
  result.type = edges_type_;
  result.size = edges_size_;
  result.color =
      QColor::fromRgbF(edges_color_.x(), edges_color_.y(), edges_color_.z());
  return result;
}

void OpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  program_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
  program_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.glsl");
}

void OpenGLWidget::resizeGL(int w, int h) { SetProjection(); }

void OpenGLWidget::paintGL() {
  glClearColor(background_color_.x(), background_color_.y(),
               background_color_.z(), 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  auto figure = controller_->GetFigure();
  if (!figure) return;

  program_.bind();
  vertex_buffer_.bind();
  facet_buffer_.bind();

  program_.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
  program_.enableAttributeArray(0);

  SetProjection();

  program_.setUniformValue(
      "u_affine", projection_ * offset_ * translation_ * scaling_ * rotation_);

  glLineWidth(edges_size_);
  if (edges_type_ == LinesType::kNormal) {
    glDisable(GL_LINE_STIPPLE);
  } else {
    glLineStipple(1, 0xF00F);
    glEnable(GL_LINE_STIPPLE);
  }
  program_.setUniformValue("u_color", edges_color_.x(), edges_color_.y(),
                           edges_color_.z());
  glDrawElements(GL_LINES, figure->GetFacetsIndexCount(), GL_UNSIGNED_INT,
                 nullptr);

  if (vertices_type_ != VerticesType::kNone) {
    if (vertices_type_ == VerticesType::kRound) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(vertices_size_);
    program_.setUniformValue("u_color", vertices_color_.x(),
                             vertices_color_.y(), vertices_color_.z());
    glDrawArrays(GL_POINTS, 0, figure->GetVertexCount());
  }

  program_.disableAttributeArray(0);
  vertex_buffer_.release();
  facet_buffer_.release();
}

void OpenGLWidget::SetProjection() {
  const GLfloat vertical_fov = 20.0f;
  const GLfloat horizontal_aspect = (double)width() / height();
  const GLfloat vertical_aspect = 1.0f;
  projection_.setToIdentity();
  if (is_perspective_) {
    projection_.perspective(
        2 * atan(tan(vertical_fov * 0.5) / horizontal_aspect),
        horizontal_aspect, 0.1f, 1000000000.0f);
  } else {
    projection_.ortho(-horizontal_aspect, horizontal_aspect, -vertical_aspect,
                      vertical_aspect, 0.1f, 1000000000.0f);
  }
}

}  // namespace view
