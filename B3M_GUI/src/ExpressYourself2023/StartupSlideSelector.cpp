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
	: SlideSelector(i_parent)
{
	setObjectName("pushButton");
	setEnabled(false);
	setText(tr("Startup Slide"));

	QPixmap mainImage("D:/Dev/Repos/B3M_dev/EY2023/resources/B3M_EY2023-start_page.png");
	m_startupImage->setPixmap(mainImage);
}

QWidget* b3m::gui::ey2023::StartupSlideSelector::getSlide()
{
	return m_startupImage;
}


//END OF FILE --------------------------------------------------------------------------------------