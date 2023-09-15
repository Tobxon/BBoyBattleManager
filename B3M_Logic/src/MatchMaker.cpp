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

using ContestantRef_t = std::reference_wrapper< const Contestant >;


std::vector< ContestantRef_t > reorderContestantsByPriority(const std::vector< Contestant >&, const History&);
std::vector< ContestantRef_t > getPreviousOpponents(const Contestant&, const std::vector< Contestant >&, const History&);


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

auto b3m::logic::SwissMatchMaker::createRound(const Tournament& i_tournament) -> TournamentRound
{
	auto contestants = i_tournament.getContestants();
	if(contestants.size() < 2)
	{
		return {}; //TODO properly report error
	}

	const auto& history = i_tournament.getHistory();

	if(history.empty())
	{
		//sort contestants by initial rating
		std::ranges::sort(contestants, [](const Contestant& i_a, const Contestant i_b){
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

	TournamentRound o_round;
	//iterate over contestants - first those who have waited in rounds before and then by ranking
	const auto contestantsInIterateOrder = reorderContestantsByPriority(contestants, history);
	for(const auto& currentContestantRef : contestantsInIterateOrder)
	{
		const auto& checkIfContestantIsAvailable = [&curRound = std::as_const(o_round)](const Contestant& i_contestant){
			return std::ranges::find_if(curRound, [&i_contestant](const Match& i_match){
				const auto& opponents = i_match.getContestantNames();
				return opponents.first == i_contestant.getName() || opponents.second == i_contestant.getName();
			}) == curRound.cend();
		};

		if(checkIfContestantIsAvailable(currentContestantRef))
		{
			//remove itself and previous opponents from possible opponents list
			auto possibleOpponents = contestants
				| std::views::filter([&currentContestantRef](const Contestant& i_contestant){ return i_contestant != currentContestantRef.get(); })
				| std::views::filter(checkIfContestantIsAvailable)
				| std::views::filter([previousOpponents = getPreviousOpponents(currentContestantRef.get(), contestants, history)](const Contestant& i_contestant){ return std::ranges::find_if(previousOpponents, [&i_contestant](const auto& i_contestantRef){ return i_contestantRef.get() == i_contestant; }) == previousOpponents.end(); })
				| std::ranges::to<std::vector<ContestantRef_t>>();

			if(!possibleOpponents.empty())
			{
				//sort possible opponents by distance weight - wrapped around, perfect opponent gets 0 (like algorithm when history is empty), each element moving away -1)
				const auto& curContestantPos = std::distance(contestants.begin(), std::ranges::find(contestants, currentContestantRef.get()));
				std::vector< ContestantRef_t> contestantsWeightingOrder(contestants.cbegin() + curContestantPos, contestants.cend()); //TODO dont copy, create a view
				const Contestant* blockerContestant{ nullptr };
				if(contestants.size() % 2 != 0)
				{
					blockerContestant = new Contestant(""); //TODO save enough?
					contestantsWeightingOrder.emplace_back(*blockerContestant);
				}
				contestantsWeightingOrder.insert(contestantsWeightingOrder.end(), contestants.cbegin(), contestants.cbegin() + curContestantPos);

				std::map< ContestantRef_t, int, std::function<bool(const Contestant&, const Contestant&)> > contestantsWeighting{
					[](const Contestant& i_a, const Contestant& i_b)
					{
						return i_a.getName() < i_b.getName();
					}
				};
				for(auto it = contestantsWeightingOrder.cbegin(); it != contestantsWeightingOrder.cend(); ++it)
				{
					contestantsWeighting[*it] = -std::abs(std::distance(it, (contestantsWeightingOrder.cbegin() + contestantsWeightingOrder.size()/2)));
				}

				std::ranges::sort(possibleOpponents, [&contestantsWeighting](const auto& i_contestantA, const auto& i_contestantB){
					return contestantsWeighting.at(i_contestantA) > contestantsWeighting.at(i_contestantB);
				});

				o_round.emplace_back(currentContestantRef.get(), possibleOpponents.front().get());

				if(contestants.size() % 2 != 0)
				{
					delete blockerContestant;
				}
			}
			else
			{
				//if match isn't found skip this contestant, if this happens again report an error (maybe throw)
				//TODO
			}
		}
	}

	return o_round;
}

std::vector< ContestantRef_t> reorderContestantsByPriority(const std::vector< Contestant >& i_contestantsToReorder, const History& i_history)
{
	std::vector< ContestantRef_t> o_reorderedContestants;
	o_reorderedContestants.reserve(i_contestantsToReorder.size());

	for(const auto& round : std::views::reverse(i_history))
	{
		if(round)
		{
			//TODO assumes that only one contestant didn't match last round - with the current from contestant perspective it can happen that multiple don't find a match
			if(const auto contestantWaited = std::ranges::find_if_not(i_contestantsToReorder,
				[&round](const Contestant& i_contestant){
					return std::ranges::find_if(*round, [&i_contestant](const Match& i_match){
						const auto& opponents = i_match.getContestantNames();
						return opponents.first == i_contestant.getName() ||
							opponents.second == i_contestant.getName();
					}) != round->cend();
			}); contestantWaited != i_contestantsToReorder.cend())
			{
				o_reorderedContestants.emplace_back(*contestantWaited);
			}
		}
	}
	for(const auto& contestant : i_contestantsToReorder)
	{
		if(std::ranges::find_if(o_reorderedContestants,
			[contestant](const auto& contestantReference){
			return contestantReference.get().getName() == contestant.getName();
		}) == o_reorderedContestants.cend())
		{
			o_reorderedContestants.emplace_back(contestant);
		}
	}

	return o_reorderedContestants;
}

std::vector< ContestantRef_t> getPreviousOpponents(const Contestant& i_contestantToFindOpponents, const std::vector< Contestant >& i_contestants, const History& i_history)
{
	std::vector< ContestantRef_t> o_prevOpponents; //TODO to set (faster search)?
	for(const auto& round : i_history)
	{
		for(const auto& match : *round)
		{
			const auto& matchOpponents = match.getContestantNames();
			if(matchOpponents.first == i_contestantToFindOpponents.getName())
			{
				const auto& opponent = std::ranges::find_if(i_contestants,[opponentName = matchOpponents.second](const Contestant& i_contestant){ return i_contestant.getName() == opponentName;}); //TODO use reference or ID of Contestants everywhere
				if(opponent != i_contestants.cend())
				{
					o_prevOpponents.emplace_back(*opponent);
				}
			}
			else if(matchOpponents.second == i_contestantToFindOpponents.getName())
			{
				const auto& opponent = std::ranges::find_if(i_contestants,[opponentName = matchOpponents.first](const Contestant& i_contestant){ return i_contestant.getName() == opponentName;});
				if(opponent != i_contestants.cend())
				{
					o_prevOpponents.emplace_back(*opponent);
				}
			}
			//TODO expects only matches with 2 opponents
		}
	}

	return o_prevOpponents;
}


//END OF FILE --------------------------------------------------------------------------------------