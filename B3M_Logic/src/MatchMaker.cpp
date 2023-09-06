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
import <vector>;
import <functional>;
import <ranges>;
import <map>;

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
using b3m::common::Match;


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

		TournamentRound o_round;
		for(auto firstHalfIt = contestants.cbegin(), secondHalfIt = contestants.cbegin() + utility::ceil_pos_uint_division<decltype(contestants.size())>(contestants.size(), 2);
			firstHalfIt < contestants.cbegin() + contestants.size()/2 && secondHalfIt < contestants.cend(); firstHalfIt++, secondHalfIt++)
		{
			o_round.emplace_back(*firstHalfIt, *secondHalfIt);
		}

		return o_round;
	}

	//sort contestants by match results (and initial rating)
	sortTeamsByResults(contestants, history);

	using contestantsElement_t = decltype(contestants)::value_type;

	//iterate over contestants - first those who have waited in rounds before and then from by ranking
	std::vector< std::reference_wrapper< const contestantsElement_t >> contestantsIterateOrder{};
	contestantsIterateOrder.reserve(contestants.size());

	for(const auto& round : std::views::reverse(history))
	{
		if(round)
		{
			if(const auto contestantWaited = std::ranges::find_if_not(contestants, [&round](const Contestant& i_contestant){
				return std::ranges::find_if(*round, [&i_contestant](const Match& i_match){
					const auto& opponents = i_match.getContestantNames();
					return opponents.first == i_contestant.getName() || opponents.second == i_contestant.getName();
				}) != round->cend();
			}); contestantWaited != contestants.cend())
			{
				contestantsIterateOrder.emplace_back(*contestantWaited);
			}
		}
	}
	for(const auto& contestant : contestants)
	{
		if(std::ranges::find_if(contestantsIterateOrder, [contestant](const auto& contestantReference){
			return contestantReference.get().getName() == contestant.getName();
		}) == contestantsIterateOrder.cend())
		{
			contestantsIterateOrder.emplace_back(contestant);
		}
	}

	std::map< std::reference_wrapper< const contestantsElement_t >, bool, std::function<bool(const contestantsElement_t&, const contestantsElement_t&)> > takenContestants{
		[](const contestantsElement_t& i_a, const contestantsElement_t& i_b)
		{
			return i_a.getName() < i_b.getName();
		}
	};
	std::ranges::transform(contestantsIterateOrder, std::inserter(takenContestants, takenContestants.end()), [](const auto& i_contestantRef){ return std::make_pair(i_contestantRef, false); });

	for(const auto& currentContestantRef : contestantsIterateOrder)
	{
		if(!takenContestants.at(currentContestantRef))
		{
			//get previous opponents for current contestant
			std::vector< std::reference_wrapper< const decltype(contestants)::value_type >> previousOpponents; //TODO to reference to contestants element
			for(const auto& round : history)
			{
				for(const auto& match : *round)
				{
					const auto& matchOpponents = match.getContestantNames();
					if(matchOpponents.first == currentContestantRef.get().getName())
					{
						const auto& opponent = std::ranges::find_if(contestants,[opponentName = matchOpponents.second](const Contestant& i_contestant){ return i_contestant.getName() == opponentName;}); //TODO use reference or ID of Contestants everywhere
						if(opponent != contestants.cend())
						{
							previousOpponents.emplace_back(*opponent);
						}
					}
					else if(matchOpponents.second == currentContestantRef.get().getName())
					{
						const auto& opponent = std::ranges::find_if(contestants,[opponentName = matchOpponents.first](const Contestant& i_contestant){ return i_contestant.getName() == opponentName;});
						if(opponent != contestants.cend())
						{
							previousOpponents.emplace_back(*opponent);
						}
					}
					//TODO expects only matches with 2 opponents
				}
			}

			//remove itself and previous opponents from possible opponents list
			const auto possibleOpponents = contestants
				| std::views::filter([&currentContestantRef](const contestantsElement_t& i_contestant){ return i_contestant != currentContestantRef.get(); })
				| std::views::filter([&takenContestants](const contestantsElement_t& i_contestant){ return takenContestants.at(i_contestant); });

			//sort possible opponents by distance weight (the closer they are to the current one the smaller the weight should be see excel) - skip previous opponents
			//TODO

			//search in weighted list of possible opponents for best fitting contestant
			//TODO

			//if match is found - mark contestants as taken and append match to TournamentRound to return
			//TODO

			//if match isn't found skip this contestant, if this happens again report an error (maybe throw)
			//TODO
		}
	}

	return {};
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