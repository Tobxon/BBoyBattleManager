//--------------------------------------------------------------------------------------------------
/**
 * \brief Widget that combines all matches of a Round and other Metainformation.
 *
 */

#ifndef B3M_GUI_TOURNAMENT_TOURNAMENT_ROUND_WIDGET_HPP_
#define B3M_GUI_TOURNAMENT_TOURNAMENT_ROUND_WIDGET_HPP_


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>

//b3m
import b3m.common;

#include "ui_TournamentRoundWidget.h"


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::common::TournamentRound;


class TournamentRoundWidget : public QWidget
{
public:
	TournamentRoundWidget(TournamentRound&, QWidget* = nullptr);
	~TournamentRoundWidget();

private:
	Ui::TournamentRoundWidget* m_ui;

	TournamentRound* m_round{ nullptr };
};



}


#endif //B3M_GUI_TOURNAMENT_TOURNAMENT_ROUND_WIDGET_HPP_
//END OF FILE --------------------------------------------------------------------------------------