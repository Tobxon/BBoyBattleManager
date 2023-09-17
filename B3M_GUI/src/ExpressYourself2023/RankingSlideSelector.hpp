//--------------------------------------------------------------------------------------------------
/**
 * \brief Class to make the RankingSlide available. RankingSlide is showing the currently registered
 *        teams and their ranking.
 *
 */

#ifndef B3M_GUI_EXPRESS_YOURSELF_2023_RANKING_SLIDE_SELECTOR_HPP
#define B3M_GUI_EXPRESS_YOURSELF_2023_RANKING_SLIDE_SELECTOR_HPP


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


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace Ui{ class SlideTemplate; }


namespace b3m::gui::ey2023
{



using b3m::gui::presentation::SlideSelector;
using b3m::common::SortedContestantsRanking;


class RankingSlide : public QWidget
{
public:
	explicit RankingSlide(const SortedContestantsRanking&, QWidget* = nullptr);
	~RankingSlide();

//public slots:
//	void updateTeamName();

private:
	Ui::SlideTemplate* m_ui;

	QList< QLabel* > m_teamNames;

	void arrangeTeamNames();
};


class RankingSlideSelector : public SlideSelector
{
	Q_OBJECT;

public:
	explicit RankingSlideSelector(const SortedContestantsRanking&, QWidget* = nullptr);

private:
	RankingSlide* m_slide{ nullptr };

private slots:
	QWidget* getSlide() override{ return m_slide; }
};



}


#endif //B3M_GUI_EXPRESS_YOURSELF_2023_RANKING_SLIDE_SELECTOR_HPP
//END OF FILE --------------------------------------------------------------------------------------