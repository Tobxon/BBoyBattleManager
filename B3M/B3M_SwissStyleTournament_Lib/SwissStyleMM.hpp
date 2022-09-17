#pragma once

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------

#include "SwissStyleTournamentLibrary.h"

//b3m
#include "MatchMaker.hpp"
#include "Score.hpp"

//--------------------------------------------------------------------------------------------------
//Declarations                                                                                 -----
//--------------------------------------------------------------------------------------------------

namespace b3m
{
//namespace b3m ------------------------------------------------------------------------------------


class SSTLIBRARY_API SwissStyleMM : public MatchMaker
{
public:
	struct SwissStyleMatchingInfos : public MatchingInfos
	{
		SwissStyleMatchingInfos() = delete;
		SwissStyleMatchingInfos(const std::map< std::vector< Contestant >::const_iterator, Score >& 
			i_ScoreOfContestants)	: m_ScoreOfContestants(i_ScoreOfContestants) {}

		std::map< std::vector< Contestant >::const_iterator, Score > m_ScoreOfContestants;
	};

	std::vector< Match > createMatches(const std::vector< Contestant >&,
		const std::map< Ranking, std::vector< Contestant >::const_iterator > & = {},
		const MatchingInfos & = {}) override;
};


//end of namespace b3m -----------------------------------------------------------------------------
}