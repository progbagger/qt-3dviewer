#ifndef VIEW_OPENGLWIDGET_H_
#define VIEW_OPENGLWIDGET_H_
#define GL_SILENCE_DEPRECATION

#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "controller.h"
#include "settings_saver.h"

namespace view {

enum VerticesType { kNone, kRound, kSquare };

enum LinesType { kNormal, kStripped };

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  OpenGLWidget(QWidget* parent = nullptr);
  ~OpenGLWidget();

  void SetController(controller::Controller* controller);

  void SetPerspective(bool perspective);
  void SetBackgroundColor(float red_, float green_, float blue_);
  void SetVerticesColor(float red_, float green_, float blue_);
  void SetVerticesType(int type);
  void SetVerticesSize(float size);
  void SetEdgesColor(float red_, float green_, float blue_);
  void SetEdgesType(int type);
  void SetEdgesSize(float size);

  void ResetTranslate();
  void SetTranslate(float x, float y, float z);
  void ResetScale();
  void SetScale(float scale);
  void ResetRotation();
  void SetRotation(float alpha, float beta, float gamma);

  bool LoadFigureByPath(const QString& path);
  void CloseFigure();

  bool GetPerspective();
  QColor GetBackgroundColor();
  SceneObjectSettings GetPointsSettings();
  SceneObjectSettings GetLineSettings();

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void SetProjection();

  controller::Controller* controller_;

  QOpenGLShaderProgram program_;

  QOpenGLBuffer vertex_buffer_;
  QOpenGLBuffer facet_buffer_;

  bool is_perspective_ = true;

  QMatrix4x4 translation_;
  QMatrix4x4 scaling_;
  QMatrix4x4 rotation_;
  QMatrix4x4 projection_;
  QMatrix4x4 offset_;

  QVector3D background_color_;
  QVector3D vertices_color_;
  VerticesType vertices_type_;
  float vertices_size_;
  QVector3D edges_color_;
  LinesType edges_type_;
  float edges_size_;
};

}  // namespace view

#endif  // VIEW_OPENGLWIDGET_H_
