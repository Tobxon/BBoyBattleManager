//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "MatchSlideSelector.hpp"
#include "ui_SlideTemplate.h"

//std
import <cmath>;

//Qt
#include <QFontDatabase>

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
using b3m::common::TournamentRound;
using b3m::common::Match;


static constexpr /*unsigned*/ int widthScreen = 1920;
static constexpr /*unsigned*/ int heightScreen = 1080;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//MatchSlide ---------------------------------------------------------------------------------------
b3m::gui::ey2023::MatchSlide::MatchSlide(TournamentRound& i_round, QWidget* i_parent)
	: QWidget(i_parent), m_ui(new Ui::SlideTemplate), m_round(&i_round)
{
	m_ui->setupUi(this);

	if(!m_round->empty())
	{
		//TODO import font at a central place
		int idFreshmaker = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf");
		QString familyFreshmaker = QFontDatabase::applicationFontFamilies(idFreshmaker).at(0);
		QFont freshmarker(familyFreshmaker);
		int idBerlinSans = QFontDatabase::addApplicationFont("D:/Dev/Repos/B3M_dev/EY2023/resources/BRLNSB.ttf");
		QString familyBerlinSans = QFontDatabase::applicationFontFamilies(idBerlinSans).at(0);
		QFont berlinSans(familyBerlinSans);

		const int logoWidth = 150;
		const int outerFrameWidth = widthScreen/8-logoWidth;
		const int innerFrameWidth = 0;

		const int outerFrameHeight = heightScreen/8;
		const int innerFrameHeight = 0;

		const int numOfRowsWithHeaders = m_round->size();
		const int heightOfRow = (heightScreen - 2*outerFrameHeight - 2*innerFrameHeight)/(numOfRowsWithHeaders);

		const int widthOfDrawArea = widthScreen - 2*outerFrameWidth - 2*logoWidth - 2*innerFrameWidth;
		const auto fontSize = widthOfDrawArea/32;
		const int widthOfNumbers = fontSize*2;
		const int widthContestantNameWidth = widthOfDrawArea/2 - widthOfNumbers - widthOfNumbers/2;

		freshmarker.setPointSize(fontSize);
		berlinSans.setPointSize(fontSize);

		QPalette palette;

		int curTop = outerFrameHeight+innerFrameHeight;
		for (const auto& match : *m_round)
		{
			const auto &[teamAName, teamBName] = match.getContestantNames();

			auto *const teamAResult = new QLabel(this);
			teamAResult->setObjectName(teamAName + "_result");
			QRect teamAResultSpace{ outerFrameWidth+logoWidth+innerFrameWidth, curTop, widthOfNumbers, heightOfRow };
			teamAResult->setGeometry(teamAResultSpace);
			teamAResult->setText("");
			teamAResult->setAlignment(Qt::AlignCenter);
			teamAResult->setFont(freshmarker); //TODO
			teamAResult->setAttribute(Qt::WA_TranslucentBackground, true);
			m_contestantsScores[teamAName] = teamAResult;

			auto *const teamANameLabel = new QLabel(this);
			teamANameLabel->setObjectName(QString::fromStdString(teamAName));
			QRect teamALabelSpace{ teamAResultSpace.right(), curTop, widthContestantNameWidth, heightOfRow };
			teamANameLabel->setGeometry(teamALabelSpace);
			teamANameLabel->setText(QString::fromStdString(teamAName));
			teamANameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
			teamANameLabel->setFont(freshmarker);
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
			vsLabel->setFont(berlinSans); //TODO
			vsLabel->setAttribute(Qt::WA_TranslucentBackground, true);

			auto *const teamBNameLabel = new QLabel(this);
			teamBNameLabel->setObjectName(QString::fromStdString(teamBName));
			QRect teamBLabelSpace{ vsLabelSpace.right(), curTop, widthContestantNameWidth, heightOfRow };
			teamBNameLabel->setGeometry(teamBLabelSpace);
			teamBNameLabel->setText(QString::fromStdString(teamBName));
			teamBNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
			teamBNameLabel->setFont(freshmarker);
			teamBNameLabel->setAttribute(Qt::WA_TranslucentBackground, true);
			palette.setColor(teamBNameLabel->foregroundRole(), Qt::white);
			teamBNameLabel->setPalette(palette);

			auto *const teamBResult = new QLabel(this);
			teamBResult->setObjectName(teamBName + "_result");
			const QRect teamBResultSpace{ teamBLabelSpace.right(), curTop, widthOfNumbers, heightOfRow };
			teamBResult->setGeometry(teamBResultSpace);
			teamBResult->setText("");
			teamBResult->setAlignment(Qt::AlignCenter);
			teamBResult->setFont(freshmarker); //TODO
			teamBResult->setAttribute(Qt::WA_TranslucentBackground, true);
			m_contestantsScores[teamBName] = teamBResult;

			curTop = teamBLabelSpace.bottom();
		}
	}
}

b3m::gui::ey2023::MatchSlide::~MatchSlide()
{
	delete m_ui;
}

void b3m::gui::ey2023::MatchSlide::updateScores()
{
	for(const auto match : *m_round)
	{
		const auto& [teamAName, teamBName] = match.getContestantNames();
		const auto& results = match.getResults();
		if(results)
		{
			const auto& resultsVal = results.value();
			if(m_contestantsScores.contains(teamAName) && resultsVal.contains(teamAName))
			{
				const auto newText = QString::number(std::lround(resultsVal.at(teamAName).second));
				m_contestantsScores[teamAName]->setText(newText);
			}
			if(m_contestantsScores.contains(teamBName) && resultsVal.contains(teamBName))
			{
				const auto newText = QString::number(std::lround(resultsVal.at(teamBName).second));
				m_contestantsScores[teamBName]->setText(newText);
			}
		}
	}
}


//MatchSlideSelector -------------------------------------------------------------------------------
b3m::gui::ey2023::MatchSlideSelector::MatchSlideSelector(TournamentRound& i_round, QWidget* i_parent)
		: SlideSelector("Match Slide", i_parent), m_slide(new MatchSlide(i_round))
{
}

//TODO to boost::signals - signal results changed from Match itself
void b3m::gui::ey2023::MatchSlideSelector::updateScores()
{
	m_slide->updateScores();
}


//END OF FILE --------------------------------------------------------------------------------------