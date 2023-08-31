//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
//module;
#include "MainWindow.hpp"

//Qt
#include <QPushButton>


//module B3M_MainWindow;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::MainWindow::MainWindow(ParticipantsDepot& i_participantStorage, QMainWindow* i_parent)
	: QMainWindow(i_parent), m_ui(new Ui::B3M_MainWindow)
	, m_participantDialog(new b3m::gui::ParticipantsDialog(i_participantStorage))
	, m_teamsOverview(new TeamsView(i_participantStorage))
	, m_tournamentManagementWindow(new TournamentManagementWindow())
{
	m_ui->setupUi(this);

	connect(m_ui->upLeftButton, &QPushButton::clicked, [this](){
		m_participantDialog->show();
	});

	m_ui->gridLayout->addWidget(m_teamsOverview, 2, 0, 1, 1);

	connect(m_ui->lowRightButton, &QPushButton::clicked, [this](){
		const auto teams = m_teamsOverview->getContestants();
		m_tournamentManagementWindow->startTournament(teams);
		m_tournamentManagementWindow->show();
	});
}

b3m::gui::MainWindow::~MainWindow()
{
	delete m_ui;
}


//END OF FILE --------------------------------------------------------------------------------------