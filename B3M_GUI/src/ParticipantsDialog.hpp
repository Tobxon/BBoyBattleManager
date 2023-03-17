//--------------------------------------------------------------------------------------------------
/**
 * \brief ParticipantsDialog is used to input participant which further can be registered to 
 *        tournaments and be challengers in battles.
 *
 */


#ifndef B3M_GUI__PARTICIPANTS_DIGALOG_HPP__
#define B3M_GUI__PARTICIPANTS_DIGALOG_HPP__

//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>

#include <ui_ParticipantsDialog.h>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace gui
{



class ParticipantsDialog : public QWidget
{
	Q_OBJECT;

public:
	explicit ParticipantsDialog(QWidget* const = nullptr);
	~ParticipantsDialog();

private:
	Ui::ParticipantsDialog* m_ui;
};



} //gui
} //b3m


#endif //B3M_GUI__PARTICIPANTS_DIGALOG_HPP__
 //END OF FILE --------------------------------------------------------------------------------------