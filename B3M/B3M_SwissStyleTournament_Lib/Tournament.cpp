#include "pch.h"

#include <map>
#include <iostream>

#include "Tournament.hpp"
#include "sst_functions.h"


bool b3m::Tournament::addTeam(const TeamName& i_toAdd, rating i_rating)
{
	if (!m_teamNames.empty() && (std::find(m_teamNames.begin(), m_teamNames.end(), i_toAdd) != m_teamNames.end()))
	{
		//Team already registered
		return false;
	}

	m_teamNames.push_back(i_toAdd);

	return true;
}

bool b3m::Tournament::setCurSpot(const TeamName& i_teamName, std::size_t i_spotToSet)
{
	auto l_it = std::find(m_teamNames.begin(), m_teamNames.end(), i_teamName);
	if (l_it == m_teamNames.end())
	{
		return false;
	}

	if (m_ratingsOfTeams.contains(i_spotToSet-1))
	{
		return false;
	}

	m_ratingsOfTeams.emplace(i_spotToSet-1, l_it);
	return true;
}


std::map<b3m::MatchId, b3m::Match> b3m::Tournament::createCurMatches()
{
	std::map<MatchId, Match> r_matches;

	std::map < std::vector<TeamName>::const_iterator, bool > l_takenTeams;
	for (auto l_it = m_teamNames.begin(); l_it != m_teamNames.end(); ++l_it)
	{
		l_takenTeams.emplace(l_it, false);
	}
	//TODO if history is empty
	for (auto l_teamNameIt = m_teamNames.begin(); l_teamNameIt != m_teamNames.end(); ++l_teamNameIt)
	{
		if (l_takenTeams.at(l_teamNameIt) == true)
		{
			continue;
		}

		std::string l_opponentName;

		if (m_history.empty())
		{
			l_opponentName = b3m::sst::findFirstMatchOpponent(l_teamNameIt, m_ratingsOfTeams);
		}
		else
		{
			//TODO
		}

		if (l_opponentName == "")
		{
			//TODO free point
			continue;
		}

		r_matches.emplace(createNewUniqueId(), Match(*l_teamNameIt, l_opponentName));
	}

	return r_matches;
}

bool b3m::Tournament::finishMatch(const MatchId& i_id, const Match& i_match, const Result& i_result, unsigned int i_roundId)
{
	//check if Match is already finished
	for (const auto& l_matchRecord : m_history)
	{
		if (l_matchRecord.getId() == i_id)
		{
			return false;
		}
	}

	//add points for winner
	{
		const auto l_winner = b3m::sst::decideWinner(i_match, i_result);

		if (l_winner == "")
		{

		}
		else
		{
			const auto l_winnerIt = std::find(m_teamNames.begin(), m_teamNames.end(), l_winner);
			++m_TeamPoints[l_winnerIt];
			//TODO update rating
		}
	}

	m_history.emplace_back(i_id, i_match, i_result, i_roundId, this);

	return true;
}


#ifdef _DEBUG
void b3m::Tournament::printAllTeamNames(std::ostream& i_printSink) const
{
	i_printSink << "Alle Teams, die in diesem Turnier antreten:" << std::endl;

	for (const auto& l_teamName : m_teamNames)
	{
		i_printSink << l_teamName << ", ";
	}
	i_printSink << std::endl;
}

void b3m::Tournament::printTeamTable(std::ostream& i_printSink) const
{
	i_printSink << "current tournament table:" << std::endl;

	for (const auto& l_entry : m_ratingsOfTeams)
	{
		i_printSink << (l_entry.first+1) << ".\t- " << *l_entry.second << std::endl;
	}
}
#endif //_DEBUG

//free functions
std::vector<b3m::TeamName> b3m::getPastOpponents(const Tournament::MatchHistory& i_history, const TeamName& i_team)
{
	std::vector<b3m::TeamName> r_opponentList;

	for (const auto& l_matchRecord : i_history)
	{
		const auto l_checkRes = l_matchRecord.wasContestant(i_team);

		if (l_checkRes.first)
		{
			r_opponentList.push_back(l_checkRes.second);
		}
	}

	return r_opponentList;
}



//MatchRecord
b3m::MatchRecord::MatchRecord(const MatchId& i_id, const Match& i_match, const Result& i_res, unsigned int i_roundId, Tournament* i_pTournament)
	: m_id(i_id), m_contestants(i_match), m_result(i_res), m_roundId(i_roundId), m_pTournament(i_pTournament)
{
}

std::pair<bool, b3m::TeamName> b3m::MatchRecord::wasContestant(const TeamName& i_team) const
{
	if (m_contestants.first == i_team)
	{
		return std::make_pair(true, m_contestants.second);
	}
	else if (m_contestants.second == i_team)
	{
		return std::make_pair(true, m_contestants.first);
	}
	else
	{
		return std::make_pair(false, "");
	}
}
