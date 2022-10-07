#include "dialog.h"

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
}

Dialog::~Dialog() { delete ui; }

void Dialog::setModelName(QString modelName) {
  this->ui->modelName->setText(modelName);
}

void Dialog::on_buttonOK_clicked() { this->hide(); }

void Dialog::disableButton() { ui->buttonOK->hide(); }
