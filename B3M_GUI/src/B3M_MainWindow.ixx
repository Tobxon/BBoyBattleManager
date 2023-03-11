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

//Qt custom
#include "ui_B3M_MainWindow.h"


//--------------------------------------------------------------------------------------------------
//------ MODULE DECLARATIONS                                                                  ------
//--------------------------------------------------------------------------------------------------
export module B3M_MainWindow;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m
{
namespace gui
{



class MainWindow : public QMainWindow
{

public:
	MainWindow(QMainWindow* parent = nullptr);
	virtual ~MainWindow();
	//TODO rule of 5

protected:

private:
	Ui::B3M_MainWindow* m_ui;
};



} //namespace gui
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------