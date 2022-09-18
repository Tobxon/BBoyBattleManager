#pragma once

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------

#include "SwissStyleTournamentLibrary.h"

//b3m
#include "MatchMaker.hpp"
#include "Score.hpp"
#include "Tournament.hpp"

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
			i_ScoreOfContestants, const std::vector< Tournament::Round >& i_history = {}) 
			: m_ScoreOfContestants(i_ScoreOfContestants), m_history(i_history) {}
		//SwissStyleMatchingInfos(const std:.vector< Contestant >& i_contants, const Tournament& i_tournament); //TODO define this constructor

		std::map< std::vector< Contestant >::const_iterator, Score > m_ScoreOfContestants;
		std::vector< Tournament::Round > m_history;
	};

	std::vector< Match > createMatches(const std::vector< Contestant >&,
		const std::map< Ranking, std::vector< Contestant >::const_iterator > & = {},
		const MatchingInfos & = {}) override;
};


//end of namespace b3m -----------------------------------------------------------------------------
}