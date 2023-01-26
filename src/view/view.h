#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QColorDialog>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMimeData>
#include <QSettings>
#include <QThread>

#include "controller.h"
#include "incorrect_file_dialog_window.h"
#include "opening_file_dialog_window.h"
#include "qgifimage.h"
#include "settings_saver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace view {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(controller::Controller *controller, QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_projection_perspective_clicked(bool checked);
  void on_background_color_clicked();
  void on_vertices_color_clicked();
  void on_vertices_type_activated(int index);
  void on_vertices_size_valueChanged(double arg1);
  void on_edges_color_clicked();
  void on_edges_type_activated(int index);
  void on_edges_size_valueChanged(double arg1);
  void on_transform_reset_clicked();
  void on_x_value_transform_valueChanged(double arg1);
  void on_y_value_transform_valueChanged(double arg1);
  void on_z_value_transform_valueChanged(double arg1);
  void on_rotation_reset_clicked();
  void on_x_value_rotation_slider_valueChanged(int value);
  void on_y_value_rotation_slider_valueChanged(int value);
  void on_z_value_rotation_slider_valueChanged(int value);
  void on_x_value_rotation_box_valueChanged(double arg1);
  void on_y_value_rotation_box_valueChanged(double arg1);
  void on_z_value_rotation_box_valueChanged(double arg1);
  void on_scale_reset_clicked();
  void on_scale_value_slider_sliderMoved(int position);
  void on_scale_value_box_valueChanged(double arg1);
  void on_actionHide_panel_toggled(bool arg1);
  void on_action_open_file_triggered();
  bool IsMouseInOpenGLWidget(const QPointF &position);
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void dragEnterEvent(QDragEnterEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void EnableInputFields(bool enable);
  void on_actionClose_triggered();
  void on_action_save_bmp_triggered();
  void on_action_save_jpeg_triggered();
  void on_action_gif_triggered();
  void SaveGifFrame();

 private:
  void OpenFile(const QString &path);
  void LoadSettings();

  QPoint mouse_position_;
  SettingsSaver settings_;

  controller::Controller *controller_;
  Ui::View *ui_;
  bool is_clicked_in_glwidget_ = false;

  QGifImage *gif_ = nullptr;
  QTimer *timer_ = nullptr;
  QThread *timer_thread_ = nullptr;
  int time_;
};

}  // namespace view

#endif  // VIEW_VIEW_H_
