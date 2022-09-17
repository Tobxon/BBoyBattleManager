#pragma once

#include "SwissStyleTournamentLibrary.h"

#include <ostream>
#include <string>
#include <unordered_set>

#include "Tournament.hpp"

namespace b3m
{



MatchId createNewUniqueId();

namespace sst
{

void SSTLIBRARY_API testPrint(std::ostream&);
std::string SSTLIBRARY_API returnHelloWorld();

TeamName findFirstMatchOpponent(const std::vector<TeamName>::const_iterator& i_ownName, const std::map<Tournament::spot, std::vector<TeamName>::const_iterator>& i_teamsByRating);

}

}

template <class IntegerType>
constexpr IntegerType divideUintRoundUp(const IntegerType& dividend, const IntegerType& divisor)
{
    return (divisor == 0) ? 0 : (dividend / divisor) + (dividend % divisor != 0);
}