//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "TournamentRoundWidget.hpp"

#include "MatchResultDialog.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::TournamentRoundWidget::TournamentRoundWidget(TournamentRound& i_round, QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::TournamentRoundWidget()), m_round(&i_round)
{
	m_ui->setupUi(this);

	for(auto& match : m_round->getMatches())
	{
		auto matchDialog = new MatchResultDialog(match, i_round.getTournament().getContestants());
		m_ui->matchesLayout->addWidget(matchDialog);
		connect(matchDialog, &MatchResultDialog::scoresUpdated, [this](){ if(isFinished()) emit roundFinished();}); //I#5 to boost::signals - signal results changed from Match itself
	}
}

b3m::gui::TournamentRoundWidget::~TournamentRoundWidget()
{
	delete m_ui;
}

bool b3m::gui::TournamentRoundWidget::isFinished()
{
	if(!m_round)
	{
		return false;
	}

	return m_round->isFinished();
}


//END OF FILE --------------------------------------------------------------------------------------