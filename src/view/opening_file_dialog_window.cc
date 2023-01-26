#include "opening_file_dialog_window.h"

#include "ui_opening_file_dialog_window.h"

namespace view {

OpeningFileDialogWindow::OpeningFileDialogWindow(QWidget* parent)
    : QDialog(parent), ui_(new Ui::OpeningFileDialogWindow) {
  ui_->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint, true);
}

OpeningFileDialogWindow::~OpeningFileDialogWindow() { delete ui_; }

void OpeningFileDialogWindow::SetProgressBarValue(int value) {
  ui_->progress_bar->setValue(value);
}

}  // namespace view
