#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();
  void setModelName(QString);
  void disableButton();

 private slots:
  void on_buttonOK_clicked();

 private:
  Ui::Dialog *ui;
};

#endif  // DIALOG_H
