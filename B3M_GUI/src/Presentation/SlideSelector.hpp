//--------------------------------------------------------------------------------------------------
/**
 * \brief TODO
 *
 */

#ifndef B3M_GUI_PRESENTATION_SLIDE_SELECTOR_HPP
#define B3M_GUI_PRESENTATION_SLIDE_SELECTOR_HPP


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QPushButton>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui::presentation
{



class SlideSelector : public QPushButton
{
	Q_OBJECT;

public:
	explicit SlideSelector(QWidget* = nullptr);

signals:
	void newSlide(QWidget*);

private slots:
	virtual QWidget* getSlide() = 0;
};



} //namespace b3m::gui::presentation


#endif //B3M_GUI_PRESENTATION_SLIDE_SELECTOR_HPP
//END OF FILE --------------------------------------------------------------------------------------