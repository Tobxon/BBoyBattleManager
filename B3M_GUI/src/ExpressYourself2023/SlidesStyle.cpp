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
		int idFreshmaker = QFontDatabase::addApplicationFont(":/fonts/freshmarker.ttf");
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
		int idBerlinSans = QFontDatabase::addApplicationFont(":/fonts/BRLNSB.TTF");
		QString familyBerlinSans = QFontDatabase::applicationFontFamilies(idBerlinSans).at(0);
		return QFont{familyBerlinSans};
	}
	catch(...)
	{
		return b3m::gui::presentation::SlidesStyle::getForegroundFont();
	}
}


//local initializer needed to force the compiler to integrate resources into the library binary
namespace
{
struct libraryInitializer {
	libraryInitializer() { Q_INIT_RESOURCE(ey2023_presentation); }
};

libraryInitializer resource_library_Initializer;
}


//END OF FILE --------------------------------------------------------------------------------------