//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "TeamsView.hpp"

//std
//import <algorithm>;
#include <algorithm>


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
	: QAbstractListModel(parent), m_teams(readTeamsByRanking(i_participants))
{
	i_participants.registerCallback([this](const ParticipantsDepot& i_participantsSource){
		m_teams = readTeamsByRanking(i_participantsSource);

		const QModelIndex topLeft = createIndex(0,0);
		const QModelIndex bottomRight = createIndex(static_cast<int>(m_teams.size()),0);
		emit dataChanged(topLeft,bottomRight);
	});
}

int b3m::gui::TeamsModel::rowCount(const QModelIndex& parent) const
{
	return static_cast<int>(m_teams.size());
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

auto b3m::gui::readTeamsByRanking(const ParticipantsDepot& i_participantsSource) -> TeamsByRanking //TODO move everything that is possible to b3m::database
{
	TeamsByRanking o_teams;

	auto teamsWithRanking = b3m::database::readTeamsWithRanking(i_participantsSource);

	std::ranges::sort(teamsWithRanking, [](auto &left, auto &right) {
		return left.second > right.second;
	});
	//TODO sort by indices without copying - preferably as a template to create any kind of new container from it

	for(const auto& [teamName, teamRanking] : teamsWithRanking)
	{
		o_teams.emplace_back(QString::fromStdString(teamName));
	}

	return o_teams;
}


//END OF FILE --------------------------------------------------------------------------------------