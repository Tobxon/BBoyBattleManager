//--------------------------------------------------------------------------------------------------
/**
 * \brief Application Entry for the GUI of the B-Boy Battle Manager (B3M).
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.database;

//std
#include <iostream>

//Qt
#include <QApplication>
#include <QWidget>

//B3M GUI
#include "MainWindow.hpp"
#include "ParticipantsDialog.hpp"


//--------------------------------------------------------------------------------------------------
//------ Main                                                                                 ------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{    
	QApplication app(argc, argv);

    //database elements
    b3m::database::ParticipantsDepot allParticipants;

	//main window
	b3m::gui::ParticipantsDialog* participantsDialog{ new b3m::gui::ParticipantsDialog() };
	b3m::gui::MainWindow b3mMainWin(*participantsDialog);
	
	////presentation window
	//QWidget showWin;

	b3mMainWin.show();
	//showWin.show();

	const int result = app.exec();
	return result;
}


//END OF FILE --------------------------------------------------------------------------------------