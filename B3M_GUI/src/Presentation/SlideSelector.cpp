//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "SlideSelector.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------


b3m::gui::presentation::SlideSelector::SlideSelector(const char* i_buttonText, QWidget* i_parent)
	: QPushButton(i_parent)
{
	setEnabled(false);
	setText(tr(i_buttonText));

	connect(this, &QPushButton::clicked, [this](){ emit newSlide(getSlide()); });
}


//END OF FILE --------------------------------------------------------------------------------------