//--------------------------------------------------------------------------------------------------
// Application Entry for the GUI of the B-Boy Battle Manager.

//--------------------------------------------------------------------------------------------------
//------ Includes                                                                             ------
//--------------------------------------------------------------------------------------------------

//std
#include <iostream>

//Qt
#include <QApplication>
#include <QMainWindow>

//--------------------------------------------------------------------------------------------------
//------ Implementation                                                                       ------
//--------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    std::cout << "Hello Lena!";
    
	QApplication app(argc, argv);

	//WavedromViewerMainWindow* mainWin = new WavedromViewerMainWindow();
	QMainWindow mainWin;
	QWidget showWin;

	//mainWin.initUI();
	mainWin.show();
	showWin.show();

	const int result = app.exec();
	return result;
}