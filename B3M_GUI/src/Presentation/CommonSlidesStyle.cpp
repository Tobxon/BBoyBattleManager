//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

//Qt
#include <QFontDatabase>


module b3m.gui.presentation;
import :CommonSlidesStyle;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//CommonSlidesStyle
QFont b3m::gui::presentation::SlidesStyle::getBackgroundFont() const
{
	return QFontDatabase::systemFont(QFontDatabase::TitleFont);
}

QFont b3m::gui::presentation::SlidesStyle::getForegroundFont() const
{
	return QFontDatabase::systemFont(QFontDatabase::FixedFont);
}


//END OF FILE --------------------------------------------------------------------------------------