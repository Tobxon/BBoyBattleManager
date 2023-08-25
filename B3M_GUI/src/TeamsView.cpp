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
	: QListView(parent), m_model(new TeamsModel(i_participants, this))
{
	QListView::setModel(m_model);
}


//TeamsViewModel -----------------------------------------------------------------------------------
b3m::gui::TeamsModel::TeamsModel(ParticipantsDepot& i_participants, QObject* parent)
	: m_teams(/*readTeamsByRanking(i_participants)*/)
{
	i_participants.registerCallback([this](const ParticipantsDepot& i_participantsSource){
		m_teams = readTeamsByRanking(i_participantsSource);

		const QModelIndex topLeft = createIndex(0,0);
		const QModelIndex bottomRight = createIndex(m_teams.size(),0);
		emit dataChanged(topLeft,bottomRight);
	});
}

int b3m::gui::TeamsModel::rowCount(const QModelIndex& parent) const
{
//	const auto returnVal = m_teams.empty() ? 1 : m_teams.size();
//	return returnVal;
	return m_teams.size();
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

auto b3m::gui::readTeamsByRanking(const ParticipantsDepot&) -> TeamsByRanking
{
	TeamsByRanking o_teams{"testTeam1", "testTeam2", "testTeam3"};

	return o_teams;
}


//END OF FILE --------------------------------------------------------------------------------------