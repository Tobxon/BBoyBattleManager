#include "pch.h"

#include <iostream>

#include "Tournament.hpp"

bool b3m::Tournament::addTeam(const teamName& i_toAdd, rating i_rating)
{
	if (!m_teamList.empty() && (std::find(m_teamList.begin(), m_teamList.end(), i_toAdd) != m_teamList.end()))
	{
		//Team already registered
		return false;
	}

	m_teamList.push_back(i_toAdd);

	return true;
}

#ifdef _DEBUG
void b3m::Tournament::printAllTeamNames(std::ostream& i_printSink) const
{
	i_printSink << "Alle Teams, die in diesem Turnier antreten:" << std::endl;

	for (const auto& l_teamName : m_teamList)
	{
		i_printSink << l_teamName << ", ";
	}
	i_printSink << std::endl;
}

#endif //_DEBUG