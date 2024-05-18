//--------------------------------------------------------------------------------------------------
/**
 * \brief Class to make the RankingSlide available. RankingSlide is showing the currently registered
 *        teams and their ranking.
 *
 */

#ifndef B3M_GUI_EXPRESS_YOURSELF_2023_MATCH_SLIDE_SELECTOR_HPP
#define B3M_GUI_EXPRESS_YOURSELF_2023_MATCH_SLIDE_SELECTOR_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>
#include <QList>
#include <QLabel>

//b3m
#include <SlideSelector.hpp>
import b3m.common;
import b3m.gui.presentation;

using b3m::gui::presentation::SlidesStyle;


namespace Ui{ class SlideTemplate; }


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui::ey2023
{



using b3m::gui::presentation::SlideSelector;
using b3m::common::TournamentRound;
using b3m::common::Contestant;


class MatchSlide : public QWidget
{
	Q_OBJECT;

public:
	explicit MatchSlide(TournamentRound&, const b3m::gui::presentation::SlidesStyle&, const QString& = {}, QWidget* = nullptr);
	~MatchSlide();

protected:
	void paintEvent(QPaintEvent*);

private:
	Ui::SlideTemplate* m_ui;

	QList< QLabel* > m_teams;
	TournamentRound* m_round;
};


class MatchSlideSelector : public SlideSelector
{
	Q_OBJECT; //I#5 to boost::signals - signal results changed from Match itself

public:
	explicit MatchSlideSelector(TournamentRound&, const QString& = {}, QWidget* = nullptr);
	explicit MatchSlideSelector(TournamentRound&, QWidget* = nullptr);

private:
	MatchSlide* m_slide{ nullptr };

private slots:
	QWidget* getSlide() override{ return m_slide; }
};



}


#endif //B3M_GUI_EXPRESS_YOURSELF_2023_MATCH_SLIDE_SELECTOR_HPP
//END OF FILE --------------------------------------------------------------------------------------