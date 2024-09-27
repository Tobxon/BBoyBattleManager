//--------------------------------------------------------------------------------------------------
/**
 * \brief Application Entry for the GUI of the B-Boy Battle Manager (B3M).
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std

//Qt
#include <QApplication>

//b3m
import b3m.database;
#include "MainWindow.hpp"


//--------------------------------------------------------------------------------------------------
//------ Main                                                                                 ------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	//database elements
	b3m::database::ParticipantsDepot allParticipants;

	//main window
	b3m::gui::MainWindow b3mMainWin(allParticipants);

	//create startup window
	b3mMainWin.show();

	const int result = app.exec();
	return result;
}


//END OF FILE --------------------------------------------------------------------------------------