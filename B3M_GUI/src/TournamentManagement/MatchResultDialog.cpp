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

	const auto teams = m_match->getContestantNames();
	const auto teamAName = QString::fromStdString(teams.first);
	const auto teamBName = QString::fromStdString(teams.second);
	m_ui->teamA->setText(teamAName);
	m_ui->teamB->setText(teamBName);

	//TODO to boost::signals - signal results changed from Match itself
	connect(m_ui->resultsLock, &QCheckBox::stateChanged, [this](int checkState){
		const auto resultLhsTeam = m_ui->resultTeamA->value();
		const auto resultRhsTeam = m_ui->resultTeamB->value();

		if(checkState == Qt::Unchecked || (resultLhsTeam == 0 && resultRhsTeam == 0))
		{
			m_match->clearResult();
		} else {
			m_match->setResult(m_ui->teamA->text().toStdString(), resultLhsTeam);
			m_match->setResult(m_ui->teamB->text().toStdString(), resultRhsTeam);
		}
		emit scoresUpdated();
	});
	connect(m_ui->resultsLock, &QCheckBox::stateChanged, [this](bool locked){
		m_ui->resultTeamA->setEnabled(!locked);
		m_ui->resultTeamB->setEnabled(!locked);
	});
	//TODO to boost::signals - signal results changed from Match itself

	static constexpr auto numOfJudges = 3.0;
	m_ui->resultTeamA->setMaximum(numOfJudges);
	m_ui->resultTeamB->setMaximum(numOfJudges);
	connect(m_ui->resultTeamA, &QDoubleSpinBox::valueChanged, [this](double i_newOtherVal){
		const auto thisNewVal = numOfJudges-i_newOtherVal;
		if(m_ui->resultTeamB->value() != thisNewVal)
		{
			m_ui->resultTeamB->setValue(thisNewVal);
		}
	});
	connect(m_ui->resultTeamB, &QDoubleSpinBox::valueChanged, [this](double i_newOtherVal){
		const auto thisNewVal = numOfJudges-i_newOtherVal;
		if(m_ui->resultTeamA->value() != thisNewVal)
		{
			m_ui->resultTeamA->setValue(thisNewVal);
		}
	});
}

b3m::gui::MatchResultDialog::~MatchResultDialog()
{
	delete m_ui;
}


//END OF FILE --------------------------------------------------------------------------------------