#pragma once

#include "SwissStyleTournamentLibrary.h"

#include <vector>
#include <map>
#include <ostream>

#include "Team.hpp"

namespace b3m
{

class Tournament;

using TeamName = std::string;
using MatchId = std::size_t;
using Match = std::pair< TeamName, TeamName >;
using Result = std::pair< int, int >;


class MatchRecord
{
public:
	MatchRecord() = delete;
	MatchRecord(const MatchId&, const Match&, const Result&, unsigned int = 0, Tournament* = nullptr);

	MatchId getId() const { return m_id; }
private:
	MatchId m_id;
	Match m_contestants;
	Result m_result;

	Tournament* m_pTournament{ nullptr };
	unsigned int m_roundId;
};


class SSTLIBRARY_API Tournament
{
public:
	using rating = unsigned int;
	using spot = std::size_t;
	using MatchHistory = std::vector<MatchRecord>;

	bool addTeam(const TeamName&, rating = 0);
	bool setCurSpot(const TeamName&, std::size_t);
	//bool setRating(const teamName&, rating);

	//algorithms
	std::map<MatchId, Match> createCurMatches();
	bool finishMatch(const MatchId&, const Match&, const Result&, unsigned int);

	std::size_t getNumOfTeams() { return m_teamNames.size(); }
	const std::vector<TeamName>& getTeamNames() { return m_teamNames; }

#ifdef _DEBUG
	void printAllTeamNames(std::ostream&) const;
	void printTeamTable(std::ostream&) const;
#endif //_DEBUG

private:
	std::vector<TeamName> m_teamNames;
	std::map<spot, std::vector<TeamName>::const_iterator> m_ratingsOfTeams;

	MatchHistory m_history;

	//b3m::MatchMaker m_matchMaker;
	//b3m::History m_history; //TODO
};

}
