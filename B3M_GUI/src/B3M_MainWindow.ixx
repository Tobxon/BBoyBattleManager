//--------------------------------------------------------------------------------------------------
/**
 * @brief B3M_Mainwindow is supposed to be the GUI Elment that is used for the main interactions by 
 *        the user.
 *
 */

//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include <QMainWindow>
#include "ui_B3M_MainWindow.h"

//--------------------------------------------------------------------------------------------------
//------ MODULE PURVIEW                                                                       ------
//--------------------------------------------------------------------------------------------------
export module B3M_MainWindow;

export class B3M_MainWindow : public QMainWindow
{

public:
	B3M_MainWindow(QMainWindow* parent = nullptr)
		: QMainWindow(parent), m_ui(new Ui::B3M_MainWindow)
	{
		m_ui->setupUi(this);
	};
	virtual ~B3M_MainWindow() { delete m_ui; };
	//TODO rule of 5

protected:

private:
	Ui::B3M_MainWindow* m_ui;
};

//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module : private;