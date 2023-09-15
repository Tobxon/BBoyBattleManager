//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
//module;
#include "MainWindow.hpp"
//module B3M_MainWindow;

//Qt
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::MainWindow::MainWindow(ParticipantsDepot& i_participantStorage, QMainWindow* i_parent)
	: QMainWindow(i_parent), m_ui(new Ui::B3M_MainWindow)
	, m_participantDialog(new b3m::gui::ParticipantsDialog(i_participantStorage))
	, m_teamsOverview(new TeamsView(i_participantStorage))
	, m_tournamentManagementWindow(new TournamentManagementWindow())
	, m_presentationManagementWindow(new PresentationManagementWindow())
{
	m_ui->setupUi(this);

	connect(m_ui->upLeftButton, &QPushButton::clicked, [this](){
		m_participantDialog->show();
	});

	m_ui->gridLayout->addWidget(m_teamsOverview, 2, 0, 1, 1);

	connect(m_ui->lowRightButton, &QPushButton::clicked, [this](){ //TODO to QAction
		const auto teams = m_teamsOverview->getContestants();
		m_tournamentManagementWindow->startTournament(teams);
		m_tournamentManagementWindow->show();
	});

	connect(m_ui->upRightButton, &QPushButton::clicked, [this](){
		m_presentationManagementWindow->show();
	});

	connect(m_tournamentManagementWindow, &TournamentManagementWindow::newRoundStarted, m_presentationManagementWindow, &PresentationManagementWindow::addSlideFor);
}

b3m::gui::MainWindow::~MainWindow()
{
	delete m_ui;
}

void b3m::gui::MainWindow::closeEvent(QCloseEvent *event)
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Bist du sicher, dass du alles aufgeben willst?", QMessageBox::Yes | QMessageBox::No))
	{
		QApplication::closeAllWindows();
	}
	else
	{
		event->ignore();
	}
}


//END OF FILE --------------------------------------------------------------------------------------