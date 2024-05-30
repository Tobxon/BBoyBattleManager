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
	try
	{
		return getBackgroundFont_impl();
	}
	catch(...)
	{
		return QFontDatabase::systemFont(QFontDatabase::TitleFont);
	}
}

QFont b3m::gui::presentation::SlidesStyle::getForegroundFont() const
{
	try
	{
		return getForegroundFont_impl();
	}
	catch (...)
	{
		return QFontDatabase::systemFont(QFontDatabase::FixedFont);
	}
}


//END OF FILE --------------------------------------------------------------------------------------