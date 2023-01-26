#include <QApplication>
#include <QFontDatabase>

#include "controller.h"
#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  model::Model m;
  controller::Controller c(&m);
  view::View w(&c);
  int id = QFontDatabase::addApplicationFont(":/lemonmilk.otf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  QFont font(family);
  w.setFont(font);
  w.show();
  return a.exec();
}
