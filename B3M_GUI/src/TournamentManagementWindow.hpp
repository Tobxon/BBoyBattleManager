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

//Qt
#include <QWidget>

//b3m
#include <ui_TournamentManagementWindow.h>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



class TournamentManagementWindow : public QWidget
{
	Q_OBJECT;

public:
	explicit TournamentManagementWindow(QWidget* = nullptr);
	~TournamentManagementWindow() override;

private:
	Ui::TournamentManagementWindow* m_ui;
};



} //namespace b3m::gui


#endif //B3M_GUI_TOURNAMENT_MANAGEMENT_DIALOG_HPP_
//END OF FILE --------------------------------------------------------------------------------------