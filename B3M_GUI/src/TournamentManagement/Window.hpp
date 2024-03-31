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
import <optional>;

//Qt
#include <QWidget>

#include <ui_TournamentManagementWindow.h>

//b3m
import b3m.common;
import b3m.database;

namespace b3m::gui{ class TournamentRoundWidget; } //I#5 to boost::signals - signal results changed from Match itself


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::database::TournamentProxy;
using b3m::common::Contestant;
using b3m::common::TournamentRound;
using b3m::common::ContestantsRanking;


class TournamentManagementWindow : public QWidget
{
	Q_OBJECT;

public:
	explicit TournamentManagementWindow(QWidget* = nullptr);
	~TournamentManagementWindow() override;

	bool startTournament(const std::vector< Contestant >&);

signals:
	void newRoundStarted(TournamentRound&, TournamentRoundWidget&); //I#5 to boost::signals - signal results changed from Match itself
	void roundScoresUpdated(); //I#5 to boost::signals - signal results changed from Match itself
	void rankingUpdated(const ContestantsRanking&);

private:
	Ui::TournamentManagementWindow* m_ui;

	TournamentProxy m_tournament;

	std::optional< QMetaObject::Connection > m_roundFinished{ std::nullopt };
};



} //namespace b3m::gui


#endif //B3M_GUI_TOURNAMENT_MANAGEMENT_DIALOG_HPP_
//END OF FILE --------------------------------------------------------------------------------------