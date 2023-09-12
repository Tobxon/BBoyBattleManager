//--------------------------------------------------------------------------------------------------
/**
 * \brief TODO
 *
 */

#ifndef B3M_GUI_PRESENTATION_MANAGEMENT_WINDOW_HPP
#define B3M_GUI_PRESENTATION_MANAGEMENT_WINDOW_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>

#include "ui_PresentationManagementWindow.h"

//b3m
#include <SlideSelector.hpp>

//ey2023
#include <StartupSlideSelector.hpp>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



class PresentationManagementWindow : public QWidget
{
	Q_OBJECT;

public:
	explicit PresentationManagementWindow(QWidget* = nullptr);
	virtual ~PresentationManagementWindow();

signals:
	void slidesVisible(bool);

private:
	Ui::PresentationManagementWindow* m_ui{ new Ui::PresentationManagementWindow };

	QWidget* m_presentationWindow{ new QWidget };
	qsizetype m_presentationWindowScreeIndex{ 1%(QGuiApplication::screens().size()) }; //use second screen on start

	b3m::gui::presentation::SlideSelector* m_startup{ new b3m::gui::ey2023::StartupSlideSelector };

	void initializeScreen();
	void setNewSlide(QWidget*);
};



} //namespace b3m::gui


#endif //B3M_GUI_PRESENTATION_MANAGEMENT_WINDOW_HPP
//END OF FILE --------------------------------------------------------------------------------------