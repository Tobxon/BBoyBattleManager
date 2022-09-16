#pragma once

#include "SwissStyleTournamentLibrary.h"

#include <vector>
#include <ostream>

#include "Team.hpp"

namespace b3m
{



class SSTLIBRARY_API Tournament
{
	using rating = unsigned int;
	using teamName = std::string;

public:
	bool addTeam(const teamName&, rating = 0);

#ifdef _DEBUG
	void printAllTeamNames(std::ostream&) const;
#endif //_DEBUG

private:
	std::vector<teamName> m_teamList;
};

}
