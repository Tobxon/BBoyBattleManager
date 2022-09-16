#pragma once

#include "SwissStyleTournamentLibrary.h"

#include <vector>
#include <map>
#include <ostream>

#include "Team.hpp"

namespace b3m
{



class SSTLIBRARY_API Tournament
{
public:
	using rating = unsigned int;
	using teamName = std::string;

	bool addTeam(const teamName&, rating = 0);
	bool setCurSpot(const teamName&, std::size_t);
	//bool setRating(const teamName&, rating);

	std::size_t getNumOfTeams() { return m_teamNames.size(); }
	const std::vector<teamName>& getTeamNames() { return m_teamNames; }

#ifdef _DEBUG
	void printAllTeamNames(std::ostream&) const;
	void printTeamTable(std::ostream&) const;
#endif //_DEBUG

private:
	std::vector<teamName> m_teamNames;
	std::map<rating, std::vector<teamName>::const_iterator> m_ratingsOfTeams;
};

}
