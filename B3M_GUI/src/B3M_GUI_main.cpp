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

	//TEST initial data for ParticipantsDialog
	allParticipants.newParticipant("David");
	allParticipants.newParticipant("Georok", {{"city", "Vertania"}, {"favColor", "grey"}});
	allParticipants.newParticipant("Liss");
	allParticipants.updateParticipantsAttributes("Liss", "crew", "PVCrew");


	//main window
	b3m::gui::MainWindow b3mMainWin(allParticipants);
	
	////presentation window
	//QWidget showWin;

	b3mMainWin.show();
	//showWin.show();

	const int result = app.exec();
	return result;
}


//END OF FILE --------------------------------------------------------------------------------------