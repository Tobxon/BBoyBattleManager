//--------------------------------------------------------------------------------------------------
/**
 * \brief The MainWindow is the input interface to the user where most of the input happens while 
 *        other windows are used for presentation and other functionality.
 *
 */

#ifndef B3M_GUI_MAIN_WINDOW_HPP_
#define B3M_GUI_MAIN_WINDOW_HPP_


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QMainWindow>

//b3m
import b3m.database;

//GUI elements
#include "ui_MainWindow.h"
#include "ParticipantsDialog.hpp"
#include "TeamsView.hpp"
#include "TournamentManagement/Window.hpp"


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::database::ParticipantsDepot;


class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	explicit MainWindow(ParticipantsDepot&, QMainWindow* parent = nullptr);
	~MainWindow() override;
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	MainWindow(MainWindow&&) = delete;
	MainWindow& operator=(MainWindow&&) = delete;

private:
	Ui::B3M_MainWindow* m_ui{ new Ui::B3M_MainWindow };

	b3m::gui::ParticipantsDialog* m_participantDialog{ nullptr };
	b3m::gui::TeamsView* m_teamsOverview{ nullptr };
	b3m::gui::TournamentManagementWindow* m_tournamentManagementWindow{ nullptr };
};



} //namespace b3m::gui


#endif //B3M_GUI_MAIN_WINDOW_HPP_
//END OF FILE --------------------------------------------------------------------------------------