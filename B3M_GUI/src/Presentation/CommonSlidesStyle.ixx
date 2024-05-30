//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for common values for the style of all or multiple slides.
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
export module b3m.gui.presentation:CommonSlidesStyle;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::gui::presentation
{



class SlidesStyle
{
public:
	virtual ~SlidesStyle() = default;

	[[nodiscard]] QFont getBackgroundFont() const;
	[[nodiscard]] QFont getForegroundFont() const;

private:
	[[nodiscard]] virtual QFont getBackgroundFont_impl() const = 0;
	[[nodiscard]] virtual QFont getForegroundFont_impl() const = 0;
};



}


//END OF FILE --------------------------------------------------------------------------------------