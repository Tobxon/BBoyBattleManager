//--------------------------------------------------------------------------------------------------
/**
 * \brief SlideSelector for the startup slide which is basically just showing an image.
 *
 */

#ifndef B3M_GUI_EXPRESS_YOURSELF_2023_STARTUP_SLIDE_HPP
#define B3M_GUI_EXPRESS_YOURSELF_2023_STARTUP_SLIDE_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QLabel>

//b3m
#include <SlideSelector.hpp>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui::ey2023
{



using b3m::gui::presentation::SlideSelector;


class StartupSlideSelector : public SlideSelector
{
public:
	explicit StartupSlideSelector(QWidget* = nullptr);

private:
	QLabel* m_startupImage{ new QLabel };

private slots:
	QWidget* getSlide() override;
};



}; //namespace b3m::gui::ey2023


#endif //B3M_GUI_EXPRESS_YOURSELF_2023_STARTUP_SLIDE_HPP
//END OF FILE --------------------------------------------------------------------------------------