//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "RankingSlideSelector.hpp"
#include "ui_SlideTemplate.h"

//std
import <utility>;
import <cmath>;

//Qt
#include <QPaintEvent>
#include <QPainter>
#include <QFontDatabase>
#include <QStyleOption>

//b3m
import b3m.common;
import b3m.logic;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
using b3m::common::History;
using b3m::common::SortedContestantsRanking;


static constexpr /*unsigned*/ int widthScreen = 1920;
static constexpr /*unsigned*/ int heightScreen = 1080;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//RankingSlide -------------------------------------------------------------------------------------
b3m::gui::ey2023::RankingSlide::RankingSlide(const SortedContestantsRanking& i_contestantsWithRating, QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::SlideTemplate)
{
	m_ui->setupUi(this);

	//TODO import font at a central place
	int id = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf"); //TODO to relative path
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont freshmarker(family);
	int idBerlinSans = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/BRLNSB.ttf"); //TODO to relative path
	QString familyBerlinSans = QFontDatabase::applicationFontFamilies(idBerlinSans).at(0);
	QFont berlinSans(familyBerlinSans);

	const int logoWidth = 150;
	const int outerFrameWidth = widthScreen/8-logoWidth;
	const int innerFrameWidth = widthScreen/16;
	const int rankingNumberColumnWidth = widthScreen/16;
	const int crewColumnWidth = widthScreen*5/16;
	const int winsColumnWidth = widthScreen*2/16;

	const int outerFrameHeight = heightScreen/16;
	const int innerFrameHeight = 0;

	const int numOfRowsWithHeaders = i_contestantsWithRating.size()+1;
	int heightOfRow = (heightScreen-2*outerFrameHeight-2*innerFrameHeight)/(numOfRowsWithHeaders);

	const auto fontSize = heightOfRow > 200 ? 100 : heightOfRow/2;
	freshmarker.setPointSize(fontSize);
	berlinSans.setPointSize(fontSize);

	// #
	QString rankingHeaderLettering{"#"};
	auto* const rankingHeader = new QLabel(this);
	rankingHeader->setObjectName(rankingHeaderLettering + "_header");
	const QRect rankingHeaderSpace{ outerFrameWidth+logoWidth+innerFrameWidth, outerFrameHeight+innerFrameHeight, rankingNumberColumnWidth, heightOfRow };
	rankingHeader->setGeometry(rankingHeaderSpace);
	rankingHeader->setText(rankingHeaderLettering);
	rankingHeader->setAlignment(Qt::AlignCenter);
	rankingHeader->setFont(berlinSans);
	rankingHeader->setAttribute( Qt::WA_TranslucentBackground, true );

	// Crew
	QString crewHeaderLettering{"Crew"};
	auto* const crewHeader = new QLabel(this);
	crewHeader->setObjectName(crewHeaderLettering + "_header");
	const QRect crewHeaderSpace{ rankingHeaderSpace.right(), outerFrameHeight+innerFrameHeight, crewColumnWidth, heightOfRow };
	crewHeader->setGeometry(crewHeaderSpace);
	crewHeader->setText(crewHeaderLettering);
	crewHeader->setAlignment(Qt::AlignCenter);
	crewHeader->setFont(berlinSans);
	crewHeader->setAttribute( Qt::WA_TranslucentBackground, true );

	// Siege
	QString winsHeaderLettering{"Siege"};
	auto* const winsHeader = new QLabel(this);
	winsHeader->setObjectName(winsHeaderLettering + "_header");
	const QRect winsHeaderSpace{ crewHeaderSpace.right(), outerFrameHeight+innerFrameHeight, winsColumnWidth, heightOfRow };
	winsHeader->setGeometry(winsHeaderSpace);
	winsHeader->setText(winsHeaderLettering);
	winsHeader->setAlignment(Qt::AlignCenter);
	winsHeader->setFont(berlinSans);
	winsHeader->setAttribute( Qt::WA_TranslucentBackground, true );

	// Hände
	QString pointsHeaderLettering{"Hände"};
	auto* const pointsHeader = new QLabel(this);
	pointsHeader->setObjectName(pointsHeaderLettering + "_header");
	const QRect pointsHeaderSpace{ winsHeaderSpace.right(), outerFrameHeight+innerFrameHeight, winsColumnWidth, heightOfRow };
	pointsHeader->setGeometry(pointsHeaderSpace);
	pointsHeader->setText(pointsHeaderLettering);
	pointsHeader->setAlignment(Qt::AlignCenter);
	pointsHeader->setFont(berlinSans);
	pointsHeader->setAttribute( Qt::WA_TranslucentBackground, true );

	QPalette palette;

	int lastRowBottom = crewHeaderSpace.bottom();
	int ranking = 1;
	for(const auto& [teamName, rating] : i_contestantsWithRating)
	{
		auto* const teamRankingLabel = new QLabel(this);
		teamRankingLabel->setObjectName(teamName + "_ranking");
		const QRect rankingLabelSpace{ rankingHeaderSpace.left(), lastRowBottom, rankingHeaderSpace.width(), heightOfRow };
		teamRankingLabel->setGeometry(rankingLabelSpace);
		teamRankingLabel->setText(QString::number(ranking));
		teamRankingLabel->setAlignment(Qt::AlignCenter);
		teamRankingLabel->setFont(freshmarker);
		teamRankingLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		++ranking;

		auto* const crewLabel = new QLabel(this);
		crewLabel->setObjectName(teamName);
		const QRect crewLabelSpace{ crewHeaderSpace.left(), lastRowBottom, crewHeaderSpace.width(), heightOfRow };
		crewLabel->setGeometry(crewLabelSpace);
		crewLabel->setText(QString::fromStdString(teamName));
		crewLabel->setAlignment(Qt::AlignCenter);
		crewLabel->setFont(freshmarker);
		crewLabel->setAttribute( Qt::WA_TranslucentBackground, true );
		palette.setColor(crewLabel->foregroundRole(), Qt::white);
		crewLabel->setPalette(palette);

		const int& wins = rating.m_numOfWins;
		auto* const winsLabel = new QLabel(this);
		winsLabel->setObjectName(teamName + "_wins");
		const QRect winsLabelSpace{ winsHeaderSpace.left(), lastRowBottom, winsHeaderSpace.width(), heightOfRow };
		winsLabel->setGeometry(winsLabelSpace);
		winsLabel->setText(QString::number(wins));
		winsLabel->setAlignment(Qt::AlignCenter);
		winsLabel->setFont(freshmarker);
		winsLabel->setAttribute( Qt::WA_TranslucentBackground, true );

		const auto& votes = rating.m_numOfVotes - (rating.m_numOfByes * b3m::common::freeTicket.second);
		auto* const pointsLabel = new QLabel(this);
		pointsLabel->setObjectName(teamName + "_points");
		const QRect pointsLabelSpace{ pointsHeaderSpace.left(), lastRowBottom, pointsHeaderSpace.width(), heightOfRow };
		pointsLabel->setGeometry(pointsLabelSpace);
		pointsLabel->setText(QString::number(votes));
		pointsLabel->setAlignment(Qt::AlignCenter);
		pointsLabel->setFont(freshmarker);
		pointsLabel->setAttribute( Qt::WA_TranslucentBackground, true );

		if(rating.m_numOfByes > 0)
		{
			const int iconLength = fontSize*3/2;
			const int iconUp = lastRowBottom+(heightOfRow-iconLength)/2;

			auto* const freeTicketWinsIcon = new QLabel(this);
			freeTicketWinsIcon->setObjectName(teamName + "_wins_bye");
			const QRect freeTicketIconWinsSpace{ winsLabelSpace.left() + winsLabelSpace.width()*2/3, iconUp, iconLength, iconLength };
			freeTicketWinsIcon->setGeometry(freeTicketIconWinsSpace);
			freeTicketWinsIcon->setPixmap(QPixmap{"D:/Dev/Repos/B3M_dev/EY2023/resources/byeIcon.png"}); //TODO to relative path
			freeTicketWinsIcon->setAttribute( Qt::WA_TranslucentBackground, true );
			freeTicketWinsIcon->setScaledContents(true);

			auto* const freeTicketPointsIcon = new QLabel(this);
			freeTicketPointsIcon->setObjectName(teamName + "_points_bye");
			const QRect freeTicketIconPointsSpace{ pointsLabelSpace.left() + pointsLabelSpace.width()*2/3, iconUp, iconLength, iconLength };
			freeTicketPointsIcon->setGeometry(freeTicketIconPointsSpace);
			freeTicketPointsIcon->setPixmap(QPixmap{"D:/Dev/Repos/B3M_dev/EY2023/resources/byeIcon.png"}); //TODO to relative path
			freeTicketPointsIcon->setAttribute( Qt::WA_TranslucentBackground, true );
			freeTicketPointsIcon->setScaledContents(true);
		}

		lastRowBottom = crewLabelSpace.bottom();
	}
}

b3m::gui::ey2023::RankingSlide::~RankingSlide()
{
	delete m_ui;
}

void b3m::gui::ey2023::RankingSlide::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(event);
}


//RankingSlideSelector -----------------------------------------------------------------------------
b3m::gui::ey2023::RankingSlideSelector::RankingSlideSelector(const SortedContestantsRanking& i_contestantsWithRating, QWidget* i_parent)
	: SlideSelector("Ranking Slide", i_parent), m_slide(new RankingSlide(i_contestantsWithRating))
{
}


//END OF FILE --------------------------------------------------------------------------------------