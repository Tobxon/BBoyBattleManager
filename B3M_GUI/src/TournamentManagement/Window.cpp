//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "Window.hpp"

//b3m
#include "TournamentRoundWidget.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------
b3m::gui::TournamentManagementWindow::TournamentManagementWindow(QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::TournamentManagementWindow())
{
	m_ui->setupUi(this);

	connect(m_ui->lowRightButton, &QPushButton::clicked, this, &QWidget::hide);

	connect(this, &TournamentManagementWindow::newRoundStarted, [this](){ return m_ui->upLeftButton->setEnabled(false);});
	connect(m_ui->upLeftButton, &QPushButton::clicked, [this](){ //TODO to QAction

		if(m_roundFinished)
		{
			disconnect(m_roundFinished.value());
		}

		auto round = m_tournament.startRound();
		//TODO get round index
		static int roundIndex = 0;

		auto roundWidget = new TournamentRoundWidget(*round);
		m_ui->roundTabs->addTab(roundWidget, QString("Round ") + QString::number(++roundIndex));
		emit newRoundStarted();

		m_roundFinished = connect(roundWidget, &TournamentRoundWidget::roundFinished, [this](){ return m_ui->upLeftButton->setEnabled(true); });
	});
}

b3m::gui::TournamentManagementWindow::~TournamentManagementWindow()
{
	delete m_ui;
}

bool b3m::gui::TournamentManagementWindow::startTournament(const std::vector< Contestant >& i_contestants)
{
	return m_tournament.startTournament(i_contestants);
}


//END OF FILE --------------------------------------------------------------------------------------