//--------------------------------------------------------------------------------------------------
/**
 * \brief Dialog for the user that is directly using the pc to document results of battles and lead
 *        through the Tournament.
 *
 */

#ifndef B3M_GUI_TOURNAMENT_MANAGEMENT_DIALOG_HPP_
#define B3M_GUI_TOURNAMENT_MANAGEMENT_DIALOG_HPP_


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <vector>;

//Qt
#include <QWidget>

#include <ui_TournamentManagementWindow.h>

//b3m
import b3m.common;
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::database::TournamentProxy;
using b3m::common::Contestant;


class TournamentManagementWindow : public QWidget
{
	Q_OBJECT;

public:
	explicit TournamentManagementWindow(QWidget* = nullptr);
	~TournamentManagementWindow() override;

	bool startTournament(const std::vector< Contestant >&);
private:
	Ui::TournamentManagementWindow* m_ui;

	TournamentProxy m_tournament;
};



} //namespace b3m::gui


#endif //B3M_GUI_TOURNAMENT_MANAGEMENT_DIALOG_HPP_
//END OF FILE --------------------------------------------------------------------------------------