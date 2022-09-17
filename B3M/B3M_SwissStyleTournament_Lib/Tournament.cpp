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

		const std::string l_opponentName = b3m::sst::findFirstMatchOpponent(l_teamNameIt, m_ratingsOfTeams);

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



//MatchRecord
b3m::MatchRecord::MatchRecord(const MatchId& i_id, const Match& i_match, const Result& i_res, unsigned int i_roundId, Tournament* i_pTournament)
	: m_id(i_id), m_contestants(i_match), m_result(i_res), m_roundId(i_roundId), m_pTournament(i_pTournament)
{
}