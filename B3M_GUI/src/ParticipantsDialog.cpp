//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "ParticipantsDialog.hpp"

//std
#include <algorithm>
#include <ranges>


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//ParticipantsDialog -------------------------------------------------------------------------------
b3m::gui::ParticipantsDialog::ParticipantsDialog(b3m::database::ParticipantsDepot& i_participantsStorage, QWidget* const i_parent)
		: QWidget(i_parent), m_ui(new Ui::ParticipantsDialog()),
			m_model(new ParticipantsDialogModel(i_participantsStorage, this))
{
	m_ui->setupUi(this);

	m_ui->participantsTable->setModel(m_model);
}

b3m::gui::ParticipantsDialog::~ParticipantsDialog()
{
	delete m_ui;
}

//ParticipantsDialogModel --------------------------------------------------------------------------
b3m::gui::ParticipantsDialogModel::ParticipantsDialogModel(b3m::database::ParticipantsDepot& i_participantsStorage, QObject* i_parent)
	: QAbstractTableModel(i_parent)
	, m_participantAttributeTitles({{0, b3m::common::nameAttribute},{1, b3m::common::teamAttribute},{2,"city"},{3,b3m::common::rankingPointsAttribute}})
	, m_participantsStorage(&i_participantsStorage)
{
	std::size_t partIndex{0};
	for(const auto& [participant, partAttributes] : i_participantsStorage)
	{
		const auto partQt = QString::fromStdString(participant);

		//TODO check if participant is created already and get index from this

		const auto nameAttrIndex =
				std::ranges::find_if(m_participantAttributeTitles,
									 [attrQt = b3m::common::nameAttribute](const auto& mapEle)
									 { return mapEle.second == attrQt; })->first; //TODO to b3m::util

		m_participantsData[partIndex].insert_or_assign(nameAttrIndex, partQt);

		for(const auto& [attribute, attrData] : partAttributes)
		{
			const auto attrQt = QString::fromStdString(attribute);
			const auto attrDataQt = QString::fromStdString(attrData);

			const auto searchAttrResult =
					std::ranges::find_if(m_participantAttributeTitles,
										 [attrQt](const auto& mapEle)
										 { return mapEle.second == attrQt; }); //TODO to b3m::util

			if(searchAttrResult != m_participantAttributeTitles.end())
			{
				const auto attrIndex = searchAttrResult->first;
				m_participantsData[partIndex].insert_or_assign(attrIndex, attrDataQt);
			} else{
				const auto newAttributeIndex = m_participantAttributeTitles.rbegin()->first+1;
				m_participantAttributeTitles.insert_or_assign(newAttributeIndex, attrQt);
				m_participantsData[partIndex].insert_or_assign(newAttributeIndex, attrDataQt);
			}
		}
		++partIndex;
	}
}

int b3m::gui::ParticipantsDialogModel::rowCount(const QModelIndex& i_parent) const
{
	return 100;
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

		const auto indexOfNameAttribute = std::ranges::find_if(m_participantAttributeTitles,
																[](const auto &element) {
																	return element.second == nameAttribute;
																})->first;

		const auto value = i_value.toString();
		if(!value.isEmpty()) //something is set
		{
			if(i_index.column() == indexOfNameAttribute) //name is set
			{
				const auto& newPartName = i_value.toString().toStdString();

				if(m_participantsData.contains(i_index.row()) && m_participantsData.at(i_index.row()).contains(i_index.column())) //renaming
				{
					const auto& prevName = m_participantsData.at(i_index.row()).at(i_index.column()).toStdString();

					m_participantsData.at(i_index.row()).insert_or_assign(i_index.column(), i_value.toString());

					//report updated participants name
					m_participantsStorage->updateParticipantsAttributes(prevName, b3m::common::nameAttribute, newPartName);
				} else { //new participant
					m_participantsData[i_index.row()].insert_or_assign(i_index.column(), i_value.toString());

					//get already registered attributes
					std::map< std::string, std::string > newPartAttributes;
					for(const auto& [attributeIndex, attributeData] : m_participantsData.at(i_index.row()))
					{
						const auto& curAttribute = m_participantAttributeTitles.at(attributeIndex);
						if(curAttribute != nameAttribute)
						{
							newPartAttributes.try_emplace(curAttribute.toStdString(), attributeData.toStdString());
						}
					}

					//report new participant
					m_participantsStorage->newParticipant(newPartName, newPartAttributes);
				}
			} else {
				m_participantsData[i_index.row()].insert_or_assign(i_index.column(), i_value.toString());

				if (m_participantsData.at(i_index.row()).contains(indexOfNameAttribute))
				{
					const auto& name = m_participantsData.at(i_index.row()).at(indexOfNameAttribute).toStdString();
					const auto& attribute = m_participantAttributeTitles.at(i_index.column()).toStdString();
					const auto& attributeVal = i_value.toString().toStdString();

					//update participant
					m_participantsStorage->updateParticipantsAttributes(name, attribute, attributeVal);
				}
			}

			return true;
		}
		else
		{
			if(m_participantsData.contains(i_index.row()) && m_participantsData.at(i_index.row()).contains(i_index.column())) //something was removed
			{
				auto& curParticipantsAttributes = m_participantsData.at(i_index.row());

				if (i_index.column() == indexOfNameAttribute) //remove participant
				{
					const auto& oldParticipantsName = curParticipantsAttributes.at(indexOfNameAttribute).toStdString();
					curParticipantsAttributes.at(indexOfNameAttribute).clear();

					m_participantsStorage->removeParticipant(oldParticipantsName);
				} else { //remove attribute
					curParticipantsAttributes.at(i_index.column()).clear();
					if(curParticipantsAttributes.contains(indexOfNameAttribute))
					{
						const auto& participantsName = curParticipantsAttributes.at(indexOfNameAttribute).toStdString();
						const auto& attributeToRemove = m_participantAttributeTitles.at(i_index.column()).toStdString();

						m_participantsStorage->removeParticipantsAttribute(participantsName, attributeToRemove);
					}
				}

				return true;
			}
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