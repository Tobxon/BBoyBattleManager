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


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------
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
				for (const auto& [contestantName, results] : matchResult.value())
				{
					contestantsRating[contestantName] += results;
				}
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

auto b3m::logic::getSortedRanking(const History& i_history, const std::optional<std::vector< Contestant >>& i_contestants) -> SortedContestantsRanking
{
	const auto& unsortedContestantRanking = calculateRating(i_history, i_contestants);

	return getSortedRanking(unsortedContestantRanking);
}

auto b3m::logic::getSortedRanking(ContestantsRanking i_contestantsWithRating) -> SortedContestantsRanking
{
	SortedContestantsRanking sortedContestantsWithRating{i_contestantsWithRating.cbegin(), i_contestantsWithRating.cend()};

	std::ranges::sort(sortedContestantsWithRating,[]
		(const SortedContestantsRanking::value_type& i_lhs, const SortedContestantsRanking::value_type& i_rhs){
			const auto& lhsRating = i_lhs.second;
			const auto& rhsRating = i_rhs.second;
			const auto& numberOfRoundsA = lhsRating.getNumberOfRatings();
			const auto& numberOfRoundsB = rhsRating.getNumberOfRatings();

			const auto resultA = (numberOfRoundsA > 0 ? static_cast<double>(lhsRating.getCombinedRating())/numberOfRoundsA : 0.0);
			const auto resultB = (numberOfRoundsB > 0 ? static_cast<double>(rhsRating.getCombinedRating())/numberOfRoundsB : 0.0);
			if(resultA == resultB)
			{
				return (numberOfRoundsA > 0 ? static_cast<double>(lhsRating.m_numOfVotes)/numberOfRoundsA : 0.0)
					   > (numberOfRoundsB > 0 ? static_cast<double>(rhsRating.m_numOfVotes)/numberOfRoundsB : 0.0);
			}
			return resultA > resultB;
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
		[&contestantsRating = std::as_const(contestantsRating),
		 &contestantsNumberOfRounds = std::as_const(contestantsNumberOfRounds)]
		(const Contestant& i_a, const Contestant& i_b){
			const auto& aName =  i_a.getName();
			const auto& bName =  i_b.getName();
			const auto& numberOfRoundsAOld = contestantsNumberOfRounds.contains(aName) ? contestantsNumberOfRounds.at(aName) : 0;
			const auto& numberOfRoundsA = contestantsRating.at(aName).getNumberOfRatings();
			const auto& numberOfRoundsBOld = contestantsNumberOfRounds.contains(bName) ? contestantsNumberOfRounds.at(bName) : 0;
			const auto& numberOfRoundsB = contestantsRating.at(bName).getNumberOfRatings();

			//TODO DEBUG
			assert(numberOfRoundsA==numberOfRoundsAOld);
			assert(numberOfRoundsB==numberOfRoundsBOld);

			const auto resultA = (numberOfRoundsA > 0 ? static_cast<double>(contestantsRating.at(aName).getCombinedRating())/numberOfRoundsA : 0.0);
			const auto resultB = (numberOfRoundsB > 0 ? static_cast<double>(contestantsRating.at(bName).getCombinedRating())/numberOfRoundsB : 0.0);
			if(resultA == resultB)
			{
				return (numberOfRoundsA > 0 ? static_cast<double>(contestantsRating.at(aName).m_numOfVotes)/numberOfRoundsA : 0.0)
					> (numberOfRoundsB > 0 ? static_cast<double>(contestantsRating.at(bName).m_numOfVotes)/numberOfRoundsB : 0.0);
			}
			return resultA > resultB;
	});
}


//END OF FILE --------------------------------------------------------------------------------------