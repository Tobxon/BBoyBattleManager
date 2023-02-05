//--------------------------------------------------------------------------------------------------
// \brief Application Entry for the GUI of the B-Boy Battle Manager (B3M).


//--------------------------------------------------------------------------------------------------
//------ IMPORTS / INCLUDES                                                                   ------
//--------------------------------------------------------------------------------------------------

import B3M_MainWindow;

//std
#include <iostream>


//Qt
#include <QApplication>
#include <QMainWindow>

//#include "B3M_MainWindow.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementation                                                                       ------
//--------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    std::cout << "Hello Lena!";
    
	QApplication app(argc, argv);

	//main window
	b3m::gui::MainWindow b3mMainWin;
	//presentation window
	QWidget showWin;

	//mainWin.initUI();
	b3mMainWin.show();
	showWin.show();

	const int result = app.exec();
	return result;
}