//--------------------------------------------------------------------------------------------------
/**
 * \brief Application Entry for the GUI of the B-Boy Battle Manager (B3M).
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.common;
import B3M_MainWindow;

//std
#include <iostream>

//Qt
#include <QApplication>
#include <QMainWindow>

//Qt custom
#include "ui_B3M_ParticipantsDialog.h"

//#include "B3M_MainWindow.hpp"


//--------------------------------------------------------------------------------------------------
//------ Main                                                                                 ------
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
	auto* const partiDialog = new Ui::ParticipantsDialog();
	partiDialog->setupUi(&showWin);

	b3mMainWin.show();
	showWin.show();

	const int result = app.exec();
	return result;
}


//END OF FILE --------------------------------------------------------------------------------------