#include "pch.h"

#include <iostream>

#include "Tournament.hpp"

bool b3m::Tournament::addTeam(const teamName& i_toAdd, rating i_rating)
{
	if (!m_teamNames.empty() && (std::find(m_teamNames.begin(), m_teamNames.end(), i_toAdd) != m_teamNames.end()))
	{
		//Team already registered
		return false;
	}

	m_teamNames.push_back(i_toAdd);

	return true;
}

bool b3m::Tournament::setCurSpot(const teamName& i_teamName, std::size_t i_spotToSet)
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