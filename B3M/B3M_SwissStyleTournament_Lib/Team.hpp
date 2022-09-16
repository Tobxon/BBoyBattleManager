#pragma once

#include "SwissStyleTournamentLibrary.h"

#include <string>
#include <ostream>

namespace b3m
{

class SSTLIBRARY_API Team
{
	using rating = unsigned int;

public:
	explicit Team(const std::string&, rating = 0);

	friend bool operator<(const Team& i_a, const Team& i_b) { return i_a.m_name < i_b.m_name; }

private:
	std::string m_name;
	const rating m_rating{0};
};

}
