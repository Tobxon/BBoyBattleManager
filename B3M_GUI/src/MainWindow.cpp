//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
//module;
#include "MainWindow.hpp"

//#include "ui_MainWindow.h"

//Qt
#include <QPushButton>


//module B3M_MainWindow;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::MainWindow::MainWindow(b3m::gui::ParticipantsDialog& i_participantDialog, 
	QMainWindow* parent)
	: QMainWindow(parent), m_ui(new Ui::B3M_MainWindow), m_participantDialog(&i_participantDialog)
{
	m_ui->setupUi(this);

	connectSignalToSubWindow(m_ui->upLeftButton, m_participantDialog);
}

b3m::gui::MainWindow::~MainWindow()
{
	delete m_ui;
}

void b3m::gui::MainWindow::connectSignalToSubWindow(QPushButton* const i_btn,
	QWidget* const i_newCentralWidget)
{
	connect(i_btn, &QPushButton::clicked, m_ui->verticalLayout,
		[i_newCentralWidget, this]() { setCentralWidget(i_newCentralWidget); });
}


//END OF FILE --------------------------------------------------------------------------------------