

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------
#include "pch.h"

//stl
#include <map>
#include <iostream>

//b3m
#include "Tournament.hpp"
#include "SwissStyleMM.hpp"

//--------------------------------------------------------------------------------------------------
//Implementations                                                                              -----
//--------------------------------------------------------------------------------------------------

b3m::Tournament::Tournament(std::unique_ptr < MatchMaker > i_matchMaker)
	: m_matchMaker(std::move(i_matchMaker)) //TODO std::move unneccessary?
{
}

//b3m::Tournament::Tournament(std::shared_ptr < MatchMaker > i_matchMaker)
//	: m_matchMaker(i_matchMaker)
//{
//}

b3m::Tournament::Tournament(std::unique_ptr < MatchMaker > i_matchMaker, 
	const std::vector< Contestant >& i_contestants)
	: m_contestants(i_contestants), m_matchMaker(std::move(i_matchMaker))
{
}

//b3m::Tournament::Tournament(std::shared_ptr < MatchMaker > i_matchMaker, 
//	const std::vector< Contestant >& i_contestants)
//	: m_contestants(i_contestants), m_matchMaker(i_matchMaker)
//{
//}

//TODO implementation
//b3m::Tournament::Tournament(std::unique_ptr < MatchMaker > i_matchMaker,
//	const std::map< Ranking, std::vector<Contestant> > i_contestantsWithInitialRanking)
//{
//}
//
//b3m::Tournament::Tournament(std::shared_ptr < MatchMaker > i_matchMaker,
//	const std::map< Ranking, std::vector<Contestant> > i_contestantsWithInitialRanking)
//{
//}


//preparation phase methods ------------------------------------------------------------------------
bool b3m::Tournament::addContestant(const Contestant& i_toAddContestant)
{
	if (m_tournamentStarted)
	{
		//tournament started already
		return false;
	}

	if (!m_contestants.empty() && (std::find(m_contestants.begin(), m_contestants.end(), 
		i_toAddContestant) != m_contestants.end()))
	{
		//Contestant Name already registered
		return false;
	}
	
	m_contestants.push_back(i_toAddContestant);
	
	return true;
}

bool b3m::Tournament::removeContestant(const Contestant& i_toRemoveContestant)
{
	if (m_tournamentStarted)
	{
		//tournament started already
		return false;
	}

	const auto l_it = std::find(m_contestants.begin(), m_contestants.end(), i_toRemoveContestant);
	if (l_it == m_contestants.end())
	{
		return false;
	}

	m_contestants.erase(l_it);

	return true;
}

bool b3m::Tournament::setInitialRanking(const Contestant& i_contestant, Ranking i_toSetRanking)
{
	if (m_tournamentStarted)
	{
		//tournament started already
		return false;
	}

	const auto l_contestantIt = std::find(m_contestants.begin(), m_contestants.end(), i_contestant);
	if (l_contestantIt == m_contestants.end())
	{
		//not a correct contestant
		return false;
	}

	if (i_toSetRanking > m_contestants.size())
	{
		//ranking too high
		return false;
	}

	if (m_initialRankings.contains(i_toSetRanking))
	{
		//ranking already taken
		return false;
	}
	
	m_initialRankings[i_toSetRanking] = l_contestantIt;
	return true;

}

//running phase methods-----------------------------------------------------------------------------

bool b3m::Tournament::start()
{
	if (m_tournamentStarted)
	{
		return true;
	}

	if (m_contestants.empty() || (m_initialRankings.size() != m_contestants.size()))
	{
		return false;
	}

	m_tournamentStarted = true;
	return m_tournamentStarted;
}

std::unique_ptr<b3m::Tournament::Round> b3m::Tournament::startNewRound()
{
if (!m_tournamentStarted)
	{
		return nullptr;
	}

	if (m_roundInProgress == true)
	{
		return nullptr;
		//TODO how to get to the round again if data has been lost?
	}

	//actual create Round by using MatchMaker to create a match for every (or every -1) contestant
	std::map< std::vector< Contestant >::const_iterator, Score > l_ScoresOfContants;
	for (auto l_contantIt = m_contestants.cbegin(); l_contantIt != m_contestants.cend(); ++l_contantIt)
	{
		l_ScoresOfContants[l_contantIt] = getScoreOfContestant(*l_contantIt);
	}

	const auto l_matches = m_matchMaker->createMatches(m_contestants, m_initialRankings, b3m::SwissStyleMM::SwissStyleMatchingInfos(l_ScoresOfContants, m_history));

	//TODO check if some Contestants didn't get a match, if yes (1 -> give him a free ticket), (2 or more -> error)

	m_roundInProgress = true;

	return std::make_unique<Round>(l_matches);
}

std::unique_ptr<b3m::Tournament::Round> b3m::Tournament::finishCurRound(
	std::unique_ptr<Round> i_toFinishRound)
{
	if (!m_tournamentStarted || !m_roundInProgress)
	{
		return std::move(i_toFinishRound);
	}

	//TODO check if Round belongs to Tournament

	if (i_toFinishRound->setFinished())
	{
		//finishing successfull
		m_history.emplace_back(*i_toFinishRound); //TODO correct way?
		m_roundInProgress = false;
		return nullptr;
	}

	//finishing Round failed - propably still match results needed to be recorded
	return std::move(i_toFinishRound);
}

std::map<b3m::Ranking, b3m::Contestant> b3m::Tournament::getCurRankings() const
{
	std::map<b3m::Ranking, b3m::Contestant> l_curRankings;

	if (!m_tournamentStarted)
	{
		for (const auto& l_contestantByRanking : m_initialRankings)
		{
			l_curRankings[l_contestantByRanking.first] = *l_contestantByRanking.second;
		}

		return l_curRankings;
	}

	return std::map<Ranking, Contestant>();
}

std::map<b3m::Ranking, std::pair<b3m::Contestant, b3m::Score>> b3m::Tournament::getCurRankingsWithScore() const
{
	return std::map<Ranking, std::pair<Contestant, Score>>();
}

b3m::Score b3m::Tournament::getScoreOfContestant(const Contestant& i_contant)
{
	if (std::find(m_contestants.cbegin(), m_contestants.cend(), i_contant) == m_contestants.cend())
	{
		throw; //TODO specify exception
	}

	Score r_score;

	for (const auto& l_round : m_history)
	{
		r_score += l_round.getScoreOfContestant(i_contant);
	}

	return r_score;
}



//OLD CODE (17/09/2022 16:05):
//bool b3m::Tournament::addTeam(const TeamName& i_toAdd, rating i_rating)
//{
//	if (!m_teamNames.empty() && (std::find(m_teamNames.begin(), m_teamNames.end(), i_toAdd) != m_teamNames.end()))
//	{
//		//Team already registered
//		return false;
//	}
//
//	m_teamNames.push_back(i_toAdd);
//
//	return true;
//}
//
//bool b3m::Tournament::setCurSpot(const TeamName& i_teamName, std::size_t i_spotToSet)
//{
//	auto l_it = std::find(m_teamNames.begin(), m_teamNames.end(), i_teamName);
//	if (l_it == m_teamNames.end())
//	{
//		return false;
//	}
//
//	if (m_ratingsOfTeams.contains(i_spotToSet-1))
//	{
//		return false;
//	}
//
//	m_ratingsOfTeams.emplace(i_spotToSet-1, l_it);
//	return true;
//}
//
//
//std::map<b3m::MatchId, b3m::Match> b3m::Tournament::createCurMatches()
//{
//	std::map<MatchId, Match> r_matches;
//
//	std::map < std::vector<TeamName>::const_iterator, bool > l_takenTeams;
//	for (auto l_it = m_teamNames.begin(); l_it != m_teamNames.end(); ++l_it)
//	{
//		l_takenTeams.emplace(l_it, false);
//	}
//	//TODO if history is empty
//	for (auto l_teamNameIt = m_teamNames.begin(); l_teamNameIt != m_teamNames.end(); ++l_teamNameIt)
//	{
//		if (l_takenTeams.at(l_teamNameIt) == true)
//		{
//			continue;
//		}
//
//		std::string l_opponentName;
//
//		if (m_history.empty())
//		{
//			l_opponentName = b3m::sst::findFirstMatchOpponent(l_teamNameIt, m_ratingsOfTeams);
//		}
//		else
//		{
//			//TODO
//		}
//
//		if (l_opponentName == "")
//		{
//			//TODO free point
//			continue;
//		}
//
//		r_matches.emplace(createNewUniqueId(), Match(*l_teamNameIt, l_opponentName));
//	}
//
//	return r_matches;
//}
//
//bool b3m::Tournament::finishMatch(const MatchId& i_id, const Match& i_match, const Result& i_result, unsigned int i_roundId)
//{
//	//check if Match is already finished
//	for (const auto& l_matchRecord : m_history)
//	{
//		if (l_matchRecord.getId() == i_id)
//		{
//			return false;
//		}
//	}
//
//	//add points for winner
//	{
//		const auto l_winner = b3m::sst::decideWinner(i_match, i_result);
//
//		if (l_winner == "")
//		{
//
//		}
//		else
//		{
//			const auto l_winnerIt = std::find(m_teamNames.begin(), m_teamNames.end(), l_winner);
//			++m_TeamPoints[l_winnerIt];
//			//TODO update rating
//		}
//	}
//
//	m_history.emplace_back(i_id, i_match, i_result, i_roundId, this);
//
//	return true;
//}
//
//
//#ifdef _DEBUG
//void b3m::Tournament::printAllTeamNames(std::ostream& i_printSink) const
//{
//	i_printSink << "Alle Teams, die in diesem Turnier antreten:" << std::endl;
//
//	for (const auto& l_teamName : m_teamNames)
//	{
//		i_printSink << l_teamName << ", ";
//	}
//	i_printSink << std::endl;
//}
//
//void b3m::Tournament::printTeamTable(std::ostream& i_printSink) const
//{
//	i_printSink << "current tournament table:" << std::endl;
//
//	for (const auto& l_entry : m_ratingsOfTeams)
//	{
//		i_printSink << (l_entry.first+1) << ".\t- " << *l_entry.second << std::endl;
//	}
//}
//#endif //_DEBUG
//
////free functions
//std::vector<b3m::TeamName> b3m::getPastOpponents(const Tournament::MatchHistory& i_history, const TeamName& i_team)
//{
//	std::vector<b3m::TeamName> r_opponentList;
//
//	for (const auto& l_matchRecord : i_history)
//	{
//		const auto l_checkRes = l_matchRecord.wasContestant(i_team);
//
//		if (l_checkRes.first)
//		{
//			r_opponentList.push_back(l_checkRes.second);
//		}
//	}
//
//	return r_opponentList;
//}
//
//
//
////MatchRecord
//b3m::MatchRecord::MatchRecord(const MatchId& i_id, const Match& i_match, const Result& i_res, unsigned int i_roundId, Tournament* i_pTournament)
//	: m_id(i_id), m_contestants(i_match), m_result(i_res), m_roundId(i_roundId), m_pTournament(i_pTournament)
//{
//}
//
//std::pair<bool, b3m::TeamName> b3m::MatchRecord::wasContestant(const TeamName& i_team) const
//{
//	if (m_contestants.first == i_team)
//	{
//		return std::make_pair(true, m_contestants.second);
//	}
//	else if (m_contestants.second == i_team)
//	{
//		return std::make_pair(true, m_contestants.first);
//	}
//	else
//	{
//		return std::make_pair(false, "");
//	}
//}

//Round---------------------------------------------------------------------------------------------


const std::vector<b3m::Match>& b3m::Tournament::Round::correctMatches(const std::vector<Match>&)
{
	if (!m_matchResults.empty())
	{
		return m_matches;
	}

	//TODO implementation
	return m_matches;
}

bool b3m::Tournament::Round::recordMatchResult(const Match& i_match, const std::pair<Score, Score>& i_score)
{
	if (m_isFinished)
	{
		return false;
	}

	const auto l_itMatch = std::find(m_matches.cbegin(), m_matches.cend(), i_match);

	if (m_matches.empty() || (l_itMatch == m_matches.cend()))
	{
		return false;
	}

	m_matchResults[*l_itMatch] = i_score;

	return true;
}

bool b3m::Tournament::Round::setFinished()
{
	if (m_isFinished)
	{
		return m_isFinished;
	}

	if (m_matchResults.size() != m_matches.size())
	{
		return false;
	}

	m_isFinished = true;

	return m_isFinished;
}

b3m::Score b3m::Tournament::Round::getScoreOfContestant(const Contestant& i_contant) const
{
	//TODO anything to check first?

	Score r_score;

	for (auto itMatch = m_matches.cbegin(); itMatch != m_matches.cend(); ++itMatch)
	{
		try
		{
			if (itMatch->first == i_contant)
			{
				r_score += m_matchResults.at(*itMatch).first;
			}
			else if (itMatch->second == i_contant)
			{
				r_score += m_matchResults.at(*itMatch).second;
			}
		}
		catch (const std::out_of_range&)
		{
			//result not recorded yet
		}
	}

	return r_score;
}

std::vector< b3m::Contestant > b3m::Tournament::Round::getOpponents(const Contestant& i_contant) const
{
	std::vector< b3m::Contestant > r_opponents;

	for (const auto& l_match : m_matches)
	{
		if (l_match.first == i_contant)
		{
			r_opponents.push_back(l_match.second);
		}
		else if (l_match.second == i_contant)
		{
			r_opponents.push_back(l_match.first);
		}
	}

	return r_opponents;
}
