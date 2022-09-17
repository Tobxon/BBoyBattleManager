#pragma once

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------

#include "SwissStyleTournamentLibrary.h"

//stl
#include <vector>
#include <map>

#include "TypesAndAliases.hpp"

//--------------------------------------------------------------------------------------------------
//Declarations                                                                                 -----
//--------------------------------------------------------------------------------------------------

namespace b3m
{
//namespace b3m ------------------------------------------------------------------------------------


class SSTLIBRARY_API MatchMaker
{
public:
	struct MatchingInfos {

	};

	virtual ~MatchMaker() = default;

	virtual std::vector< Match > createMatches(const std::vector< Contestant >&,
		const std::map< Ranking, std::vector< Contestant >::const_iterator >& = {}, 
		const MatchingInfos & = {}) = 0;
};


//end of namespace b3m -----------------------------------------------------------------------------
}
