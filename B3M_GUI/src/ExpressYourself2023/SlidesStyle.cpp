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
	//TODO if font file not found return common style font
	int idFreshmaker = QFontDatabase::addApplicationFont("E:/Dev/Repos/B3M_dev/EY2023/resources/freshmarker.ttf"); //TODO to relative path
	QString familyFreshmaker = QFontDatabase::applicationFontFamilies(idFreshmaker).at(0);
	return QFont{ familyFreshmaker };
}

QFont b3m::gui::ey2023::SlidesStyle::getForegroundFont() const
{
	//TODO if font file not found return common style font
	int idBerlinSans = QFontDatabase::addApplicationFont("E:/Dev/Repos/B3M_dev/EY2023/resources/BRLNSB.ttf"); //TODO to relative path
	QString familyBerlinSans = QFontDatabase::applicationFontFamilies(idBerlinSans).at(0);
	return QFont{ familyBerlinSans };
}


//END OF FILE --------------------------------------------------------------------------------------