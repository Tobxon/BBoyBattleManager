//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.logic;
import :MatchMaker;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <algorithm>;

import utility;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using b3m::common::Team;
using b3m::common::Contestant;
using b3m::common::History;
using b3m::common::TournamentRating;


void sortTeamsByResults(std::vector< Contestant >&, const History&);


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

auto b3m::logic::SwissMatchMaker::createRound(const Tournament& i_tournament) -> TournamentRound
{
	auto contestants = i_tournament.getContestants();
	if(contestants.size() < 2)
	{
		return {};
	}

	const auto& history = i_tournament.getHistory();

	if(history.empty())
	{
		//sort contestants by initial ranking
		std::ranges::sort(contestants, [](const Team& i_a, const Team i_b){
			return i_a.getRating() < i_b.getRating();
		});
	}
	else
	{
		//sort contestants by match results (and initial rating)
		sortTeamsByResults(contestants, history);
	}

	TournamentRound o_round;
	for(auto firstHalfIt = contestants.cbegin(), secondHalfIt = contestants.cbegin() + utility::ceil_pos_uint_division<decltype(contestants.size())>(contestants.size(), 2);
		firstHalfIt < contestants.cbegin() + contestants.size()/2 && secondHalfIt < contestants.cend(); firstHalfIt++, secondHalfIt++)
	{
		o_round.emplace_back(*firstHalfIt, *secondHalfIt);
	}

	return o_round;
}

void sortTeamsByResults(std::vector< Contestant >& i_contestantsToSort, const History& i_history)
{
	std::map< Contestant::Name_t, TournamentRating > contestantsRating;

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
		 &numberOfRounds = std::as_const(numberOfRounds)]
		(const Contestant& i_a, const Contestant& i_b){
//			return contestantsRating.at(i_a.getName()) > contestantsRating.at(i_b.getName());
			const auto combRatingA = contestantsRating.at(i_a.getName()).getCombinedRating();
			const auto combRatingB = contestantsRating.at(i_b.getName()).getCombinedRating();
			if(combRatingA == combRatingB)
			{
				return contestantsRating.at(i_a.getName()).m_numOfVotes > contestantsRating.at(i_b.getName()).m_numOfVotes;
			}
			return static_cast<double>(combRatingA)/numberOfRounds
				> static_cast<double>(combRatingB)/numberOfRounds;
	});
}


//END OF FILE --------------------------------------------------------------------------------------