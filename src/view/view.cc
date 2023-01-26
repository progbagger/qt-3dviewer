#include "view.h"

#include "./ui_view.h"

namespace view {

View::View(controller::Controller* controller, QWidget* parent)
    : QMainWindow(parent),
      settings_(QDir::homePath() + QDir::separator() + '.' + qAppName(), this),
      controller_(controller),
      ui_(new Ui::View) {
  ui_->setupUi(this);
  ui_->openglwidget->SetController(controller_);
  LoadSettings();
}

View::~View() {
  settings_.SaveProjectionType(ui_->openglwidget->GetPerspective());
  settings_.SaveBackgroundColor(ui_->openglwidget->GetBackgroundColor());
  settings_.SavePointStyle(ui_->openglwidget->GetPointsSettings());
  settings_.SaveLineStyle(ui_->openglwidget->GetLineSettings());
  delete ui_;
  if (timer_thread_) timer_thread_->terminate();
  delete timer_;
  delete timer_thread_;
  delete gif_;
}

void View::on_projection_perspective_clicked(bool checked) {
  ui_->openglwidget->SetPerspective(checked);
}

void View::on_background_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Background color");
  ui_->openglwidget->SetBackgroundColor(color.redF(), color.greenF(),
                                        color.blueF());
}

void View::on_vertices_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Vertices color");
  ui_->openglwidget->SetVerticesColor(color.redF(), color.greenF(),
                                      color.blueF());
}

void View::on_vertices_type_activated(int index) {
  ui_->vertices_size->setEnabled(
      (!controller_->GetFigure() || index == 0) ? false : true);
  ui_->openglwidget->SetVerticesType(index);
}

void View::on_vertices_size_valueChanged(double arg1) {
  ui_->openglwidget->SetVerticesSize(arg1);
}

void View::on_edges_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Edges color");
  ui_->openglwidget->SetEdgesColor(color.redF(), color.greenF(), color.blueF());
}

void View::on_edges_type_activated(int index) {
  ui_->openglwidget->SetEdgesType(index);
}

void View::on_edges_size_valueChanged(double arg1) {
  ui_->openglwidget->SetEdgesSize(arg1);
}

void View::on_transform_reset_clicked() {
  ui_->x_value_transform->setValue(0);
  ui_->y_value_transform->setValue(0);
  ui_->z_value_transform->setValue(0);
  ui_->openglwidget->ResetTranslate();
}

void View::on_x_value_transform_valueChanged(double arg1) {
  ui_->openglwidget->SetTranslate(arg1, ui_->y_value_transform->value(),
                                  ui_->z_value_transform->value());
}

void View::on_y_value_transform_valueChanged(double arg1) {
  ui_->openglwidget->SetTranslate(ui_->x_value_transform->value(), arg1,
                                  ui_->z_value_transform->value());
}

void View::on_z_value_transform_valueChanged(double arg1) {
  ui_->openglwidget->SetTranslate(ui_->x_value_transform->value(),
                                  ui_->y_value_transform->value(), arg1);
}

void View::on_rotation_reset_clicked() {
  ui_->x_value_rotation_box->setValue(0);
  ui_->y_value_rotation_box->setValue(0);
  ui_->z_value_rotation_box->setValue(0);
  ui_->x_value_rotation_slider->setValue(0);
  ui_->y_value_rotation_slider->setValue(0);
  ui_->z_value_rotation_slider->setValue(0);
  ui_->openglwidget->ResetRotation();
}

void View::on_x_value_rotation_slider_valueChanged(int value) {
  float change = value / 100.0;
  ui_->x_value_rotation_box->setValue(change);
  ui_->openglwidget->SetRotation(change, ui_->y_value_rotation_box->value(),
                                 ui_->z_value_rotation_box->value());
}

void View::on_y_value_rotation_slider_valueChanged(int value) {
  float change = value / 100.0;
  ui_->y_value_rotation_box->setValue(change);
  ui_->openglwidget->SetRotation(ui_->x_value_rotation_box->value(), change,
                                 ui_->z_value_rotation_box->value());
}

void View::on_z_value_rotation_slider_valueChanged(int value) {
  float change = value / 100.0;
  ui_->z_value_rotation_box->setValue(change);
  ui_->openglwidget->SetRotation(ui_->x_value_rotation_box->value(),
                                 ui_->y_value_rotation_box->value(), change);
}

void View::on_x_value_rotation_box_valueChanged(double arg1) {
  ui_->x_value_rotation_slider->setValue(arg1 * 100);
  ui_->openglwidget->SetRotation(arg1, ui_->y_value_rotation_box->value(),
                                 ui_->z_value_rotation_box->value());
}

void View::on_y_value_rotation_box_valueChanged(double arg1) {
  ui_->y_value_rotation_slider->setValue(arg1 * 100);
  ui_->openglwidget->SetRotation(ui_->x_value_rotation_box->value(), arg1,
                                 ui_->z_value_rotation_box->value());
}

void View::on_z_value_rotation_box_valueChanged(double arg1) {
  ui_->z_value_rotation_slider->setValue(arg1 * 100);
  ui_->openglwidget->SetRotation(ui_->x_value_rotation_box->value(),
                                 ui_->y_value_rotation_box->value(), arg1);
}

void View::on_scale_reset_clicked() {
  ui_->scale_value_box->setValue(1);
  ui_->scale_value_slider->setValue(100);
  ui_->openglwidget->ResetScale();
}

void View::on_scale_value_slider_sliderMoved(int position) {
  ui_->scale_value_box->setValue(position / 100.0);
  ui_->openglwidget->SetScale(position / 100.0);
}

void View::on_scale_value_box_valueChanged(double arg1) {
  ui_->scale_value_slider->setValue(arg1 * 100);
  ui_->openglwidget->SetScale(arg1);
}

void View::on_actionHide_panel_toggled(bool arg1) {
  ui_->tab_widget->setVisible(!arg1);
}

void View::on_action_open_file_triggered() {
  QString path = QFileDialog().getOpenFileName(
      this, "Select model", QDir::homePath(), "Object file (*.obj)");
  OpenFile(path);
}

bool View::IsMouseInOpenGLWidget(const QPointF& position) {
  if (!controller_->GetFigure()) return false;
  const QPointF& glwidget_top_left = ui_->openglwidget->geometry().topLeft();
  const QPointF& glwidget_bottom_right =
      ui_->openglwidget->geometry().bottomRight();
  if (position.x() < glwidget_top_left.x()) return false;
  if (position.y() < glwidget_top_left.y()) return false;
  if (position.x() > glwidget_bottom_right.x()) return false;
  if (position.y() > glwidget_bottom_right.y()) return false;
  return true;
}

void View::mousePressEvent(QMouseEvent* event) {
  if (IsMouseInOpenGLWidget(event->scenePosition())) {
    is_clicked_in_glwidget_ = true;
    mouse_position_ = event->pos();
  } else {
    is_clicked_in_glwidget_ = false;
  }
}

void View::mouseMoveEvent(QMouseEvent* event) {
  if (is_clicked_in_glwidget_) {
    const QPoint& current_pos = event->pos();
    double diff_x = current_pos.x() - mouse_position_.x();
    double diff_y = current_pos.y() - mouse_position_.y();
    if (event->buttons() & Qt::LeftButton) {
      double y_rotation = ui_->x_value_rotation_box->value() + diff_y / 2.0;
      if (y_rotation < -180.0)
        y_rotation = 180.0;
      else if (y_rotation > 180.0)
        y_rotation = -180.0;
      on_x_value_rotation_box_valueChanged(y_rotation);
      double x_rotation = ui_->y_value_rotation_box->value() + diff_x / 2.0;
      if (x_rotation < -180.0)
        x_rotation = 180.0;
      else if (x_rotation > 180.0)
        x_rotation = -180.0;
      on_y_value_rotation_box_valueChanged(x_rotation);
    } else if (event->buttons() & Qt::RightButton) {
      double z_rotation =
          ui_->z_value_rotation_box->value() - diff_x / 4.0 - diff_y / 4.0;
      if (z_rotation < -180.0)
        z_rotation = 180.0;
      else if (z_rotation > 180.0)
        z_rotation = -180.0;
      on_z_value_rotation_box_valueChanged(z_rotation);
    } else if (event->buttons() & Qt::MiddleButton) {
      if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
        ui_->z_value_transform->setValue(ui_->z_value_transform->value() +
                                         diff_y / 10.0);
        ui_->x_value_transform->setValue(ui_->x_value_transform->value() +
                                         diff_x / 500.0);
      } else {
        ui_->y_value_transform->setValue(ui_->y_value_transform->value() -
                                         diff_y / 500.0);
        ui_->x_value_transform->setValue(ui_->x_value_transform->value() +
                                         diff_x / 500.0);
      }
    }
    mouse_position_ = current_pos;
  }
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  is_clicked_in_glwidget_ = false;
}

void View::dropEvent(QDropEvent* event) {
  QString path =
      event->mimeData()->urls().at(0).toString().replace("file://", "");
  OpenFile(path);
}

void View::dragEnterEvent(QDragEnterEvent* event) {
  event->acceptProposedAction();
}

void View::wheelEvent(QWheelEvent* event) {
  if (IsMouseInOpenGLWidget(event->position())) {
    ui_->scale_value_box->setValue(ui_->scale_value_box->value() +
                                   event->angleDelta().y() / 4000.0);
  }
}

void View::EnableInputFields(bool enable) {
  ui_->actionClose->setEnabled(enable);
  ui_->action_save_bmp->setEnabled(enable);
  ui_->action_save_jpeg->setEnabled(enable);
  ui_->edges_color->setEnabled(enable);
  ui_->vertices_color->setEnabled(enable);
  ui_->vertices_size->setEnabled(enable);
  ui_->edges_size->setEnabled(enable);
  ui_->edges_type->setEnabled(enable);
  ui_->vertices_type->setEnabled(enable);
  ui_->projection_perspective->setEnabled(enable);
  ui_->transform_reset->setEnabled(enable);
  ui_->x_value_transform->setEnabled(enable);
  ui_->y_value_transform->setEnabled(enable);
  ui_->z_value_transform->setEnabled(enable);
  ui_->scale_value_box->setEnabled(enable);
  ui_->scale_reset->setEnabled(enable);
  ui_->rotation_reset->setEnabled(enable);
  ui_->x_value_rotation_box->setEnabled(enable);
  ui_->x_value_rotation_slider->setEnabled(enable);
  ui_->y_value_rotation_box->setEnabled(enable);
  ui_->y_value_rotation_slider->setEnabled(enable);
  ui_->z_value_rotation_box->setEnabled(enable);
  ui_->z_value_rotation_slider->setEnabled(enable);
  ui_->scale_value_slider->setEnabled(enable);
  ui_->action_gif->setEnabled(enable);
}

void View::on_actionClose_triggered() {
  EnableInputFields(false);
  ui_->filename->setText("-");
  ui_->number_of_vertices->setText("-");
  ui_->number_of_edges->setText("-");
  ui_->number_of_facets->setText("-");
  ui_->width->setText("-");
  ui_->height->setText("-");
  ui_->depth->setText("-");
  on_rotation_reset_clicked();
  on_transform_reset_clicked();
  on_scale_reset_clicked();
  ui_->openglwidget->CloseFigure();
}

void View::on_action_save_bmp_triggered() {
  QImage frame = ui_->openglwidget->grabFramebuffer();
  QString save_path = QFileDialog::getSaveFileName(
      this, "Save screenshot as bmp", QDir::homePath());
  QString extension = ".bmp";
  frame.save(save_path + extension);
}

void View::on_action_save_jpeg_triggered() {
  QImage frame = ui_->openglwidget->grabFramebuffer();
  QString save_path = QFileDialog::getSaveFileName(
      this, "Save screenshot as jpeg", QDir::homePath());
  QString extension = ".jpeg";
  frame.save(save_path + extension);
}

void View::OpenFile(const QString& path) {
  int id = QFontDatabase::addApplicationFont(":/lemonmilk.otf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  QFont font(family);
  OpeningFileDialogWindow* opening_dialog = new OpeningFileDialogWindow(this);
  opening_dialog->setFont(font);
  opening_dialog->open();
  bool is_parsed = ui_->openglwidget->LoadFigureByPath(path);
  if (!is_parsed) {
    delete opening_dialog;
    if (!path.isEmpty()) {
      IncorrectFileDialogWindow* dialog = new IncorrectFileDialogWindow(this);
      dialog->setFont(font);
      dialog->exec();
      delete dialog;
    }
  } else {
    opening_dialog->SetProgressBarValue(50);
    EnableInputFields(true);
    auto figure = controller_->GetFigure();
    ui_->filename->setText(QString(figure->GetName().data()));
    ui_->number_of_vertices->setText(QString::number(figure->GetVertexCount()));
    ui_->number_of_edges->setText(QString::number(figure->GetEdgesCount()));
    ui_->number_of_facets->setText(QString::number(figure->GetFacetsCount()));
    ui_->width->setText(QString::number(ceil(figure->GetRectangle().Width())) +
                        " pixels");
    ui_->height->setText(
        QString::number(ceil(figure->GetRectangle().Height())) + " pixels");
    ui_->depth->setText(QString::number(ceil(figure->GetRectangle().Depth())) +
                        " pixels");
    opening_dialog->SetProgressBarValue(100);
    delete opening_dialog;
    on_transform_reset_clicked();
    on_rotation_reset_clicked();
    on_scale_reset_clicked();
  }
}

void View::LoadSettings() {
  ui_->projection_perspective->setChecked(settings_.GetProjectionType());
  on_projection_perspective_clicked(ui_->projection_perspective->isChecked());
  QColor background_color = settings_.GetBackgroundColor();
  ui_->openglwidget->SetBackgroundColor(background_color.redF(),
                                        background_color.greenF(),
                                        background_color.blueF());
  SceneObjectSettings points_settings = settings_.GetPointStyle();
  ui_->vertices_type->setCurrentIndex(points_settings.type);
  on_vertices_type_activated(ui_->vertices_type->currentIndex());
  ui_->vertices_size->setValue(points_settings.size);
  on_vertices_size_valueChanged(ui_->vertices_size->value());
  ui_->openglwidget->SetVerticesColor(points_settings.color.redF(),
                                      points_settings.color.greenF(),
                                      points_settings.color.blueF());
  SceneObjectSettings line_settings = settings_.GetLineStyle();
  ui_->edges_type->setCurrentIndex(line_settings.type);
  on_edges_type_activated(ui_->edges_type->currentIndex());
  ui_->edges_size->setValue(line_settings.size);
  on_edges_size_valueChanged(ui_->edges_size->value());
  ui_->openglwidget->SetEdgesColor(line_settings.color.redF(),
                                   line_settings.color.greenF(),
                                   line_settings.color.blueF());
}

void View::on_action_gif_triggered() {
  timer_ = new QTimer;
  timer_->setInterval(100);
  timer_thread_ = new QThread(this);
  gif_ = new QGifImage;
  time_ = 0;
  timer_->moveToThread(timer_thread_);
  connect(timer_, SIGNAL(timeout()), this, SLOT(SaveGifFrame()));
  connect(timer_thread_, SIGNAL(started()), timer_, SLOT(start()));
  connect(timer_thread_, SIGNAL(finished()), timer_, SLOT(stop()));
  timer_thread_->start();
}

void View::SaveGifFrame() {
  time_++;
  QImage frame = ui_->openglwidget->grabFramebuffer().scaled(640, 480);
  gif_->addFrame(frame, 100);
  ui_->statusBar->showMessage("Recording gif. Estimated time: " +
                              QString::number(5.0 - time_ / 10.0, 'f', 2) +
                              " sec");
  if (time_ == 50) {
    timer_thread_->terminate();
    ui_->statusBar->clearMessage();
    QString save_path = QFileDialog::getSaveFileName(
        this, "Save screencast as gif", QDir::homePath());
    QString extension = ".gif";
    gif_->save(save_path + extension);
    delete timer_;
    timer_ = nullptr;
    delete timer_thread_;
    timer_thread_ = nullptr;
    delete gif_;
    gif_ = nullptr;
  }
}

}  // namespace view
