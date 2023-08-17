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

#include "ui_MainWindow.h"

#include "ParticipantsDialog.hpp"

//b3m
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	explicit MainWindow(b3m::database::ParticipantsDepot&, QMainWindow* parent = nullptr);
	~MainWindow() override;
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	MainWindow(MainWindow&&) = delete;
	MainWindow& operator=(MainWindow&&) = delete;

private:
	void connectSignalToSubWindow(QPushButton*, QWidget*);

	Ui::B3M_MainWindow* m_ui{ new Ui::B3M_MainWindow };
	b3m::gui::ParticipantsDialog* m_participantDialog{ nullptr };

	//void slot_setCentralWidget(QWidget* const);
};



} //namespace b3m::gui


#endif //B3M_GUI_MAIN_WINDOW_HPP_
//END OF FILE --------------------------------------------------------------------------------------