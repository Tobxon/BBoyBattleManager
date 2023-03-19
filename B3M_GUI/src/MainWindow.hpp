//--------------------------------------------------------------------------------------------------
/**
 * \brief The MainWindow is the input interface to the user where most of the input happens while 
 *        other windows are used for presentation and other functionality.
 *
 */


#ifndef B3M_GUI__MAIN_WINDOW_HPP__
#define B3M_GUI__MAIN_WINDOW_HPP__

//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QMainWindow>

#include "ui_MainWindow.h"

#include "ParticipantsDialog.hpp"


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace gui
{



class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	explicit MainWindow(b3m::gui::ParticipantsDialog&, QMainWindow* parent = nullptr);
	virtual ~MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	MainWindow(MainWindow&&) = delete;
	MainWindow& operator=(MainWindow&&) = delete;

private:
	void connectSignalToSubWindow(QPushButton* const, QWidget* const);

	Ui::B3M_MainWindow* m_ui{ new Ui::B3M_MainWindow };
	b3m::gui::ParticipantsDialog* m_participantDialog{ new b3m::gui::ParticipantsDialog() };

	//void slot_setCentralWidget(QWidget* const);
};



} //namespace gui
} //namespace b3m


#endif //B3M_GUI__MAIN_WINDOW_HPP__
//END OF FILE --------------------------------------------------------------------------------------