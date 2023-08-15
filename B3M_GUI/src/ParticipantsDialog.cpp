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

//ParticipantsDialogModel --------------------------------------------------------------------------
b3m::gui::ParticipantsDialogModel::ParticipantsDialogModel(QObject* i_parent)
	: QAbstractTableModel(i_parent)
    , m_participantAttributeTitles({{0, "name"},{1, "crew"},{2,"city"}})
{
    //TODO initialize gui data with data from i_partContainer
}

int b3m::gui::ParticipantsDialogModel::rowCount(const QModelIndex& i_parent) const
{
	return 10;
}

int b3m::gui::ParticipantsDialogModel::columnCount(const QModelIndex& i_parent) const
{
	return static_cast<int>(m_participantAttributeTitles.size());
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

        const auto value = i_value.toString();
        if(!value.isEmpty()) {
            auto mapResult = m_participantsData[i_index.row()].insert_or_assign(i_index.column(), i_value.toString());

            //TODO inform participants database about the change made to participant or the introduction of a new
            const auto indexOfNameAttribute = std::ranges::find_if(m_participantAttributeTitles,
                                                                   [this](const auto &element) {
                                                                       return element.second == nameAttribute;
                                                                   })->first;

            if (i_index.column() == indexOfNameAttribute && mapResult.second) //new participant
            {
                const auto newPart = i_value.toString().toStdString();
                emit newParticipant(newPart);
                //TODO report already registered attributes
            } else {
                if (m_participantsData.at(i_index.row()).contains(indexOfNameAttribute)) {
                    const auto &name = m_participantsData.at(i_index.row()).at(indexOfNameAttribute).toStdString();
                    const auto &attribute = m_participantAttributeTitles.at(i_index.column()).toStdString();
                    const auto &attributeVal = i_value.toString().toStdString();
                    emit participantUpdated(name, attribute, attributeVal);
                }
            }

            return true;
        }
    }
    return false;
}

Qt::ItemFlags b3m::gui::ParticipantsDialogModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

QVariant b3m::gui::ParticipantsDialogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if(m_participantAttributeTitles.contains(section))
        {
            return m_participantAttributeTitles.at(section);
        }
    }
    return {};
}


//END OF FILE --------------------------------------------------------------------------------------