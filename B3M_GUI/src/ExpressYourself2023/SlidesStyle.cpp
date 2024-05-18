//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

//Qt
#include <QFontDatabase>
#include <QString>
#include <QList>


module b3m.gui.ey2023;
import :SlidesStyle;

//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

QFont b3m::gui::ey2023::SlidesStyle::getBackgroundFont() const
{
	try
	{
		int idFreshmaker = QFontDatabase::addApplicationFont("C:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf"); //I#10 portable resource file management
		QString familyFreshmaker = QFontDatabase::applicationFontFamilies(idFreshmaker).at(0);
		return QFont{familyFreshmaker};
	}
	catch(...)
	{
		return b3m::gui::presentation::SlidesStyle::getBackgroundFont();
	}
}

QFont b3m::gui::ey2023::SlidesStyle::getForegroundFont() const
{
	try
	{
		int idBerlinSans = QFontDatabase::addApplicationFont("C:/Dev/Repos/B3M_dev/EY2023/resources/BRLNSB.ttf"); //I#10 portable resource file management
		QString familyBerlinSans = QFontDatabase::applicationFontFamilies(idBerlinSans).at(0);
		return QFont{familyBerlinSans};
	}
	catch(...)
	{
		return b3m::gui::presentation::SlidesStyle::getForegroundFont();
	}
}


//END OF FILE --------------------------------------------------------------------------------------