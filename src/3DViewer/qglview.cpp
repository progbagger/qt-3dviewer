#include "qglview.h"

QglView::QglView(QWidget *parent) : QOpenGLWidget(parent) {
  currentModel = NULL;
  currentVertexes = NULL;
  zNear = 1;
  isPreviousModelLoaded = false;
  resetSettings();
  update();
}

bool QglView::isModelExist() {
  bool result = false;
  if (currentModel) result = true;
  return result;
}

void QglView::emitSignals() {
  if (currentModel) {
    emit changeXRotSlider(yRot * 10000.0);
    emit changeYRotSlider(xRot * 10000.0);
    emit changeXShiftSlider(xShift * 1000.0);
    emit changeYShiftSlider(yShift * 1000.0);
    emit changeZShiftSlider(zShift * 1000.0);
    emit changeScaleSlider(zNear * 1000.0);

    emit changeXShiftBox(xShift);
    emit changeYShiftBox(yShift);
    emit changeZShiftBox(zShift);
    emit changeXRotBox(yRot);
    emit changeYRotBox(xRot);
    emit changeScaleBox(zNear);
  }
}

void QglView::resetSettings() {
  resetView();
  isModelClosed = true;
  pointsStyle = 1;
  projectionType = 0;
  vertexesStyle = 0;
  lineStyle = 0;
  pointsSize = 15;
  lineWidth = 6;
  rLineColor = gLineColor = bLineColor = 127;
  rPointColor = bPointColor = 0;
  gPointColor = 127;
  rBgColor = gBgColor = bBgColor = 0;
  update();
}

double QglView::getMinZ() {
  double result = NAN;
  if (currentModel)
    result = -fabs((currentModel->zMax - currentModel->zMin) *
                   AXES_SCALING_MULTIPLIER) -
             1.0;
  return result;
}

double QglView::getMaxZ() {
  double result = NAN;
  if (currentModel)
    result = fabs((currentModel->zMax - currentModel->zMin) *
                  AXES_SCALING_MULTIPLIER) +
             1.0;
  return result;
}

double QglView::getZNear() { return zNear; }

void QglView::setZNear(double value) {
  zNear = value;
  if (zNear < MIN_SCALE)
    zNear = MIN_SCALE;
  else if (zNear > MAX_SCALE)
    zNear = MAX_SCALE;
  if (currentModel) update();
  emit changeScaleSlider(zNear * 1000.0);
  emit changeScaleBox(zNear);
}

double QglView::getZShift() { return zShift; }

void QglView::setZShift(double value) {
  zShift = value;
  if (zShift < getMinZ())
    zShift = getMinZ();
  else if (zShift > getMaxZ())
    zShift = getMaxZ();
  if (currentModel) update();
  emit changeZShiftSlider(zShift * 1000.0);
  emit changeZShiftBox(zShift);
}

double QglView::getMinY() {
  double result = NAN;
  if (currentModel)
    result = -fabs((currentModel->yMax - currentModel->yMin) *
                   AXES_SCALING_MULTIPLIER) -
             1.0;
  return result;
}

double QglView::getMaxY() {
  double result = NAN;
  if (currentModel)
    result = fabs((currentModel->yMax - currentModel->yMin) *
                  AXES_SCALING_MULTIPLIER) +
             1.0;
  return result;
}

double QglView::getXShift() { return xShift; }

void QglView::setXShift(double value) {
  xShift = value;
  if (xShift < getMinX())
    xShift = getMinX();
  else if (xShift > getMaxX())
    xShift = getMaxX();
  if (currentModel) update();
  emit changeXShiftSlider(xShift * 1000.0);
  emit changeXShiftBox(xShift);
}

double QglView::getMinX() {
  double result = NAN;
  if (currentModel)
    result = -fabs((currentModel->xMax - currentModel->xMin) *
                   AXES_SCALING_MULTIPLIER) -
             1.0;
  return result;
}

double QglView::getMaxX() {
  double result = NAN;
  if (currentModel)
    result = fabs((currentModel->xMax - currentModel->xMin) *
                  AXES_SCALING_MULTIPLIER) +
             1.0;
  return result;
}

double QglView::getYShift() { return yShift; }

void QglView::setYShift(double value) {
  yShift = value;
  if (yShift < getMinY())
    yShift = getMinY();
  else if (yShift > getMaxY())
    yShift = getMaxY();
  if (currentModel) update();
  emit changeYShiftSlider(yShift * 1000.0);
  emit changeYShiftBox(yShift);
}

void QglView::resetView() {
  xRot = yRot = zRot = 0;
  zNear = 1;
  xShift = yShift = 0;
  zShift = getMinZ();
  emitSignals();
  if (currentModel) update();
}

void QglView::saveSettings() {
  QFile file(QDir::home().absolutePath() + "/3DViewer_settings.conf");
  file.open(QFile::WriteOnly);
  file.write(("modelPath=" + modelPath + "\n").toStdString().data());
  file.write(("xShift=" + QString::number(xShift) + "\n").toStdString().data());
  file.write(("yShift=" + QString::number(yShift) + "\n").toStdString().data());
  file.write(("zShift=" + QString::number(zShift) + "\n").toStdString().data());
  file.write(("zNear=" + QString::number(zNear) + "\n").toStdString().data());
  file.write(("xRot=" + QString::number(xRot) + "\n").toStdString().data());
  file.write(("yRot=" + QString::number(yRot) + "\n").toStdString().data());
  file.write(("zRot=" + QString::number(zRot) + "\n").toStdString().data());
  file.write(("mPos=" + QString::number(mPos.x()) + ", " +
              QString::number(mPos.y()) + "\n")
                 .toStdString()
                 .data());
  file.write(("pointsStyle=" + QString::number(pointsStyle) + "\n")
                 .toStdString()
                 .data());
  file.write(
      ("lineStyle=" + QString::number(lineStyle) + "\n").toStdString().data());
  file.write(("projectionType=" + QString::number(projectionType) + "\n")
                 .toStdString()
                 .data());
  file.write(("vertexesStyle=" + QString::number(vertexesStyle) + "\n")
                 .toStdString()
                 .data());
  file.write(("pointsSize=" + QString::number(pointsSize) + "\n")
                 .toStdString()
                 .data());
  file.write(
      ("lineWidth=" + QString::number(lineWidth) + "\n").toStdString().data());
  file.write(("rLineColor=" + QString::number(rLineColor) + "\n")
                 .toStdString()
                 .data());
  file.write(("gLineColor=" + QString::number(gLineColor) + "\n")
                 .toStdString()
                 .data());
  file.write(("bLineColor=" + QString::number(bLineColor) + "\n")
                 .toStdString()
                 .data());
  file.write(("rPointColor=" + QString::number(rPointColor) + "\n")
                 .toStdString()
                 .data());
  file.write(("gPointColor=" + QString::number(gPointColor) + "\n")
                 .toStdString()
                 .data());
  file.write(("bPointColor=" + QString::number(bPointColor) + "\n")
                 .toStdString()
                 .data());
  file.write(
      ("rBgColor=" + QString::number(rBgColor) + "\n").toStdString().data());
  file.write(
      ("gBgColor=" + QString::number(gBgColor) + "\n").toStdString().data());
  file.write(
      ("bBgColor=" + QString::number(bBgColor) + "\n").toStdString().data());
  file.close();
}

void QglView::loadSettings() {
  QFile file(QDir::home().absolutePath() + QDir::separator() +
             "3DViewer_settings.conf");
  if (file.exists()) {
    file.open(QFile::ReadOnly);
    while (!file.atEnd()) {
      QString line(file.readLine());
      line.chop(1);
      QStringList splitted = line.split("=");
      if (splitted.length() >= 2) {
        // ...
        if (line.contains("modelPath")) {
          modelPath = splitted[1];
        } else if (line.contains("xShift")) {
          xShift = splitted[1].toDouble();
        } else if (line.contains("yShift")) {
          yShift = splitted[1].toDouble();
        } else if (line.contains("zShift")) {
          zShift = splitted[1].toDouble();
        } else if (line.contains("zNear")) {
          zNear = splitted[1].toDouble();
        } else if (line.contains("xRot")) {
          xRot = splitted[1].toDouble();
        } else if (line.contains("yRot")) {
          yRot = splitted[1].toDouble();
        } else if (line.contains("zRot")) {
          zRot = splitted[1].toDouble();
        } else if (line.contains("mPos")) {
          splitted = splitted[1].split(", ");
          if (splitted.length() >= 3) {
            mPos.setX(splitted[0].toDouble());
            mPos.setY(splitted[1].toDouble());
          }
        } else if (line.contains("pointsStyle")) {
          pointsStyle = splitted[1].toDouble();
        } else if (line.contains("lineStyle")) {
          lineStyle = splitted[1].toDouble();
        } else if (line.contains("projectionType")) {
          projectionType = splitted[1].toDouble();
        } else if (line.contains("vertexesStyle")) {
          vertexesStyle = splitted[1].toDouble();
        } else if (line.contains("pointsSize")) {
          pointsSize = splitted[1].toDouble();
        } else if (line.contains("lineWidth")) {
          lineWidth = splitted[1].toDouble();
        } else if (line.contains("rLineColor")) {
          rLineColor = splitted[1].toDouble();
        } else if (line.contains("gLineColor")) {
          gLineColor = splitted[1].toDouble();
        } else if (line.contains("bLineColor")) {
          bLineColor = splitted[1].toDouble();
        } else if (line.contains("rPointColor")) {
          rPointColor = splitted[1].toDouble();
        } else if (line.contains("gPointColor")) {
          gPointColor = splitted[1].toDouble();
        } else if (line.contains("rBgColor")) {
          rBgColor = splitted[1].toDouble();
        } else if (line.contains("gBgColor")) {
          gBgColor = splitted[1].toDouble();
        } else if (line.contains("bBgColor")) {
          bBgColor = splitted[1].toDouble();
        } else if (line.contains("bPointColor")) {
          bPointColor = splitted[1].toDouble();
        }
      }
    }
    if (!modelPath.isEmpty()) {
      isPreviousModelLoaded = true;
      emit setSavedModel(modelPath);
    } else {
      resetSettings();
    }
    file.close();
  }
}

void QglView::cleanModel() {
  modelPath = "";
  clean_obj(currentModel);
  if (currentVertexes) free(currentVertexes);
  currentVertexes = NULL;
  resetSettings();
  currentModel = NULL;
  update();
}

QglView::~QglView() {
  clean_obj(currentModel);
  if (currentVertexes) free(currentVertexes);
  saveSettings();
};

void QglView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void QglView::resizeGL(int w, int h) {
  if (!currentModel) loadSettings();
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -(double(this->height()) / double(this->width())),
          double(this->height()) / double(this->width()),
          tan(10.0 * M_PI / 180.0 / 2), 999999999999);
}

void QglView::paintGL() {
  // clearing and setting background color
  glClear(GL_COLOR_CLEAR_VALUE | GL_DEPTH_BUFFER_BIT);
  glClearColor((float)rBgColor / 255.0, (float)gBgColor / 255.0,
               (float)bBgColor / 255.0, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  double l = -(double(this->width()) / double(this->height())),
         r = double(this->width()) / double(this->height());

  // setting projection type
  if (!projectionType)
    glFrustum(l, r, l, r, POV, 999999999999);
  else
    glOrtho(l, r, l, r, POV, 999999999999);

  // doing affine transformations on model
  if (currentModel) {
    if (!projectionType) {
      translate_model(currentModel, currentVertexes, xShift, yShift, zShift,
                      zNear, zNear, zNear, yRot, xRot);
    } else {
      double scaleDependedOnZShift =
          (MAX_SCALE - MIN_SCALE) / 2.0 * -zShift / getMinZ() +
          (MIN_SCALE + MAX_SCALE) / 2.0;
      translate_model(currentModel, currentVertexes, xShift, yShift, zShift,
                      scaleDependedOnZShift * zNear * 0.1,
                      scaleDependedOnZShift * zNear * 0.1,
                      scaleDependedOnZShift * zNear * 0.1, yRot, xRot);
    }
    drawModel();
  } else if (isModelClosed) {
    update();
    isModelClosed = false;
  }
}

void QglView::drawModel() {
  // updating closed model so it dissapears
  if (isModelClosed) {
    update();
    isModelClosed = false;
  }

  glVertexPointer(3, GL_DOUBLE, 0, currentVertexes);
  glEnableClientState(GL_VERTEX_ARRAY);

  // handling line style
  if (!lineStyle) {
    glEnable(GL_LINE_SMOOTH);
  } else {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(6, 0x3333);
  }

  // handling points style
  if (pointsStyle) {
    glEnable(GL_POINTS);
    if (pointsStyle == 1)
      glEnable(GL_POINT_SMOOTH);
    else if (pointsStyle == 2)
      glEnable(GL_POINT_BIT);
  }

  // different parameters for lines, points and background styles
  glLineWidth(lineWidth);
  glPointSize(pointsSize);
  glColor3b(rLineColor, gLineColor, bLineColor);

  // drawing everything
  glDrawElements(GL_LINES, currentModel->faces_count, GL_UNSIGNED_INT,
                 currentModel->faces);
  if (pointsStyle) {
    glColor3b(rPointColor, gPointColor, bPointColor);
    glDrawArrays(GL_POINTS, 0, currentModel->vertexes_count / 3);
  }

  // disabling points
  if (pointsStyle) {
    if (pointsStyle == 1)
      glDisable(GL_POINT_SMOOTH);
    else if (pointsStyle == 2)
      glDisable(GL_POINT_BIT);
    glDisable(GL_POINTS);
  }

  // disabling lines
  if (!lineStyle)
    glDisable(GL_LINE_SMOOTH);
  else
    glDisable(GL_LINE_STIPPLE);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void QglView::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void QglView::mouseMoveEvent(QMouseEvent *mo) {
  // setting rotation angle on axis X
  xRot += 0.5 / M_PI * (mo->pos().y() - mPos.y());
  if (xRot > 180.0)
    xRot -= 360.0;
  else if (xRot < -180.0)
    xRot += 360.0;

  // setting rotation angle on axis Y
  yRot += 0.5 / M_PI * (mo->pos().x() - mPos.x());
  yRot = fmod(yRot, 360.0);
  if (yRot < 0) yRot += 360.0;

  // updating previous mouse location
  mPos = mo->pos();
  if (currentModel) update();
}

void QglView::mouseReleaseEvent(QMouseEvent *mo) { emitSignals(); }

void QglView::keyPressEvent(QKeyEvent *ke) {
  if (currentModel) {
    QString t = ke->text();
    if (t.contains('w') || t.contains("ц"))
      setZShift(zShift + getMaxZ() / MOVING_MULTIPLIER);
    if (t.contains('W') || t.contains("Ц"))
      setZShift(zShift +
                getMaxZ() / MOVING_MULTIPLIER * SHIFT_MOVING_MULTIPLIER);
    if (t.contains('s') || t.contains("ы"))
      setZShift(zShift - getMaxZ() / MOVING_MULTIPLIER);
    if (t.contains('S') || t.contains("Ы"))
      setZShift(zShift -
                getMaxZ() / MOVING_MULTIPLIER * SHIFT_MOVING_MULTIPLIER);
    if (t.contains('a') || t.contains("ф"))
      setXShift(xShift - getMaxX() / MOVING_MULTIPLIER);
    if (t.contains('A') || t.contains("Ф"))
      setXShift(xShift -
                getMaxX() / MOVING_MULTIPLIER * SHIFT_MOVING_MULTIPLIER);
    if (t.contains('d') || t.contains("в"))
      setXShift(xShift + getMaxX() / MOVING_MULTIPLIER);
    if (t.contains('D') || t.contains("В"))
      setXShift(xShift +
                getMaxX() / MOVING_MULTIPLIER * SHIFT_MOVING_MULTIPLIER);
    if (t.contains('r') || t.contains("к"))
      setYShift(yShift + getMaxY() / MOVING_MULTIPLIER);
    if (t.contains('R') || t.contains("К"))
      setYShift(yShift +
                getMaxY() / MOVING_MULTIPLIER * SHIFT_MOVING_MULTIPLIER);
    if (t.contains('f') || t.contains("а"))
      setYShift(yShift - getMaxY() / MOVING_MULTIPLIER);
    if (t.contains('F') || t.contains("А"))
      setYShift(yShift -
                getMaxY() / MOVING_MULTIPLIER * SHIFT_MOVING_MULTIPLIER);
    update();
    emitSignals();
  }
}

void QglView::wheelEvent(QWheelEvent *wh) {
  if (currentModel) {
    setZNear(zNear + fabs(zNear) * wh->angleDelta().y() / 1000.0);
    update();
    emitSignals();
  }
}

bool QglView::setModel(const QString &filePath) {
  bool result = false;
  Obj *new_obj = parse_obj(filePath.toStdString().data());
  if (new_obj) {
    if (!isPreviousModelLoaded) cleanModel();
    result = true;
    Obj *tmp = currentModel;
    currentModel = new_obj;
    free(tmp);
    if (!isPreviousModelLoaded)
      resetView();
    else
      isPreviousModelLoaded = false;
    if (!currentVertexes)
      currentVertexes =
          (double *)calloc(currentModel->vertexes_count, sizeof(double));
    update();
    emitSignals();
  }
  return result;
}

size_t QglView::getVertexCount() {
  size_t result = 0;
  if (currentModel) result = currentModel->vertexes_count / 3;
  return result;
}
size_t QglView::getFacesCount() {
  size_t result = 0;
  if (currentModel) result = currentModel->f_count;
  return result;
}

void QglView::setXRot(double value) {
  yRot = value;
  update();
  emit changeXRotSlider(yRot * 10000.0);
  emit changeXRotBox(yRot);
}

void QglView::setYRot(double value) {
  xRot = value;
  update();
  emit changeYRotSlider(xRot * 10000.0);
  emit changeYRotBox(xRot);
}

double QglView::getXRot() { return xRot; }

double QglView::getYRot() { return yRot; }
