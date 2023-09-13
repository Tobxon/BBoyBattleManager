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
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//RankingSlide -------------------------------------------------------------------------------------
b3m::gui::ey2023::RankingSlide::RankingSlide(QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::SlideTemplate)
{
	m_ui->setupUi(this);


	int id = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont freshmarker(family);

	QRect centralSpace{ 250, 100, 1420, 880 };

	QList< QString > teamNames{ "DDC Talents", "GingerBreads Crew", "Style Insiders", "Nasty Attack", "Offbeat", "Dream ASF", "Crazy Monkeys", "Fresh Family", "Speed Breaker", "The Wild Foxes", "Die BBoys", "Fire Girls" };
	int heightOfSingleName = centralSpace.height()/teamNames.size();
	freshmarker.setPointSize(heightOfSingleName > 200 ? 100 : heightOfSingleName/2);
	int index = 0;
	for(const auto teamName : teamNames)
	{
		auto* const teamNameLabel = new QLabel(this);
		teamNameLabel->setObjectName(teamName);
		QRect curSpace{ centralSpace.left(), centralSpace.top()+heightOfSingleName*index, centralSpace.width(), heightOfSingleName };
		teamNameLabel->setGeometry(curSpace);
		teamNameLabel->setMidLineWidth(0);
		teamNameLabel->setText(teamName);
		teamNameLabel->setAlignment(Qt::AlignCenter);
		teamNameLabel->setFont(freshmarker);
		teamNameLabel->setAttribute( Qt::WA_TranslucentBackground, true );
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