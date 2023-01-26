#ifndef INCORRECT_FILE_DIALOG_WINDOW_H
#define INCORRECT_FILE_DIALOG_WINDOW_H

#include <QDialog>

namespace Ui {
class IncorrectFileDialogWindow;
}

namespace view {

class IncorrectFileDialogWindow : public QDialog {
  Q_OBJECT

 public:
  explicit IncorrectFileDialogWindow(QWidget *parent = nullptr);
  ~IncorrectFileDialogWindow();

 private slots:
  void on_ok_button_clicked();

 private:
  Ui::IncorrectFileDialogWindow *ui_;
};

}  // namespace view

#endif  // INCORRECT_FILE_DIALOG_WINDOW_H
