//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "ParticipantsDialog.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::ParticipantsDialog::ParticipantsDialog(QWidget* const i_parent)
	: QWidget(i_parent), m_ui(new Ui::ParticipantsDialog())
{
	m_ui->setupUi(this);
}

b3m::gui::ParticipantsDialog::~ParticipantsDialog()
{
	delete m_ui;
}

 //END OF FILE --------------------------------------------------------------------------------------