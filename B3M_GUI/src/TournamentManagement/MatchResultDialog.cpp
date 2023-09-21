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

b3m::gui::MatchResultDialog::MatchResultDialog(Match& i_match, const std::vector<Contestant>& i_contestants, QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::MatchResultDialog()), m_match(&i_match)
{
	m_ui->setupUi(this);

	const auto teams = m_match->getContestantNames();
	const auto teamLhsName = teams.first;
	const auto teamRhsName = teams.second;

	m_ui->TeamLhsSelector->addItem(QString::fromStdString(teamLhsName));
	m_ui->TeamRhsSelector->addItem(QString::fromStdString(teamRhsName));
	for(const auto& otherContestant : i_contestants)
	{
		const auto& otherContestantName = otherContestant.getName();
		if(otherContestantName != teamLhsName)
		{
			m_ui->TeamLhsSelector->addItem(QString::fromStdString(otherContestantName));
		}
		if(otherContestantName != teamRhsName)
		{
			m_ui->TeamRhsSelector->addItem(QString::fromStdString(otherContestantName));
		}
	}

	//TODO to boost::signals - signal results changed from Match itself
	connect(m_ui->TeamLhsSelector, &QComboBox::currentIndexChanged, [this](int newIndex){
		const auto& oldContestants = m_match->getContestantNames();
		const QString& newContestantName = m_ui->TeamLhsSelector->currentText(); //TODO save?
		m_match->changeContestant(oldContestants.first, newContestantName.toStdString());
	});
	connect(m_ui->TeamRhsSelector, &QComboBox::currentIndexChanged, [this](){
		const auto& oldContestants = m_match->getContestantNames();
		const QString& newContestantName = m_ui->TeamRhsSelector->currentText(); //TODO save?
		m_match->changeContestant(oldContestants.second, newContestantName.toStdString());
	});
	//TODO to boost::signals - signal results changed from Match itself


	//TODO to boost::signals - signal results changed from Match itself
	connect(m_ui->resultsLock, &QCheckBox::stateChanged, [this](int checkState){
		const auto resultLhsTeam = m_ui->resultTeamLhs->value();
		const auto resultRhsTeam = m_ui->resultTeamRhs->value();

		if(checkState == Qt::Unchecked || (resultLhsTeam == 0 && resultRhsTeam == 0))
		{
			m_match->clearResult();
		} else {
			m_match->setResult(m_ui->TeamLhsSelector->currentText().toStdString(), resultLhsTeam);
			m_match->setResult(m_ui->TeamRhsSelector->currentText().toStdString(), resultRhsTeam);
		}
		emit scoresUpdated();
	});
	connect(m_ui->resultsLock, &QCheckBox::stateChanged, [this](bool locked){
		m_ui->resultTeamLhs->setEnabled(!locked);
		m_ui->resultTeamRhs->setEnabled(!locked);
	});
	//TODO to boost::signals - signal results changed from Match itself

	static constexpr auto numOfJudges = 3.0;
	m_ui->resultTeamLhs->setMaximum(numOfJudges);
	m_ui->resultTeamRhs->setMaximum(numOfJudges);
	connect(m_ui->resultTeamLhs, &QDoubleSpinBox::valueChanged, [this](double i_newOtherVal){
		const auto thisNewVal = numOfJudges-i_newOtherVal;
		if(m_ui->resultTeamRhs->value() != thisNewVal)
		{
			m_ui->resultTeamRhs->setValue(thisNewVal);
		}
	});
	connect(m_ui->resultTeamRhs, &QDoubleSpinBox::valueChanged, [this](double i_newOtherVal){
		const auto thisNewVal = numOfJudges-i_newOtherVal;
		if(m_ui->resultTeamLhs->value() != thisNewVal)
		{
			m_ui->resultTeamLhs->setValue(thisNewVal);
		}
	});
}

b3m::gui::MatchResultDialog::~MatchResultDialog()
{
	delete m_ui;
}


//END OF FILE --------------------------------------------------------------------------------------