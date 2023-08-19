//--------------------------------------------------------------------------------------------------
/**
 * \brief B3M_Mainwindow is supposed to be the GUI Element that is used for the main interactions by
 *        the user.
 * So its the Window where e.g. contestants are registered, tournaments are planned and results of 
 * matches are noted.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

//Qt
#include <QMainWindow>
#include "ui_B3M_MainWindow.h"


export module B3M_MainWindow;
//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace gui
{



export class MainWindow : public QMainWindow
{

public:
	explicit MainWindow(QMainWindow* parent = nullptr);
	virtual ~MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	MainWindow(MainWindow&&) = delete;
	MainWindow& operator=(MainWindow&&) = delete;

private:
	Ui::B3M_MainWindow* m_ui;
};



} //namespace gui
} //namespace b3m


//--------------------------------------------------------------------------------------------------
//------ PRIVATE MODULE FRAGMENT                                                              ------
//--------------------------------------------------------------------------------------------------
module : private;
//implementations of the module can also be done here


//END OF FILE --------------------------------------------------------------------------------------