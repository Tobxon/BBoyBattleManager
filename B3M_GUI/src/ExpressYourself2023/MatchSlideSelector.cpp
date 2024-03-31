//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "MatchSlideSelector.hpp"
#include "ui_SlideTemplate.h"

//std
import <optional>;

//Qt
#include <QFontDatabase>
#include <QStyleOption>
#include <QPainter>

//b3m
import b3m.gui.ey2023;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
using b3m::common::TournamentRound;
using b3m::common::Match;
using b3m::common::Judgement;


static constexpr /*unsigned*/ int widthScreen = 1920;
static constexpr /*unsigned*/ int heightScreen = 1080;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//MatchSlide ---------------------------------------------------------------------------------------
b3m::gui::ey2023::MatchSlide::MatchSlide(TournamentRound& i_round,
	const b3m::gui::presentation::SlidesStyle& i_style, const QString& i_title, QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::SlideTemplate), m_round(&i_round)
{
	m_ui->setupUi(this);

	const auto& matches = m_round->getMatches();
	if(!matches.empty())
	{
		QFont backgroundFont = i_style.getBackgroundFont();
		QFont foregroundFont = i_style.getForegroundFont();

		const int logoWidth = 150;
		const int outerFrameWidth = widthScreen/8-logoWidth;
		const int innerFrameWidth = 0;

		const int outerFrameHeight = heightScreen/16;
		const int titleHeight = heightScreen/8;

		const int numOfRowsWithHeaders = matches.size();
		const int heightOfRow = (heightScreen - 2*outerFrameHeight - titleHeight)/(numOfRowsWithHeaders);

		const int widthOfDrawArea = widthScreen - 2*outerFrameWidth - 2*logoWidth - titleHeight;
		const auto fontSize = widthOfDrawArea/32;
		const auto titleFontSize = titleHeight/2;
		const int widthOfNumbers = fontSize*2;
		const int widthContestantNameWidth = widthOfDrawArea/2 - widthOfNumbers - widthOfNumbers/2;

		foregroundFont.setPointSize(titleFontSize);
		auto *const title = new QLabel(this);
		title->setObjectName("title");
		const QRect titleSpace{ outerFrameWidth+logoWidth+innerFrameWidth, outerFrameHeight, widthOfDrawArea, titleHeight };
		title->setGeometry(titleSpace);
		title->setText(i_title);
		title->setAlignment(Qt::AlignCenter);
		title->setFont(foregroundFont);
		title->setAttribute(Qt::WA_TranslucentBackground, true);

		backgroundFont.setPointSize(fontSize);
		foregroundFont.setPointSize(fontSize);

		QPalette palette;
		int curTop = titleSpace.bottom();
		for (const auto& match : matches)
		{
			const auto &[teamAName, teamBName] = match.getContestantNames();

			auto *const teamAResult = new QLabel(this);
			teamAResult->setObjectName(teamAName + "_result");
			QRect teamAResultSpace{ outerFrameWidth+logoWidth+innerFrameWidth, curTop, widthOfNumbers, heightOfRow };
			teamAResult->setGeometry(teamAResultSpace);
			teamAResult->setText("");
			teamAResult->setAlignment(Qt::AlignCenter);
			teamAResult->setFont(backgroundFont);
			teamAResult->setAttribute(Qt::WA_TranslucentBackground, true);

			auto *const teamANameLabel = new QLabel(this);
			teamANameLabel->setObjectName(QString::fromStdString(teamAName));
			QRect teamALabelSpace{ teamAResultSpace.right(), curTop, widthContestantNameWidth, heightOfRow };
			teamANameLabel->setGeometry(teamALabelSpace);
			teamANameLabel->setText(QString::fromStdString(teamAName));
			teamANameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
			teamANameLabel->setFont(backgroundFont);
			teamANameLabel->setAttribute(Qt::WA_TranslucentBackground, true);
			palette.setColor(teamANameLabel->foregroundRole(), Qt::white);
			teamANameLabel->setPalette(palette);

			auto *const vsLabel = new QLabel(this);
			const char *const vsSymbol{"vs"};
			vsLabel->setObjectName(vsSymbol);
			QRect vsLabelSpace{ teamALabelSpace.right(), curTop, widthOfNumbers, heightOfRow };
			vsLabel->setGeometry(vsLabelSpace);
			vsLabel->setText(vsSymbol);
			vsLabel->setAlignment(Qt::AlignCenter);
			vsLabel->setFont(foregroundFont);
			vsLabel->setAttribute(Qt::WA_TranslucentBackground, true);

			auto *const teamBNameLabel = new QLabel(this);
			teamBNameLabel->setObjectName(QString::fromStdString(teamBName));
			QRect teamBLabelSpace{ vsLabelSpace.right(), curTop, widthContestantNameWidth, heightOfRow };
			teamBNameLabel->setGeometry(teamBLabelSpace);
			teamBNameLabel->setText(QString::fromStdString(teamBName));
			teamBNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
			teamBNameLabel->setFont(backgroundFont);
			teamBNameLabel->setAttribute(Qt::WA_TranslucentBackground, true);
			palette.setColor(teamBNameLabel->foregroundRole(), Qt::white);
			teamBNameLabel->setPalette(palette);

			auto *const teamBResult = new QLabel(this);
			teamBResult->setObjectName(teamBName + "_result");
			const QRect teamBResultSpace{ teamBLabelSpace.right(), curTop, widthOfNumbers, heightOfRow };
			teamBResult->setGeometry(teamBResultSpace);
			teamBResult->setText("");
			teamBResult->setAlignment(Qt::AlignCenter);
			teamBResult->setFont(backgroundFont);
			teamBResult->setAttribute(Qt::WA_TranslucentBackground, true);

			//I#5 to proper observer registrations
			match.m_resultsChangedCallback = [teamAResult, teamBResult](const std::pair< std::optional< Judgement >, std::optional< Judgement >>& i_newResults){
				const auto& teamLhsNewResult = i_newResults.first;
				const auto& teamRhsNewResult = i_newResults.second;
				if(teamLhsNewResult)
				{
					teamAResult->setText(QString::number(teamLhsNewResult.value()));
				}
				if(teamRhsNewResult)
				{
					teamBResult->setText(QString::number(teamRhsNewResult.value()));
				}
			};
			match.m_contestantsChangedCallback = [teamANameLabel, teamBNameLabel](const std::pair< Contestant::Name_t, Contestant::Name_t >& i_newContestants){
				teamANameLabel->setText(QString::fromStdString(i_newContestants.first));
				teamBNameLabel->setText(QString::fromStdString(i_newContestants.second));
			};

			curTop = teamBLabelSpace.bottom();
		}
	}
}

b3m::gui::ey2023::MatchSlide::~MatchSlide()
{
	delete m_ui;
}

void b3m::gui::ey2023::MatchSlide::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QWidget::paintEvent(event);
}


//MatchSlideSelector -------------------------------------------------------------------------------
b3m::gui::ey2023::MatchSlideSelector::MatchSlideSelector(TournamentRound& i_round, const QString& i_title, QWidget* i_parent)
		: SlideSelector("Match Slide", i_parent), m_slide(new MatchSlide(i_round, b3m::gui::ey2023::SlidesStyle{}, i_title))
{}

b3m::gui::ey2023::MatchSlideSelector::MatchSlideSelector(TournamentRound& i_round, QWidget* i_parent)
: MatchSlideSelector(i_round, {}, i_parent)
{}


//END OF FILE --------------------------------------------------------------------------------------