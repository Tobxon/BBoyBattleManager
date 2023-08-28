//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "TeamsView.hpp"

//std
import <algorithm>;
import <ranges>;
import <vector>;
import <functional>;

//b3m
import b3m.common;


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
	: QAbstractListModel(parent)
	, m_teams(getTeamNamesSortedByRating(i_participants))
{
	i_participants.registerCallback([this](const ParticipantsDepot& i_participantsSource){
		m_teams = getTeamNamesSortedByRating(i_participantsSource);

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

auto b3m::gui::getTeamNamesSortedByRating(const ParticipantsDepot& i_participantsSource) -> TeamsByRanking
{
	TeamsByRanking o_sortedTeamNames;

	const auto teams = b3m::database::readTeams(i_participantsSource);

	{
		std::vector< std::reference_wrapper< const decltype(teams)::value_type >> teamsProj( teams.begin(), teams.end() );

		std::ranges::sort(teamsProj, [](const b3m::common::Team& i_a, const b3m::common::Team& i_b){
			return i_a.getRating() > i_b.getRating();
		});

		for(const b3m::common::Team& team : teamsProj)
		{
			o_sortedTeamNames.emplace_back(QString::fromStdString(team.getName()));
		}
	}

	return o_sortedTeamNames;
}


//END OF FILE --------------------------------------------------------------------------------------