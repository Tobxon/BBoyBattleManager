//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "RankingSlideSelector.hpp"
#include "ui_SlideTemplate.h"

//Qt
#include <QPaintEvent>
#include <QPainter>
#include <QFontDatabase>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
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
	int id = QFontDatabase::addApplicationFont("C:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont freshmarker(family);

	QFont system;

	QList< QString > teamNames{ "DDC Talents", "GingerBreads Crew", "Style Insiders", "Nasty Attack", "Offbeat", "Dream ASF", "Crazy Monkeys", "Fresh Family", "Speed Breaker", "The Wild Foxes", "Die BBoys", "Fire Girls" };
	int heightOfRow = (heightScreen/10*8)/(teamNames.size()+1);
	const auto fontSize = heightOfRow > 200 ? 100 : heightOfRow/2;
	freshmarker.setPointSize(fontSize);
	system.setPointSize(fontSize);
	int index = 0;
	{
		// #
		QString rankingHeaderLettering{"#"};
		auto* const rankingHeader = new QLabel(this);
		rankingHeader->setObjectName(rankingHeaderLettering);
		QRect rankingHeaderSpace{ widthScreen/10, heightScreen/10, heightOfRow, heightOfRow };
		rankingHeader->setGeometry(rankingHeaderSpace);
		rankingHeader->setMidLineWidth(0);
		rankingHeader->setText(rankingHeaderLettering);
		rankingHeader->setAlignment(Qt::AlignCenter);
		rankingHeader->setFont(system);
		rankingHeader->setAttribute( Qt::WA_TranslucentBackground, true );

		// Crew
		QString crewHeaderLettering{"Crew"};
		auto* const crewHeader = new QLabel(this);
		crewHeader->setObjectName(crewHeaderLettering);
		QRect crewHeaderSpace{ widthScreen/10+heightOfRow, heightScreen/10, widthScreen/2-widthScreen/10+heightOfRow, heightOfRow };
		crewHeader->setGeometry(crewHeaderSpace);
		crewHeader->setMidLineWidth(0);
		crewHeader->setText(crewHeaderLettering);
		crewHeader->setAlignment(Qt::AlignCenter);
		crewHeader->setFont(system);
		crewHeader->setAttribute( Qt::WA_TranslucentBackground, true );

		// Siege
		QString winsHeaderLettering{"Siege"};
		auto* const winsHeader = new QLabel(this);
		winsHeader->setObjectName(winsHeaderLettering);
		QRect winsHeaderSpace{ widthScreen/2, heightScreen/10, (widthScreen/2-widthScreen/10)/2, heightOfRow };
		winsHeader->setGeometry(winsHeaderSpace);
		winsHeader->setMidLineWidth(0);
		winsHeader->setText(winsHeaderLettering);
		winsHeader->setAlignment(Qt::AlignCenter);
		winsHeader->setFont(system);
		winsHeader->setAttribute( Qt::WA_TranslucentBackground, true );

		// Hände
		QString pointsHeaderLettering{"Siege"};
		auto* const pointsHeader = new QLabel(this);
		pointsHeader->setObjectName(pointsHeaderLettering);
		QRect pointsHeaderSpace{ widthScreen/2 + (widthScreen/2-widthScreen/10)/2, heightScreen/10, (widthScreen/2-widthScreen/10)/2, heightOfRow };
		pointsHeader->setGeometry(pointsHeaderSpace);
		pointsHeader->setMidLineWidth(0);
		pointsHeader->setText(winsHeaderLettering);
		pointsHeader->setAlignment(Qt::AlignCenter);
		pointsHeader->setFont(system);
		pointsHeader->setAttribute( Qt::WA_TranslucentBackground, true );
	}
	for(const auto teamName : teamNames)
	{
//		auto* const teamNameLabel = new QLabel(this);
//		teamNameLabel->setObjectName(teamName);
//		QRect curSpace{ centralSpace.left(), centralSpace.top()+heightOfRow*index, centralSpace.width(), heightOfRow };
//		teamNameLabel->setGeometry(curSpace);
//		teamNameLabel->setMidLineWidth(0);
//		teamNameLabel->setText(teamName);
//		teamNameLabel->setAlignment(Qt::AlignCenter);
//		teamNameLabel->setFont(freshmarker);
//		teamNameLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		++index;
	}
//	arrangeTeamNames();
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