//--------------------------------------------------------------------------------------------------
// For explanation see header.


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include "ui_B3M_MainWindow.h"

//--------------------------------------------------------------------------------------------------
//------ MODULE IMPLEMENTATIONS                                                               ------
//--------------------------------------------------------------------------------------------------
module B3M_MainWindow;

b3m::gui::MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent), m_ui(new Ui::B3M_MainWindow)
{
	m_ui->setupUi(this);
}

b3m::gui::MainWindow::~MainWindow()
{
	delete m_ui;
}

//END OF FILE --------------------------------------------------------------------------------------