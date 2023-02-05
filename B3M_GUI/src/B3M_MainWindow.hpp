//--------------------------------------------------------------------------------------------------
/**
 * @brief B3M_Mainwindow is supposed to be the GUI Elment that is used for the main interactions by 
 *        the user.
 *
 */

//--------------------------------------------------------------------------------------------------
//------ INCLUDES                                                                             ------
//--------------------------------------------------------------------------------------------------

//std
#include <memory>

//Qt
#include <QMainWindow>

namespace Ui
{
	class B3M_MainWindow;
}

//--------------------------------------------------------------------------------------------------
//------ DECLARATIONS                                                                         ------
//--------------------------------------------------------------------------------------------------

class B3M_MainWindow : public QMainWindow
{

public:
	B3M_MainWindow(QMainWindow* parent = nullptr);
	virtual ~B3M_MainWindow();
	//TODO rule of 5

protected:

private:
	Ui::B3M_MainWindow* m_ui;
};