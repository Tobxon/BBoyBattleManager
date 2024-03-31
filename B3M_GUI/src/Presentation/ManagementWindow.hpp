//--------------------------------------------------------------------------------------------------
/**
 * \brief The PresentationManagementWindow is the Widget which is used as a controller to the
 *        presentation that most likely will be on another screen (e.g. projected by a beamer)
 *
 */

#ifndef B3M_GUI_PRESENTATION_MANAGEMENT_WINDOW_HPP
#define B3M_GUI_PRESENTATION_MANAGEMENT_WINDOW_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>
#include <QList>

#include "ui_PresentationManagementWindow.h"

//b3m
#include <SlideSelector.hpp>
import b3m.common;

namespace b3m::gui{ class TournamentRoundWidget; } //I#5 to boost::signals - signal results changed from Match itself

//ey2023
#include <StartupSlideSelector.hpp>
#include <RankingSlideSelector.hpp>
#include <MatchSlideSelector.hpp>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::gui::presentation::SlideSelector;
using b3m::common::TournamentRound;
using b3m::common::Contestant;
using b3m::common::ContestantsRanking;


class PresentationManagementWindow : public QWidget
{
	Q_OBJECT;

public:
	explicit PresentationManagementWindow(QWidget* = nullptr);
	virtual ~PresentationManagementWindow();

public slots:
	void addSlideFor(TournamentRound&, const TournamentRoundWidget&); //I#5 to boost::signals - signal results changed from Match itself
	void newRanking(const ContestantsRanking&);

signals:
	void slidesVisible(bool);

private:
	Ui::PresentationManagementWindow* m_ui{ new Ui::PresentationManagementWindow };

	QWidget* m_presentationWindow{ new QWidget };
	qsizetype m_presentationWindowScreeIndex{ 1%(QGuiApplication::screens().size()) }; //use second screen on start

	QList< SlideSelector* > m_slides{ new b3m::gui::ey2023::StartupSlideSelector };
	SlideSelector* m_curSlide{ nullptr };

	void initializeScreen();
	void setNewSlide(QWidget*);

	void addNewSlide(SlideSelector&);
	void initializeSlide(SlideSelector&);
};



} //namespace b3m::gui


#endif //B3M_GUI_PRESENTATION_MANAGEMENT_WINDOW_HPP
//END OF FILE --------------------------------------------------------------------------------------