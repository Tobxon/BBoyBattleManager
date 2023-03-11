//--------------------------------------------------------------------------------------------------
// \brief Application Entry for the GUI of the B-Boy Battle Manager (B3M).


//--------------------------------------------------------------------------------------------------
//------ IMPORTS / INCLUDES                                                                   ------
//--------------------------------------------------------------------------------------------------

import B3M_MainWindow;
import b3m_common;

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
	//simple testing - can be removed when functional development starts                      ------
	b3m::common::Participant testParticipant{ "Human0" };
    std::cout << "Hello Lena!";
	//                                                                                        ------
    
	QApplication app(argc, argv);

	//main window
	b3m::gui::MainWindow b3mMainWin;
	//presentation window
	QWidget showWin;

	b3mMainWin.show();
	showWin.show();

	const int result = app.exec();
	return result;
}