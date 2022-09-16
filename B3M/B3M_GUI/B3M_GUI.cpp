#include "B3M_GUI.h"

#include <sst_functions.h>

B3M_GUI::B3M_GUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void B3M_GUI::on_closeButton_clicked()
{
    close();
}
