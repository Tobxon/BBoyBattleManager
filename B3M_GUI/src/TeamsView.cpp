//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "TeamsView.hpp"


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//TeamsView ----------------------------------------------------------------------------------------
b3m::gui::TeamsView::TeamsView(ParticipantsDepot& i_participants, QWidget* parent)
	: m_model(new TeamsModel(i_participants, this))
{
	QListView::setModel(m_model);
}


//TeamsViewModel -----------------------------------------------------------------------------------
b3m::gui::TeamsModel::TeamsModel(ParticipantsDepot& i_participants, QObject* parent)
	: m_teams()
	, m_teamsSource(i_participants, m_teams,
					[](const std::string& i_string){ return QString::fromStdString(i_string);})
{
}

int b3m::gui::TeamsModel::rowCount(const QModelIndex& parent) const
{
	return m_teams.empty() ? 1 : m_teams.size();
}

QVariant b3m::gui::TeamsModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if(index.column() == 0 && index.row() < m_teams.size())
		{
			return m_teams.at(index.row());
		}
	}
	return {};
}

//END OF FILE --------------------------------------------------------------------------------------