//--------------------------------------------------------------------------------------------------
/**
 * \brief Class to make the RankingSlide available. RankingSlide is showing the currently registered
 *        teams and their ranking.
 *
 */

#ifndef B3M_GUI_EXPRESS_YOURSELF_2023_DETAILED_RANKING_SLIDE_SELECTOR_HPP
#define B3M_GUI_EXPRESS_YOURSELF_2023_DETAILED_RANKING_SLIDE_SELECTOR_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>
#include <QList>
#include <QLabel>

//b3m
#include <SlideSelector.hpp>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace Ui{ class SlideTemplate; }


namespace b3m::gui::ey2023
{



using b3m::gui::presentation::SlideSelector;


class DetailedRankingSlide : public QWidget
{
public:
	explicit DetailedRankingSlide(QWidget* = nullptr);
	~DetailedRankingSlide();

//public slots:
//	void updateTeamName();

private:
	Ui::SlideTemplate* m_ui;

	QList< QLabel* > m_teamNames;

	void arrangeTeamNames();
};


class DetailedRankingSlideSelector : public SlideSelector
{
	Q_OBJECT;

public:
	explicit DetailedRankingSlideSelector(QWidget* = nullptr);

private:
	DetailedRankingSlide* m_slide{ new DetailedRankingSlide };

private slots:
	QWidget* getSlide() override{ return m_slide; }
};



}


#endif //B3M_GUI_EXPRESS_YOURSELF_2023_DETAILED_RANKING_SLIDE_SELECTOR_HPP
//END OF FILE --------------------------------------------------------------------------------------