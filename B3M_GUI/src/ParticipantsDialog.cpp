//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "ParticipantsDialog.hpp"

//std
#include <algorithm>

//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//ParticipantsDialog -------------------------------------------------------------------------------
b3m::gui::ParticipantsDialog::ParticipantsDialog(participantsContainer& i_container, 
	QWidget* const i_parent)
	: QWidget(i_parent), m_ui(new Ui::ParticipantsDialog()), 
	m_model(new ParticipantsDialogModel(i_container, this))
{
	m_ui->setupUi(this);

	m_ui->participantsTable->setModel(m_model);
}

b3m::gui::ParticipantsDialog::~ParticipantsDialog()
{
	delete m_ui;
}

//ParticipantsDialogModel --------------------------------------------------------------------------
b3m::gui::ParticipantsDialogModel::ParticipantsDialogModel(participantsContainer& i_container, 
	QObject* const i_parent)
	: QAbstractTableModel(i_parent), m_data(&i_container), m_header({ nameTitle, "City", "Crew"})
{
}

int b3m::gui::ParticipantsDialogModel::rowCount(const QModelIndex& i_parent) const
{
	return 2;
}

int b3m::gui::ParticipantsDialogModel::columnCount(const QModelIndex& i_parent) const
{
	return 3;
}

QVariant b3m::gui::ParticipantsDialogModel::data(const QModelIndex& i_index, int i_role) const
{
	if (i_role == Qt::DisplayRole)
	{
		//TODO connection to actual data
		return QString("row%1, col%2").arg(i_index.row() + 1).arg(i_index.column() + 1);
	}
	return QVariant();
}

QVariant b3m::gui::ParticipantsDialogModel::headerData(int i_section, Qt::Orientation i_orientation,
	int i_role) const
{
	if (i_role == Qt::DisplayRole && i_orientation == Qt::Horizontal)
	{
		if (i_section < m_header.size())
		{
			return m_header.at(i_section);
		}
		else
		{
			return ".....";
		}
	}
	return QVariant();
}

bool b3m::gui::ParticipantsDialogModel::setData(const QModelIndex& i_index, const QVariant& i_value, int i_role)
{
	if (i_role == Qt::EditRole)
	{
		if (!checkIndex(i_index))
		{
			return false;
		}

		auto nameColIndexIt = std::ranges::find(m_header, nameTitle);
		if (nameColIndexIt != m_header.cend())
		{
			QModelIndex curParticipantNameIndex = createIndex(i_index.row(), nameColIndexIt - m_header.cbegin());

			const QString curParticipantName = data(curParticipantNameIndex).toString();

			//TODO
			m_data->setAttributeOfParticipant(curParticipantName.toStdString(), headerData(i_index.column(), Qt::Horizontal, Qt::DisplayRole).toString().toStdString(), i_value.toString().toStdString());

			return true;
		}
		//TODO else?
	}

	return false;
}

Qt::ItemFlags b3m::gui::ParticipantsDialogModel::flags(const QModelIndex& i_index) const
{
	return Qt::ItemIsEditable | QAbstractTableModel::flags(i_index);
}


//END OF FILE --------------------------------------------------------------------------------------