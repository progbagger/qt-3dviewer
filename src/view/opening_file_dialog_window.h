#ifndef OPENING_FILE_DIALOG_WINDOW_H
#define OPENING_FILE_DIALOG_WINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class OpeningFileDialogWindow;
}

namespace view {

class OpeningFileDialogWindow : public QDialog {
  Q_OBJECT

 public:
  explicit OpeningFileDialogWindow(QWidget *parent = nullptr);
  ~OpeningFileDialogWindow();

  void SetProgressBarValue(int value);

 private:
  Ui::OpeningFileDialogWindow *ui_;
};

}  // namespace view

#endif  // OPENING_FILE_DIALOG_WINDOW_H
