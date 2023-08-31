//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "MatchResultDialog.hpp"

import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::MatchResultDialog::MatchResultDialog(Match& i_match, QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::MatchResultDialog()), m_match(&i_match)
{
	m_ui->setupUi(this);

	const auto teams = m_match->getContestants();
//	const auto teamAName = QString::fromStdString(teams.at(0).getName());
	//TODO
	const auto teamAName = QString("Team1");
	const auto teamBName = QString("Team2");
	m_ui->teamA->setText(teamAName);
	m_ui->teamB->setText(teamBName);
}

b3m::gui::MatchResultDialog::~MatchResultDialog()
{
	delete m_ui;
}


//END OF FILE --------------------------------------------------------------------------------------