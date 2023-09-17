//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.logic;
import :MatchMakingUtility;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <algorithm>;
import <iterator>;
import <cassert>; //TODO DEBUG

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using b3m::common::Contestant;
using b3m::common::History;
using b3m::common::TournamentRating;
using b3m::common::ContestantsRanking;
using b3m::common::SortedContestantsRanking;
using b3m::common::Match;
using b3m::common::Judgement;
using b3m::common::TournamentRound;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------
bool compareRatingsOrder(const TournamentRating& i_lhs, const TournamentRating& i_rhs)
{
	if(const auto lhsCombRating = i_lhs.getCombinedRating(), rhsCombRating = i_rhs.getCombinedRating();
		lhsCombRating != rhsCombRating)
	{
		return lhsCombRating > rhsCombRating;
	}
	else if(const auto lhsByes = i_lhs.m_numOfByes, rhsByes = i_rhs.m_numOfByes;
			lhsByes != rhsByes)
	{
		return lhsByes > rhsByes;
	}
	else if(const auto lhsVotes = i_lhs.m_numOfVotes, rhsVotes = i_rhs.m_numOfVotes;
			lhsVotes != rhsVotes)
	{
		return lhsVotes > rhsVotes;
	}

	return false;
}

auto b3m::logic::calculateRating(const History& i_history, const std::optional<std::vector< Contestant >>& i_contestants) -> ContestantsRanking
{
	ContestantsRanking contestantsRating;

	for(const auto& round : i_history)
	{
		for(const auto& match : *round)
		{
			const auto matchResult = match.getResults();
			if(matchResult)
			{
				for (const auto& [contestantName, result] : matchResult.value())
				{
					contestantsRating[contestantName] += result;
				}
			}
		}
		if(i_contestants)
		{
			if(const auto freeTicketContestant = getFreeTicketContestant(*round, i_contestants.value()))
			{
				contestantsRating[freeTicketContestant.value().getName()] += b3m::common::freeTicket;
			}
		}
	}
	if(i_contestants)
	{
		for(const auto& contestant : i_contestants.value())
		{
			const auto contestantName = contestant.getName();
			if(!contestantsRating.contains(contestantName))
			{
				contestantsRating[contestantName];
			}
		}
	}

	return contestantsRating;
}

auto b3m::logic::getSortedRanking(const History& i_history, const std::vector< Contestant >& i_contestants) -> SortedContestantsRanking
{
	const auto& unsortedContestantRanking = calculateRating(i_history, i_contestants);

	return getSortedRanking(i_contestants, unsortedContestantRanking);
}

auto b3m::logic::getSortedRanking(const std::vector< Contestant >& i_contestants, const ContestantsRanking& i_contestantsWithRating) -> SortedContestantsRanking
{
	SortedContestantsRanking sortedContestantsWithRating;
	std::ranges::transform(i_contestants, std::back_inserter(sortedContestantsWithRating), [i_contestantsWithRating](const Contestant& i_contestant){
		const auto& contestantName = i_contestant.getName();
		return std::make_pair<>(contestantName, i_contestantsWithRating.contains(contestantName) ? i_contestantsWithRating.at(contestantName) : TournamentRating{});
	});

	std::ranges::sort(sortedContestantsWithRating,[] //TODO merge with lamdba on line 137
		(const SortedContestantsRanking::value_type& i_lhs, const SortedContestantsRanking::value_type& i_rhs){
			return compareRatingsOrder(i_lhs.second, i_rhs.second);
	});

	return sortedContestantsWithRating;
}

void b3m::logic::sortTeamsByResults(std::vector< Contestant >& i_contestantsToSort, const History& i_history)
{
	std::map< Contestant::Name_t, TournamentRating > contestantsRating;
	std::map< Contestant::Name_t, int > contestantsNumberOfRounds;

	//TODO to std algorithm use? - //TODO replace with calculateRating result
	for(const auto& round : i_history)
	{
		for(const auto& match : *round)
		{
			const auto matchResult = match.getResults();
			if(matchResult)
			{
				for (const auto& [contestantName, results] : matchResult.value())
				{
					contestantsRating[contestantName] += results;
					contestantsNumberOfRounds[contestantName]++;
				}
			}
		}
	}
	for(const auto& contestant : i_contestantsToSort)
	{
		const auto contestantName = contestant.getName();
		if(!contestantsRating.contains(contestantName))
		{
			contestantsRating[contestantName];
		}
	}

	const auto numberOfRounds = i_history.size();

	std::ranges::sort(i_contestantsToSort,
		[&contestantsRating = std::as_const(contestantsRating)]
		(const Contestant& i_lhs, const Contestant& i_rhs){
			return compareRatingsOrder(contestantsRating.at(i_lhs.getName()), contestantsRating.at(i_rhs.getName()));
	});
}

auto b3m::logic::getFreeTicketContestant(const TournamentRound& i_round, const std::vector< Contestant >& i_contestants) -> std::optional< Contestant >
{
	//TODO assumes that only one contestant didn't match last round - with the current from contestant perspective it can happen that multiple don't find a match
	if(const auto contestantWaited = std::ranges::find_if_not(i_contestants,
		[&i_round](const Contestant& i_contestant){
			return std::ranges::find_if(i_round, [&i_contestant](const Match& i_match){
				const auto& opponents = i_match.getContestantNames();
				return opponents.first == i_contestant.getName() ||
					opponents.second == i_contestant.getName();
			}) != i_round.cend();
		}); contestantWaited != i_contestants.cend())
	{
		return *contestantWaited;
	}

	return std::nullopt;
}


//END OF FILE --------------------------------------------------------------------------------------