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
	: QWidget(i_parent), m_ui(new Ui::ParticipantsDialog()), 
	m_model(new ParticipantsDialogModel(this))
{
	m_ui->setupUi(this);

	m_ui->participantsTable->setModel(m_model);
}

b3m::gui::ParticipantsDialog::~ParticipantsDialog()
{
	delete m_ui;
}

b3m::gui::ParticipantsDialogModel::ParticipantsDialogModel(QObject* i_parent)
	: QAbstractTableModel(i_parent)
{
}

int b3m::gui::ParticipantsDialogModel::rowCount(const QModelIndex& i_parent) const
{
	return 10;
}

int b3m::gui::ParticipantsDialogModel::columnCount(const QModelIndex& i_parent) const
{
	return 4;
}

QVariant b3m::gui::ParticipantsDialogModel::data(const QModelIndex& i_index, int i_role) const
{
	if (i_role == Qt::DisplayRole)
	{
        if(m_participantsData.contains(i_index.row()) && m_participantsData.at(i_index.row()).contains(i_index.column()))
        {
            return m_participantsData.at(i_index.row()).at(i_index.column());
        }
	}
	return {};
}

bool b3m::gui::ParticipantsDialogModel::setData(const QModelIndex& i_index, const QVariant& i_value, int i_role)
{
    if (i_role == Qt::EditRole)
    {
        if (!checkIndex(i_index))
        {
            return false;
        }

        m_participantsData[i_index.row()].insert_or_assign(i_index.column(), i_value.toString());


        return true;
    }
    return false;
}

Qt::ItemFlags b3m::gui::ParticipantsDialogModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}


//END OF FILE --------------------------------------------------------------------------------------