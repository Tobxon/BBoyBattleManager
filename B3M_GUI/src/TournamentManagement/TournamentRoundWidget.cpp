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

	for(auto& match : *m_round)
	{
		auto matchDialog = new MatchResultDialog(match, i_round.getTournament().getContestants());
		m_ui->matchesLayout->addWidget(matchDialog);
		connect(matchDialog, &MatchResultDialog::scoresUpdated, [this](){ if(isFinished()) emit roundFinished();}); //TODO to boost::signals - signal results changed from Match itself
		connect(matchDialog, &MatchResultDialog::scoresUpdated, this, &TournamentRoundWidget::scoresUpdated); //TODO to boost::signals - signal results changed from Match itself
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

	for(const auto& match : *m_round)
	{
		if(!match.isFinished())
		{
			return false;
		}
	}

	return true;
}


//END OF FILE --------------------------------------------------------------------------------------