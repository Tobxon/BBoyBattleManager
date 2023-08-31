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
		m_ui->matchesLayout->addWidget(new MatchResultDialog(match));
	}
}

b3m::gui::TournamentRoundWidget::~TournamentRoundWidget()
{
	delete m_ui;
}


//END OF FILE --------------------------------------------------------------------------------------