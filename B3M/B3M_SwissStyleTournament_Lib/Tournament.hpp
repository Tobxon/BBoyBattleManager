#pragma once

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------
#include "SwissStyleTournamentLibrary.h"

//stl
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <optional>

//b3m
#include "TypesAndAliases.hpp"
#include "Score.hpp"
#include "MatchMaker.hpp"


//--------------------------------------------------------------------------------------------------
//Declarations                                                                                 -----
//--------------------------------------------------------------------------------------------------

//error type with error msg
//using error = std::pair< bool, std::optional<std::string> >; 

namespace b3m
{
//namespace b3m ------------------------------------------------------------------------------------


class SSTLIBRARY_API Tournament
{
public:
	class Round;

	Tournament() = delete;
	explicit Tournament(std::unique_ptr < MatchMaker >);
	//explicit Tournament(std::shared_ptr < MatchMaker >);
	Tournament(std::unique_ptr < MatchMaker >, const std::vector< Contestant >&);
	//Tournament(std::shared_ptr < MatchMaker >, const std::vector< Contestant >&);
	//TODO implementation
	//Tournament(std::unique_ptr < MatchMaker >, const std::map< Ranking, std::vector<Contestant> >);
	//Tournament(std::shared_ptr < MatchMaker >, const std::map< Ranking, std::vector<Contestant> >);
	Tournament(const Tournament&) = default;
	//Tournament(const Tournament&&) = default;
	//TODO rule of five

	//preparation phase methods
	bool addContestant(const Contestant&);
	bool removeContestant(const Contestant&);
	bool setInitialRanking(const Contestant&, Ranking);

	bool start(); //makes m_contestants read only
	bool isStarted() const { return m_tournamentStarted; }
	
	//running phase methods
	std::unique_ptr<Round> startNewRound();
	std::unique_ptr<Round> finishCurRound(std::unique_ptr<Round>); //return round again if its not ready to be finished, finish successfull -> returning nullptr

	const std::vector< Contestant >& showTeams() const { return m_contestants; }
	std::map< Ranking, Contestant > getCurRankings() const;
	std::map< Ranking, std::pair< Contestant, Score >> getCurRankingsWithScore() const;

private:
	//std::shared_ptr< MatchMaker > m_matchMaker;
	std::unique_ptr< MatchMaker > m_matchMaker;

	//container of Contestants
	std::vector< Contestant > m_contestants{};
	bool m_tournamentStarted{ false };

	std::map< Ranking, std::vector< Contestant >::const_iterator > m_initialRankings{};

	//list of Rounds (past and last entry is current)
	std::vector< Round > m_history{};
	bool m_roundInProgress{ false };

	//TODO rearrange members for optimal memory 
};

class Tournament::Round 
{
public:
	//Round() = default;
	//explicit Round(std::shared_ptr< Tournament >);

	bool recordMatchResult(const Match&, const Score&);
	const std::vector<Match>& correctMatches(const std::vector<Match>&);
	bool setFinished();

	bool canBeFinished() const { return m_matchResults.size() == m_matches.size(); }
	const std::vector<Match>& showMatches() const { return m_matches; }
	Score getScoreOfContestant(const Contestant&) const;

private:
	//std::shared_ptr< Tournament > m_correspondingTournament{ nullptr };

	std::vector< Match > m_matches;
	std::map< std::vector<Match>::const_iterator, Score > m_matchResults;

	bool m_isFinished{ false };
};


//end of namespace b3m -----------------------------------------------------------------------------
}
