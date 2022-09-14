#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_B3M_GUI.h"

class B3M_GUI : public QMainWindow
{
    Q_OBJECT

public:
    B3M_GUI(QWidget *parent = nullptr);

private slots:
    void on_closeButton_clicked();

private:
    Ui::B3M_GUIClass ui;
};
