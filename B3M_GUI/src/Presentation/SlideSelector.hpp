//--------------------------------------------------------------------------------------------------
/**
 * \brief Base Class for the objects that manage a slide used in the presentation (e.g. on a beamer
 *        somewhere in the event location).
 *        Inherit from this class and hand out your custom type of slide on getSlide to add your own
 *        slide to the tournament presentation.
 *
 */

#ifndef B3M_GUI_PRESENTATION_SLIDE_SELECTOR_HPP
#define B3M_GUI_PRESENTATION_SLIDE_SELECTOR_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QPushButton>
#include <QString>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui::presentation
{



class SlideSelector : public QPushButton
{
	Q_OBJECT;

public:
	explicit SlideSelector(const char*, QWidget* = nullptr);

signals:
	void newSlide(QWidget*);

private slots:
	virtual QWidget* getSlide() = 0;
};



} //namespace b3m::gui::presentation


#endif //B3M_GUI_PRESENTATION_SLIDE_SELECTOR_HPP
//END OF FILE --------------------------------------------------------------------------------------