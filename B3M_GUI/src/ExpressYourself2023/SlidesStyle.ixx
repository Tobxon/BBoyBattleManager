//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for slides style.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

//Qt
#include <QFont>


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.gui.ey2023:SlidesStyle;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
import b3m.gui.presentation;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::gui::ey2023
{



class SlidesStyle : public b3m::gui::presentation::SlidesStyle
{
public:
	[[nodiscard]] QFont getBackgroundFont() const override;
	[[nodiscard]] QFont getForegroundFont() const override;
};



}


//END OF FILE --------------------------------------------------------------------------------------