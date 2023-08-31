//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "Window.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------
b3m::gui::TournamentManagementWindow::TournamentManagementWindow(QWidget* const i_parent)
	: QWidget(i_parent), m_ui(new Ui::TournamentManagementWindow())
{
	m_ui->setupUi(this);

	connect(m_ui->lowRightButton, &QPushButton::clicked, this, &QWidget::hide);

	connect(m_ui->upLeftButton, &QPushButton::clicked, [this](){
		auto round = m_tournament.startRound();
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