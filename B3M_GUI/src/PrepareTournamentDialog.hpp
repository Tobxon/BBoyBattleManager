//--------------------------------------------------------------------------------------------------
/**
 * \brief PrepareTournamentDialog is mainly used to get everything ready to start a tournament. This
 *        will include creating teams out of the registered participants and make sure all needed
 *        information are submitted.
 *
 */


#ifndef B3M_GUI_PREPARE_TOURNAMENT_DIALOG_HPP_
#define B3M_GUI_PREPARE_TOURNAMENT_DIALOG_HPP_

//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



class PrepareTournamentDialog : public QWidget
{
	Q_OBJECT;

public:
	explicit PrepareTournamentDialog(QWidget* = nullptr);
//	~PrepareTournamentDialog() override;

private:

};



} // gui


#endif //B3M_GUI_PREPARE_TOURNAMENT_DIALOG_HPP_
//END OF FILE --------------------------------------------------------------------------------------