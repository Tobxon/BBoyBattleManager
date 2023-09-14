//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "MatchSlideSelector.hpp"
#include "ui_SlideTemplate.h"

//Qt
#include <QFontDatabase>

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
using b3m::common::TournamentRound;
using b3m::common::Match;
using b3m::common::Team;


static constexpr /*unsigned*/ int widthScreen = 1920;
static constexpr /*unsigned*/ int heightScreen = 1080;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//MatchSlide ---------------------------------------------------------------------------------------
b3m::gui::ey2023::MatchSlide::MatchSlide(QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::SlideTemplate)
{
	m_ui->setupUi(this);

	//TODO import font at a central place
	int id = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont freshmarker(family);

	QFont system;

	Match testMatch{Team("team1"),Team("crew2")};
	TournamentRound curRound{
		{Team("DDC Talents"), Team("Crazy Monkeys")},
		{Team("GingerBreads Crew"), Team("Fresh Family")},
		{Team("Style Insiders"), Team("Speed Breaker")},
		{Team("Nasty Attack"), Team("The Wild Foxes")},
		{Team("Offbeat"), Team("Die BBoys")},
		{Team("Dream ASF"), Team("Fire Girls")}
	};
	int heightOfSingleMatch = (heightScreen/10*8)/curRound.size();

	const auto fontSize = heightOfSingleMatch > 100 ? 50 : heightOfSingleMatch/2;
	freshmarker.setPointSize(fontSize);
	system.setPointSize(fontSize);

	int index = 0;
	for(const auto& match : curRound)
	{
		const auto& [teamAName, teamBName] = match.getContestantNames();
		auto* const teamANameLabel = new QLabel(this);
		teamANameLabel->setObjectName(QString::fromStdString(teamAName));
		QRect teamALabelSpace{ widthScreen/10, heightScreen/10+index*heightOfSingleMatch, (widthScreen*8/10-heightOfSingleMatch)/2, heightOfSingleMatch };
		teamANameLabel->setGeometry(teamALabelSpace);
//		teamANameLabel->setMidLineWidth(0);
		teamANameLabel->setText(QString::fromStdString(teamAName));
		teamANameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
		teamANameLabel->setFont(freshmarker);
		teamANameLabel->setAttribute( Qt::WA_TranslucentBackground, true );

		auto* const vsLabel = new QLabel(this);
		const char* const vsSymbol{"vs"};
		vsLabel->setObjectName(vsSymbol);
		QRect vsLabelSpace{ widthScreen/2-heightOfSingleMatch/2, heightScreen/10+index*heightOfSingleMatch, heightOfSingleMatch, heightOfSingleMatch };
		vsLabel->setGeometry(vsLabelSpace);
//		vsLabel->setMidLineWidth(0);
		vsLabel->setText(vsSymbol);
		vsLabel->setAlignment(Qt::AlignCenter);
		vsLabel->setFont(system); //TODO
		vsLabel->setAttribute( Qt::WA_TranslucentBackground, true );

		auto* const teamBNameLabel = new QLabel(this);
		teamBNameLabel->setObjectName(QString::fromStdString(teamBName));
		QRect teamBLabelSpace{ widthScreen/2+heightOfSingleMatch/2, heightScreen/10+index*heightOfSingleMatch, (widthScreen*8/10-heightOfSingleMatch)/2, heightOfSingleMatch };
		teamBNameLabel->setGeometry(teamBLabelSpace);
//		teamBNameLabel->setMidLineWidth(0);
		teamBNameLabel->setText(QString::fromStdString(teamBName));
		teamBNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		teamBNameLabel->setFont(freshmarker);
		teamBNameLabel->setAttribute( Qt::WA_TranslucentBackground, true );

		++index;
	}
}

b3m::gui::ey2023::MatchSlide::~MatchSlide()
{
	delete m_ui;
}


//MatchSlideSelector -------------------------------------------------------------------------------
b3m::gui::ey2023::MatchSlideSelector::MatchSlideSelector(QWidget* i_parent)
		: SlideSelector("Match Slide", i_parent)
{
}


//END OF FILE --------------------------------------------------------------------------------------