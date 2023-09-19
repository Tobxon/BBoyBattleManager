//--------------------------------------------------------------------------------------------------
/**
 * \brief Application Entry for the GUI of the B-Boy Battle Manager (B3M).
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <string>;
import <map>;

//Qt
#include <QApplication>

//b3m
import b3m.common;
import b3m.database;
#include "MainWindow.hpp"


using b3m::common::ParticipantAttributes;
using b3m::common::Attribute;


//--------------------------------------------------------------------------------------------------
//------ Main                                                                                 ------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	//Test1
	std::map< b3m::common::Participant::Name_t, b3m::common::ParticipantAttributes > test1Participants{
		{{ "guy" }, {{ b3m::common::teamAttribute, "Gingerbreads Crew" }, { b3m::common::ratingAttribute, "9" }}},
		{{ "human" }, {{ b3m::common::teamAttribute, "Style Insiders" }, { b3m::common::ratingAttribute, "8" }}},
		{{ "chick" }, {{ b3m::common::teamAttribute, "Nasty Attack" }, { b3m::common::ratingAttribute, "7" }}},
		{{ "dude" }, {{ b3m::common::teamAttribute, "Offbeat" }, { b3m::common::ratingAttribute, "6" }}},
		{{ "expert" }, {{ b3m::common::teamAttribute, "Dream ASF" }, { b3m::common::ratingAttribute, "4" }}},
		{{ "pro" }, {{ b3m::common::teamAttribute, "Crazy Monkeys" }, { b3m::common::ratingAttribute, "3" }}},
		{{ "clown" }, {{ b3m::common::teamAttribute, "Fresh Family" }, { b3m::common::ratingAttribute, "2" }}},
		{{ "queer" }, {{ b3m::common::teamAttribute, "Speed Breaker" }, { b3m::common::ratingAttribute, "1" }}},
		{{ "incognito" }, {{ b3m::common::teamAttribute, "Anonymous Crew" }, { b3m::common::ratingAttribute, "5" }}}
	};

	//database elements
	b3m::database::ParticipantsDepot testParticipants{
			test1Participants
	};

	//main window
	auto b3mMainWin = new b3m::gui::MainWindow(testParticipants);

	//create startup window
	b3mMainWin->show();

	const int result = app.exec();
	return result;
}


//END OF FILE --------------------------------------------------------------------------------------