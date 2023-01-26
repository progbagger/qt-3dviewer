#include "incorrect_file_dialog_window.h"

#include "ui_incorrect_file_dialog_window.h"

namespace view {

IncorrectFileDialogWindow::IncorrectFileDialogWindow(QWidget *parent)
    : QDialog(parent), ui_(new Ui::IncorrectFileDialogWindow) {
  ui_->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint, true);
}

IncorrectFileDialogWindow::~IncorrectFileDialogWindow() { delete ui_; }

void IncorrectFileDialogWindow::on_ok_button_clicked() { hide(); }

}  // namespace view
