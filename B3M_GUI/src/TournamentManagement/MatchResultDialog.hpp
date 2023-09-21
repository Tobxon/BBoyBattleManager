//--------------------------------------------------------------------------------------------------
/**
 * \brief Widget to show a single match and enable input of the results.
 *
 */

#ifndef B3M_GUI_TOURNAMENT_MANAGEMENT_TOURNAMENT_ROUND_WIDGET_HPP_
#define B3M_GUI_TOURNAMENT_MANAGEMENT_TOURNAMENT_ROUND_WIDGET_HPP_


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>

//b3m
import b3m.common;

#include "ui_MatchResultDialog.h"


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::common::Match;
using b3m::common::Contestant;


class MatchResultDialog : public QWidget
{
	Q_OBJECT;

public:
	MatchResultDialog(Match&, const std::vector <Contestant>&, QWidget* = nullptr);
	~MatchResultDialog();

signals:
	void scoresUpdated();
	void contestantChanged();

private:
	Ui::MatchResultDialog* m_ui;

	Match* m_match;
};



}


#endif //B3M_GUI_TOURNAMENT_MANAGEMENT_TOURNAMENT_ROUND_WIDGET_HPP_
//END OF FILE --------------------------------------------------------------------------------------