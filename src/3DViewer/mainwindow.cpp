#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setWindowTitle("3DViewer");
  ui->setupUi(this);
  disableButtons();

  // Sliders signals
  connect(ui->openGLWidget, &QglView::changeXRotSlider, this,
          &MainWindow::xRotChanged);
  connect(ui->openGLWidget, &QglView::changeYRotSlider, this,
          &MainWindow::yRotChanged);
  connect(ui->openGLWidget, &QglView::changeXShiftSlider, this,
          &MainWindow::xShiftChanged);
  connect(ui->openGLWidget, &QglView::changeYShiftSlider, this,
          &MainWindow::yShiftChanged);
  connect(ui->openGLWidget, &QglView::changeZShiftSlider, this,
          &MainWindow::zShiftChanged);
  connect(ui->openGLWidget, &QglView::changeScaleSlider, this,
          &MainWindow::scaleChanged);

  // File open signal
  connect(ui->openGLWidget, &QglView::setSavedModel, this,
          &MainWindow::setSavedModelName);

  // Double spin boxes signals
  connect(ui->openGLWidget, &QglView::changeXShiftBox, this,
          &MainWindow::xShiftBoxChanged);
  connect(ui->openGLWidget, &QglView::changeYShiftBox, this,
          &MainWindow::yShiftBoxChanged);
  connect(ui->openGLWidget, &QglView::changeZShiftBox, this,
          &MainWindow::zShiftBoxChanged);
  connect(ui->openGLWidget, &QglView::changeXRotBox, this,
          &MainWindow::xRotBoxChanged);
  connect(ui->openGLWidget, &QglView::changeYRotBox, this,
          &MainWindow::yRotBoxChanged);
  connect(ui->openGLWidget, &QglView::changeScaleBox, this,
          &MainWindow::scaleBoxChanged);

  // GIF signals
  connect(ui->save_bmp, SIGNAL(triggered()), this, SLOT(save_image()));
  connect(ui->save_jpeg, SIGNAL(triggered()), this, SLOT(save_image()));
  connect(ui->save_giff, SIGNAL(triggered()), this, SLOT(save_image()));

  ui->recording->setVisible(false);
  ui->modelInfo->setText("- Vertexes: 0\n- Faces: 0");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pointsSize_sliderMoved(int position) {
  ui->openGLWidget->pointsSize = position / 10.0;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_lineStyle_currentTextChanged(const QString &arg1) {
  if (arg1 == "Smooth")
    ui->openGLWidget->lineStyle = 0;
  else
    ui->openGLWidget->lineStyle = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_red_valueChanged(int value) {
  ui->openGLWidget->rLineColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_green_valueChanged(int value) {
  ui->openGLWidget->gLineColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_blue_valueChanged(int value) {
  ui->openGLWidget->bLineColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_pointRed_valueChanged(int value) {
  ui->openGLWidget->rPointColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_pointGreen_valueChanged(int value) {
  ui->openGLWidget->gPointColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_pointBlue_valueChanged(int value) {
  ui->openGLWidget->bPointColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_lineWidth_valueChanged(int value) {
  ui->openGLWidget->lineWidth = value / 10.0;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_rBgColor_valueChanged(int value) {
  ui->openGLWidget->rBgColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_gBgColor_valueChanged(int value) {
  ui->openGLWidget->gBgColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::on_bBgColor_valueChanged(int value) {
  ui->openGLWidget->bBgColor = value;
  if (!ui->openGLWidget->isHidden()) ui->openGLWidget->update();
}

void MainWindow::keyPressEvent(QKeyEvent *ke) {
  ui->openGLWidget->keyPressEvent(ke);
}

void MainWindow::setModelInfo() {
  ui->modelInfo->setText(
      "- Vertexes: " + QString::number(ui->openGLWidget->getVertexCount()) +
      "\n- Faces: " + QString::number(ui->openGLWidget->getFacesCount()));
}

Dialog *MainWindow::showDialog(QString text, bool exec = false) {
  Dialog *dWindow = new Dialog(this);
  dWindow->setModelName(text);
  dWindow->setModal(true);
  if (exec) {
    dWindow->exec();
  } else {
    dWindow->disableButton();
    dWindow->open();
  }
  return dWindow;
}

void MainWindow::setSlidersPositions() {
  ui->projectionType->setCurrentIndex(ui->openGLWidget->projectionType);
  ui->togglePoints->setCurrentIndex((ui->openGLWidget->pointsStyle - 1) % 3);
  ui->pointsSize->setValue(ui->openGLWidget->pointsSize * 10.0);
  ui->pointRed->setValue(ui->openGLWidget->rPointColor);
  ui->pointGreen->setValue(ui->openGLWidget->gPointColor);
  ui->pointBlue->setValue(ui->openGLWidget->bPointColor);
  ui->lineStyle->setCurrentIndex(ui->openGLWidget->lineStyle);
  ui->lineWidth->setValue(ui->openGLWidget->lineWidth * 10.0);
  ui->red->setValue(ui->openGLWidget->rLineColor);
  ui->green->setValue(ui->openGLWidget->gLineColor);
  ui->blue->setValue(ui->openGLWidget->bLineColor);
  ui->rBgColor->setValue(ui->openGLWidget->rBgColor);
  ui->gBgColor->setValue(ui->openGLWidget->gBgColor);
  ui->bBgColor->setValue(ui->openGLWidget->bBgColor);
  ui->xAxisRotationInput->setValue(ui->openGLWidget->getYRot());
  ui->xAxisShiftInput->setValue(ui->openGLWidget->getXShift());
  ui->yAxisShiftInput->setValue(ui->openGLWidget->getYShift());
  ui->zAxisShiftInput->setValue(ui->openGLWidget->getZShift());
  ui->yAxisRotationInput->setValue(ui->openGLWidget->getXRot());
  ui->scaleInput->setValue(ui->openGLWidget->getZNear());
  ui->yShift->setValue(ui->openGLWidget->getYShift() * 1000.0);
  ui->scale->setValue(ui->openGLWidget->getZNear() * 1000.0);
  //  ui->xShift->setSingleStep(-1);
  ui->xShift->setValue(ui->openGLWidget->getXShift() * 1000.0);
  ui->zShift->setValue(ui->openGLWidget->getZShift() * 1000.0);
}

void MainWindow::setSlidersEdges() {
  ui->zShift->setMinimum(ui->openGLWidget->getMinZ() * 1000.0);
  ui->zShift->setMaximum(ui->openGLWidget->getMaxZ() * 1000.0);
  ui->yShift->setMinimum(ui->openGLWidget->getMinY() * 1000.0);
  ui->yShift->setMaximum(ui->openGLWidget->getMaxY() * 1000.0);
  ui->xShift->setMinimum(ui->openGLWidget->getMinX() * 1000.0);
  ui->xShift->setMaximum(ui->openGLWidget->getMaxX() * 1000.0);
  ui->scale->setMinimum(MIN_SCALE * 1000.0);
  ui->scale->setMaximum(MAX_SCALE * 1000.0);
  ui->xAxisRotationInput->setMinimum(0.0);
  ui->xAxisRotationInput->setMaximum(360.0);
  ui->xAxisShiftInput->setMinimum(ui->openGLWidget->getMinX());
  ui->xAxisShiftInput->setMaximum(ui->openGLWidget->getMaxX());
  ui->yAxisShiftInput->setMinimum(ui->openGLWidget->getMinY());
  ui->yAxisShiftInput->setMaximum(ui->openGLWidget->getMaxY());
  ui->zAxisShiftInput->setMinimum(ui->openGLWidget->getMinZ());
  ui->zAxisShiftInput->setMaximum(ui->openGLWidget->getMaxZ());
  ui->scaleInput->setMinimum(MIN_SCALE);
  ui->scaleInput->setMaximum(MAX_SCALE);
  ui->yAxisRotationInput->setMinimum(-180.0);
  ui->yAxisRotationInput->setMaximum(180.0);
}

void MainWindow::on_openFile_triggered() {
  QString file;
  if (prevModelName.isEmpty()) {
    file = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(),
                                        "Object files (*.obj)");
  } else {
    file = prevModelName;
    prevModelName = "";
  }
  if (!file.isEmpty() && QFile::exists(file)) {
    QString modelName =
        file.last(file.length() - file.lastIndexOf(QDir::separator()) - 1);
    qDebug() << modelName;
    if (modelName == file)
      modelName = file.last(file.length() - file.lastIndexOf('/') - 1);
    Dialog *dWindow = showDialog("Loading model " + modelName);
    bool check = ui->openGLWidget->setModel(file);
    if (check) {
      ui->openGLWidget->modelPath = file;
      setModelInfo();
      delete dWindow;
      ui->objectName->setText(modelName);
      enableButtons();
      setSlidersEdges();
      setSlidersPositions();
    } else {
      delete dWindow;
      dWindow = showDialog("This file is incorrect", true);
      delete dWindow;
    }
  }
}

void MainWindow::on_closeFile_triggered() {
  ui->openGLWidget->cleanModel();
  ui->openGLWidget->isModelClosed = true;
  disableButtons();
  ui->modelInfo->setText("- Vertexes: 0\n- Faces: 0");
  ui->objectName->setText("");
}

void MainWindow::on_resetView_clicked() { ui->openGLWidget->resetView(); }

void MainWindow::disableButtons() {
  ui->resetView->setDisabled(true);
  ui->togglePoints->setDisabled(true);
  ui->pointsSize->setDisabled(true);
  ui->pointRed->setDisabled(true);
  ui->pointGreen->setDisabled(true);
  ui->pointBlue->setDisabled(true);
  ui->lineStyle->setDisabled(true);
  ui->lineWidth->setDisabled(true);
  ui->red->setDisabled(true);
  ui->green->setDisabled(true);
  ui->blue->setDisabled(true);
  ui->rBgColor->setDisabled(true);
  ui->gBgColor->setDisabled(true);
  ui->bBgColor->setDisabled(true);
  ui->xRot->setDisabled(true);
  ui->yRot->setDisabled(true);
  ui->xShift->setDisabled(true);
  ui->yShift->setDisabled(true);
  ui->zShift->setDisabled(true);
  ui->projectionType->setDisabled(true);
  ui->xAxisShiftInput->setDisabled(true);
  ui->yAxisShiftInput->setDisabled(true);
  ui->yAxisRotationInput->setDisabled(true);
  ui->zAxisShiftInput->setDisabled(true);
  ui->xAxisRotationInput->setDisabled(true);
  ui->closeFile->setDisabled(true);
  ui->scale->setDisabled(true);
  ui->scaleInput->setDisabled(true);
  ui->menuSave_File->setDisabled(true);
}

void MainWindow::enableButtons() {
  ui->resetView->setDisabled(false);
  ui->togglePoints->setDisabled(false);
  ui->pointsSize->setDisabled(false);
  ui->pointRed->setDisabled(false);
  ui->pointGreen->setDisabled(false);
  ui->pointBlue->setDisabled(false);
  ui->lineStyle->setDisabled(false);
  ui->lineWidth->setDisabled(false);
  ui->red->setDisabled(false);
  ui->green->setDisabled(false);
  ui->blue->setDisabled(false);
  ui->rBgColor->setDisabled(false);
  ui->gBgColor->setDisabled(false);
  ui->bBgColor->setDisabled(false);
  ui->xRot->setDisabled(false);
  ui->yRot->setDisabled(false);
  ui->xShift->setDisabled(false);
  ui->yShift->setDisabled(false);
  ui->zShift->setDisabled(false);
  ui->projectionType->setDisabled(false);
  ui->xAxisShiftInput->setDisabled(false);
  ui->yAxisShiftInput->setDisabled(false);
  ui->yAxisRotationInput->setDisabled(false);
  ui->zAxisShiftInput->setDisabled(false);
  ui->xAxisRotationInput->setDisabled(false);
  ui->closeFile->setDisabled(false);
  ui->scale->setDisabled(false);
  ui->scaleInput->setDisabled(false);
  ui->menuSave_File->setDisabled(false);
}

void MainWindow::xRotChanged(double value) {
  if (value != ui->xRot->value()) ui->xRot->setValue(value);
}
void MainWindow::yRotChanged(double value) {
  if (value != ui->yRot->value()) ui->yRot->setValue(value);
}
void MainWindow::xShiftChanged(double value) {
  if (value != ui->xShift->value()) ui->xShift->setValue(value);
}
void MainWindow::yShiftChanged(double value) {
  if (value != ui->yShift->value()) ui->yShift->setValue(value);
}
void MainWindow::zShiftChanged(double value) {
  if (value != ui->zShift->value()) ui->zShift->setValue(value);
}

void MainWindow::setSavedModelName(QString filePath) {
  prevModelName = filePath;
  on_openFile_triggered();
}

void MainWindow::on_projectionType_currentTextChanged(const QString &arg1) {
  if (arg1 == "Central")
    ui->openGLWidget->projectionType = 0;
  else
    ui->openGLWidget->projectionType = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_togglePoints_currentTextChanged(const QString &arg1) {
  if (arg1 == "Circle") {
    ui->openGLWidget->pointsStyle = 1;
  } else if (arg1 == "Square") {
    ui->openGLWidget->pointsStyle = 2;
  } else {
    ui->openGLWidget->pointsStyle = 0;
  }
  ui->pointsSize->setDisabled(!ui->openGLWidget->pointsStyle);
  ui->pointRed->setDisabled(!ui->openGLWidget->pointsStyle);
  ui->pointGreen->setDisabled(!ui->openGLWidget->pointsStyle);
  ui->pointBlue->setDisabled(!ui->openGLWidget->pointsStyle);
  ui->openGLWidget->update();
}

void MainWindow::on_xAxisRotationInput_valueChanged(double arg1) {
  ui->openGLWidget->setXRot(arg1);
}

void MainWindow::on_xRot_valueChanged(int value) {
  ui->openGLWidget->setXRot(value / 10000.0);
}

void MainWindow::on_xShift_valueChanged(int value) {
  ui->openGLWidget->setXShift(value / 1000.0);
}

void MainWindow::on_zShift_valueChanged(int value) {
  ui->openGLWidget->setZShift(value / 1000.0);
}

void MainWindow::on_yShift_valueChanged(int value) {
  ui->openGLWidget->setYShift(value / 1000.0);
}

void MainWindow::on_yRot_valueChanged(int value) {
  ui->openGLWidget->setYRot(value / 10000.0);
}

void MainWindow::on_xAxisShiftInput_valueChanged(double arg1) {
  ui->openGLWidget->setXShift(arg1);
}

void MainWindow::on_zAxisShiftInput_valueChanged(double arg1) {
  ui->openGLWidget->setZShift(arg1);
}

void MainWindow::on_yAxisShiftInput_valueChanged(double arg1) {
  ui->openGLWidget->setYShift(arg1);
}

void MainWindow::on_yAxisRotationInput_valueChanged(double arg1) {
  ui->openGLWidget->setYRot(arg1);
}

void MainWindow::xShiftBoxChanged(double value) {
  if (value != ui->xAxisShiftInput->value())
    ui->xAxisShiftInput->setValue(value);
}

void MainWindow::yShiftBoxChanged(double value) {
  if (value != ui->yAxisShiftInput->value())
    ui->yAxisShiftInput->setValue(value);
}

void MainWindow::zShiftBoxChanged(double value) {
  if (value != ui->zAxisShiftInput->value())
    ui->zAxisShiftInput->setValue(value);
}

void MainWindow::xRotBoxChanged(double value) {
  if (value != ui->xAxisRotationInput->value())
    ui->xAxisRotationInput->setValue(value);
}

void MainWindow::yRotBoxChanged(double value) {
  if (value != ui->yAxisRotationInput->value())
    ui->yAxisRotationInput->setValue(value);
}

void MainWindow::close_file() {
  save_ptr->close();
  delete save_ptr;
  save_ptr = nullptr;
}
void MainWindow::save_image() {
  std::string file_extension;
  if (sender() == ui->save_jpeg) {
    file_extension = "Images (*.jpeg)";
  } else if (sender() == ui->save_bmp) {
    file_extension = "Images (*.bmp)";
  } else if (sender() == ui->save_giff) {
    file_extension = "GIF Images (*.gif)";
  }
  std::string title = "Save File";
  QString fileName = QFileDialog::getSaveFileName(
      this, tr(title.c_str()), "/home/Users/", tr(file_extension.c_str()));
  save_ptr = new QFile(fileName);
  if (!save_ptr->open(QIODevice::WriteOnly)) {
  } else {
    if (sender() == ui->save_giff) {
      make_gif();
    } else {
      ui->openGLWidget->grabFramebuffer().save(save_ptr);
      close_file();
    }
  }
}

void MainWindow::record_gif_file() {
  ++frame_count;
  gif->addFrame(ui->openGLWidget->grabFramebuffer(), 100);
  if (frame_count == 50) {
    timer->stop();
    ui->recording->setVisible(false);
    gif->save(save_ptr);
    close_file();
    delete gif;
    gif = nullptr;
  }
}

void MainWindow::make_gif() {
  gif = new QGifImage();
  frame_count = 0;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(record_gif_file()));
  ui->recording->setVisible(true);
  timer->start(100);
}

void MainWindow::scaleChanged(double value) {
  if (ui->scale->value() != value) ui->scale->setValue(value);
}

void MainWindow::scaleBoxChanged(double value) {
  if (ui->scaleInput->value() != value) ui->scaleInput->setValue(value);
}

void MainWindow::on_scale_valueChanged(int value) {
  ui->openGLWidget->setZNear(value / 1000.0);
}

void MainWindow::on_scaleInput_valueChanged(double arg1) {
  ui->openGLWidget->setZNear(arg1);
}
