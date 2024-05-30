//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "StartupSlideSelector.hpp"

//Qt
#include <QPixmap>
#include <QPushButton>


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::ey2023::StartupSlideSelector::StartupSlideSelector(QWidget* i_parent)
	: SlideSelector("Startup Slide", i_parent)
{
	m_startupImage->setPixmap(QPixmap(":/images/B3M_EY2023-start_page.png"));
}

QWidget* b3m::gui::ey2023::StartupSlideSelector::getSlide()
{
	return m_startupImage;
}


//END OF FILE --------------------------------------------------------------------------------------