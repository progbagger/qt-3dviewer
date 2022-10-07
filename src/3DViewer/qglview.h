#ifndef OPEN_GL_WINDOW_OPEN_GL_WINDOW_H
#define OPEN_GL_WINDOW_OPEN_GL_WINDOW_H
#define GL_SILENCE_DEPRECATION

#include <QFile>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <cmath>

#ifdef __cplusplus
extern "C" {
#endif

#include "../affine.h"

#ifdef __cplusplus
}
#endif

#define MIN_SCALE 0.25
#define MAX_SCALE 5.0
#define AXES_SCALING_MULTIPLIER 3.0
#define MOVING_MULTIPLIER 500.0
#define SHIFT_MOVING_MULTIPLIER 5.0
#define POV 1.0 / (tan(10.0 * M_PI / 180.0 / 2.0))

class QglView : public QOpenGLWidget {
  Q_OBJECT

 private:
  double xShift, yShift, zShift;
  double zNear;
  double xRot, yRot, zRot;
  QPoint mPos;
  void drawModel();
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);
  Obj *currentModel;
  double *currentVertexes;
  void saveSettings();
  void loadSettings();
  void emitSignals();
  void resetVertexes();

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

 public:
  QglView(QWidget *parent = nullptr);
  ~QglView();
  bool isModelClosed;
  QString modelPath;
  void setXRot(double value);
  void setYRot(double value);
  size_t getVertexCount();
  size_t getFacesCount();
  bool setModel(const QString &filePath);
  void cleanModel();
  void resetSettings();
  void resetView();
  void keyPressEvent(QKeyEvent *);
  int pointsStyle, lineStyle, projectionType, vertexesStyle;
  double lineWidth, pointsSize;
  unsigned char rLineColor, gLineColor, bLineColor;
  unsigned char rPointColor, gPointColor, bPointColor;
  unsigned char rBgColor, gBgColor, bBgColor;
  double getMinZ();
  double getMaxZ();
  double getZNear();
  void setZNear(double value);
  double getMinY();
  double getMaxY();
  double getXShift();
  double getZShift();
  void setZShift(double value);
  void setXShift(double value);
  double getMinX();
  double getMaxX();
  double getYShift();
  void setYShift(double value);
  double getXRot();
  double getYRot();
  bool isModelExist();
  bool isPreviousModelLoaded;

 signals:
  void changeXRotSlider(double value);
  void changeYRotSlider(double value);
  void changeXShiftSlider(double value);
  void changeYShiftSlider(double value);
  void changeZShiftSlider(double value);
  void changeScaleSlider(double value);

  void setSavedModel(QString filePath);

  void changeXShiftBox(double value);
  void changeYShiftBox(double value);
  void changeZShiftBox(double value);
  void changeXRotBox(double value);
  void changeYRotBox(double value);
  void changeScaleBox(double value);
};

#endif  // OPEN_GL_WINDOW_OPEN_GL_WINDOW_H
