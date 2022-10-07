#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QColorDialog>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QTimer>
#include <QVector3D>
#include <QWidget>
#include <string>

#include "../Qtgifimage/gifimage/qgifimage.h"
#include "dialog.h"
#include "qglview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pointsSize_sliderMoved(int position);
  void on_lineStyle_currentTextChanged(const QString &arg1);
  void on_red_valueChanged(int value);
  void on_green_valueChanged(int value);
  void on_blue_valueChanged(int value);
  void on_pointRed_valueChanged(int value);
  void on_pointGreen_valueChanged(int value);
  void on_pointBlue_valueChanged(int value);
  void on_lineWidth_valueChanged(int value);
  void on_rBgColor_valueChanged(int value);
  void on_gBgColor_valueChanged(int value);
  void on_bBgColor_valueChanged(int value);
  void keyPressEvent(QKeyEvent *);
  void on_openFile_triggered();
  void setModelInfo();
  void on_closeFile_triggered();
  void on_resetView_clicked();
  void disableButtons();
  void enableButtons();
  void on_projectionType_currentTextChanged(const QString &arg1);
  void on_togglePoints_currentTextChanged(const QString &arg1);
  Dialog *showDialog(QString text, bool exec);
  void setSlidersPositions();
  void setSlidersEdges();
  void on_xAxisRotationInput_valueChanged(double arg1);
  void on_xRot_valueChanged(int value);
  void on_xShift_valueChanged(int value);
  void on_zShift_valueChanged(int value);
  void on_yShift_valueChanged(int value);
  void on_yRot_valueChanged(int value);
  void on_xAxisShiftInput_valueChanged(double arg1);
  void on_zAxisShiftInput_valueChanged(double arg1);
  void on_yAxisShiftInput_valueChanged(double arg1);
  void on_yAxisRotationInput_valueChanged(double arg1);
  void save_image();
  void record_gif_file();
  void make_gif();
  void on_scale_valueChanged(int value);
  void on_scaleInput_valueChanged(double arg1);

 public slots:
  void xRotChanged(double value);
  void yRotChanged(double value);
  void xShiftChanged(double value);
  void yShiftChanged(double value);
  void zShiftChanged(double value);
  void scaleChanged(double value);

  void setSavedModelName(QString filePath);

  void xShiftBoxChanged(double value);
  void yShiftBoxChanged(double value);
  void zShiftBoxChanged(double value);
  void xRotBoxChanged(double value);
  void yRotBoxChanged(double value);
  void scaleBoxChanged(double value);

 private:
  Ui::MainWindow *ui;
  QString prevModelName;
  QFile *save_ptr;
  QGifImage *gif;
  QTimer *timer;
  int frame_count;
  void close_file();
};
#endif  // MAINWINDOW_H
