//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "RankingSlideSelector.hpp"
#include "ui_SlideTemplate.h"

//std
import <utility>;

//Qt
#include <QPaintEvent>
#include <QPainter>
#include <QFontDatabase>

//b3m
import b3m.common;
import b3m.logic;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
using b3m::common::History;


static constexpr /*unsigned*/ int widthScreen = 1920;
static constexpr /*unsigned*/ int heightScreen = 1080;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//RankingSlide -------------------------------------------------------------------------------------
b3m::gui::ey2023::RankingSlide::RankingSlide(QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::SlideTemplate)
{
	m_ui->setupUi(this);

	//TODO import font at a central place
	int id = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont freshmarker(family);

	QFont system;

	QList<std::pair< QString, std::pair<int, int> >> teamNames{
		{"DDC Talents",{3, 8}},
		{"GingerBreads Crew",{3, 8}},
		{"Style Insiders",{2, 7}},
		{"Nasty Attack",{2, 6}},
		{"Offbeat",{2, 6}},
		{"Dream ASF",{1, 4}},
		{"Crazy Monkeys",{1, 4}},
		{"Fresh Family",{1, 3}},
		{"Speed Breaker",{1, 3}},
		{"The Wild Foxes",{1, 3}},
		{"Die BBoys",{1, 2}},
		{"Fire Girls",{0, 0}}};

//	const auto

	const int logoWidth = 150;
	const int outerFrameWidth = widthScreen/8-logoWidth;
	const int innerFrameWidth = widthScreen/16;
	const int rankingNumberColumnWidth = widthScreen/16;
	const int crewColumnWidth = widthScreen*5/16;
	const int winsColumnWidth = widthScreen*2/16;

	const int outerFrameHeight = heightScreen/8;
	const int innerFrameHeight = 0;

	const int numOfRowsWithHeaders = teamNames.size()+1;
	int heightOfRow = (heightScreen-2*outerFrameHeight-2*innerFrameHeight)/(numOfRowsWithHeaders);

	const auto fontSize = heightOfRow > 200 ? 100 : heightOfRow/2;
	freshmarker.setPointSize(fontSize);
	system.setPointSize(fontSize);

	// #
	QString rankingHeaderLettering{"#"};
	auto* const rankingHeader = new QLabel(this);
	rankingHeader->setObjectName(rankingHeaderLettering + "_header");
	const QRect rankingHeaderSpace{ outerFrameWidth+logoWidth+innerFrameWidth, outerFrameHeight+innerFrameHeight, rankingNumberColumnWidth, heightOfRow };
	rankingHeader->setGeometry(rankingHeaderSpace);
	rankingHeader->setText(rankingHeaderLettering);
	rankingHeader->setAlignment(Qt::AlignCenter);
	rankingHeader->setFont(system);
	rankingHeader->setAttribute( Qt::WA_TranslucentBackground, true );
	rankingHeader->setStyleSheet("{color: #FFFFFF}");

	// Crew
	QString crewHeaderLettering{"Crew"};
	auto* const crewHeader = new QLabel(this);
	crewHeader->setObjectName(crewHeaderLettering + "_header");
	const QRect crewHeaderSpace{ rankingHeaderSpace.right(), outerFrameHeight+innerFrameHeight, crewColumnWidth, heightOfRow };
	crewHeader->setGeometry(crewHeaderSpace);
	crewHeader->setText(crewHeaderLettering);
	crewHeader->setAlignment(Qt::AlignCenter);
	crewHeader->setFont(system);
	crewHeader->setAttribute( Qt::WA_TranslucentBackground, true );
	crewHeader->setStyleSheet("{color: #FFFFFF}");

	// Siege
	QString winsHeaderLettering{"Siege"};
	auto* const winsHeader = new QLabel(this);
	winsHeader->setObjectName(winsHeaderLettering + "_header");
	const QRect winsHeaderSpace{ crewHeaderSpace.right(), outerFrameHeight+innerFrameHeight, winsColumnWidth, heightOfRow };
	winsHeader->setGeometry(winsHeaderSpace);
	winsHeader->setText(winsHeaderLettering);
	winsHeader->setAlignment(Qt::AlignCenter);
	winsHeader->setFont(system);
	winsHeader->setAttribute( Qt::WA_TranslucentBackground, true );
	winsHeader->setStyleSheet("{color: #000000}");

	// Hände
	QString pointsHeaderLettering{"Hände"};
	auto* const pointsHeader = new QLabel(this);
	pointsHeader->setObjectName(pointsHeaderLettering + "_header");
	const QRect pointsHeaderSpace{ winsHeaderSpace.right(), outerFrameHeight+innerFrameHeight, winsColumnWidth, heightOfRow };
	pointsHeader->setGeometry(pointsHeaderSpace);
	pointsHeader->setText(pointsHeaderLettering);
	pointsHeader->setAlignment(Qt::AlignCenter);
	pointsHeader->setFont(system);
	pointsHeader->setAttribute( Qt::WA_TranslucentBackground, true );
	pointsHeader->setStyleSheet("{color: #FFFFFF}");

	int lastRowBottom = crewHeaderSpace.bottom();
	int ranking = 1;
	for(const auto& [teamName, results] : teamNames)
	{
		auto* const teamRankingLabel = new QLabel(this);
		teamRankingLabel->setObjectName(teamName + "_ranking");
		const QRect rankingLabelSpace{ rankingHeaderSpace.left(), lastRowBottom, rankingHeaderSpace.width(), heightOfRow };
		teamRankingLabel->setGeometry(rankingLabelSpace);
		teamRankingLabel->setText(QString::number(ranking));
		teamRankingLabel->setAlignment(Qt::AlignCenter);
		teamRankingLabel->setFont(freshmarker);
		teamRankingLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		teamRankingLabel->setStyleSheet("{color: #FFFFFF}");
		++ranking;

		auto* const crewLabel = new QLabel(this);
		crewLabel->setObjectName(teamName);
		const QRect crewLabelSpace{ crewHeaderSpace.left(), lastRowBottom, crewHeaderSpace.width(), heightOfRow };
		crewLabel->setGeometry(crewLabelSpace);
		crewLabel->setText(teamName);
		crewLabel->setAlignment(Qt::AlignCenter);
		crewLabel->setFont(freshmarker);
		crewLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		crewLabel->setStyleSheet("{color: #FFFFFF}");

		auto* const winsLabel = new QLabel(this);
		winsLabel->setObjectName(teamName + "_wins");
		const QRect winsLabelSpace{ winsHeaderSpace.left(), lastRowBottom, winsHeaderSpace.width(), heightOfRow };
		winsLabel->setGeometry(winsLabelSpace);
		winsLabel->setText(QString::number(results.first));
		winsLabel->setAlignment(Qt::AlignCenter);
		winsLabel->setFont(freshmarker);
		winsLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		winsLabel->setStyleSheet("{color: #FFFFFF}");

		auto* const pointsLabel = new QLabel(this);
		pointsLabel->setObjectName(teamName + "_points");
		const QRect pointsLabelSpace{ pointsHeaderSpace.left(), lastRowBottom, pointsHeaderSpace.width(), heightOfRow };
		pointsLabel->setGeometry(pointsLabelSpace);
		pointsLabel->setText(QString::number(results.second));
		pointsLabel->setAlignment(Qt::AlignCenter);
		pointsLabel->setFont(freshmarker);
		pointsLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		pointsLabel->setStyleSheet("{color: #FFFFFF}");

		lastRowBottom = crewLabelSpace.bottom();
	}
}

b3m::gui::ey2023::RankingSlide::~RankingSlide()
{
	delete m_ui;
}

void b3m::gui::ey2023::RankingSlide::arrangeTeamNames()
{

}


//RankingSlideSelector -----------------------------------------------------------------------------
b3m::gui::ey2023::RankingSlideSelector::RankingSlideSelector(QWidget* i_parent)
	: SlideSelector("Ranking Slide", i_parent)
{
}


//END OF FILE --------------------------------------------------------------------------------------