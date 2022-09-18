

//--------------------------------------------------------------------------------------------------
//Includes                                                                                     -----
//--------------------------------------------------------------------------------------------------
#include "pch.h"

#include <stdexcept>
#include <algorithm>
#include <set>

//corresponding header
#include "SwissStyleMM.hpp"
#include "utility.hpp"

//--------------------------------------------------------------------------------------------------
//Implementations                                                                              -----
//--------------------------------------------------------------------------------------------------

std::vector<b3m::Match> b3m::SwissStyleMM::createMatches(
	const std::vector<Contestant>& i_contestants, 
	const std::map<Ranking, std::vector<Contestant>::const_iterator>& i_initialRankings, 
	const MatchingInfos& i_furtherInformations)
{
	//const auto& l_sizeHalfBrackets = i_contestants.size() / 2;

	////TODO create ranking of asked contestants
	//std::map< Ranking, std::vector<Contestant>::const_iterator > l_curRanking;

	const auto& l_furtherInfos = dynamic_cast<const SwissStyleMatchingInfos&>(i_furtherInformations); //might throw
	//TODO catch exception

	//acquire current score of asked contestants (i_contestants)
	std::map< std::vector<Contestant>::const_iterator, Score > l_scoreOfAskedContants;
	for (auto l_contantIt = i_contestants.cbegin(); l_contantIt != i_contestants.cend(); ++l_contantIt)
	{
		try
		{
			const auto c_tempScore = l_furtherInfos.m_ScoreOfContestants.at(l_contantIt);
			l_scoreOfAskedContants[l_contantIt] = c_tempScore;
		}
		catch (const std::out_of_range& exception)
		{
			//Score for contestant *l_contantIt not delivered
			l_scoreOfAskedContants[l_contantIt] = Score(0);
		}
	}

	//from max score to min score

	auto l_scoreCmp = [](const Score& i_lhs, const Score& i_rhs) {
		return i_lhs.m_wins + i_lhs.m_freeTickets > i_rhs.m_wins + i_rhs.m_freeTickets;
	};
	std::set< Score, decltype(l_scoreCmp) > l_existingScores(l_scoreCmp);
	for (const auto& l_scoreEntry : l_scoreOfAskedContants)
	{
		l_existingScores.insert(l_scoreEntry.second);
	}


	std::vector<b3m::Match> r_matches;


	std::vector< Contestant > l_remainingContants{}; //empty at begin

	for (const auto& l_score : l_existingScores)
	{
		std::vector< Contestant > l_contantsToMatch{ l_remainingContants }; //TODO add isTaken information
		l_remainingContants.clear();

		for (const auto& l_contantEntry : i_initialRankings)
		{
			using namespace b3m::sst;
			if (l_scoreOfAskedContants.at(l_contantEntry.second) == l_score)
			{
				l_contantsToMatch.push_back(*l_contantEntry.second);
			}
		}

		//const auto c_halfBracketSize = l_contantsToMatch.size() / 2;
		//for (std::size_t iContant = 0; iContant < l_contantsToMatch.size()/2; ++iContant)
		//{
		//	//TODO
		//	r_matches.push_back(Match(l_contantsToMatch.at(iContant), l_contantsToMatch.at(iContant+ c_halfBracketSize)));
		//}

		////TODO append remaining Contants for next iteration
		//if (l_contantsToMatch.size() % 2 != 0)
		//{
		//	l_remainingContants.push_back(l_contantsToMatch.at(l_contantsToMatch.size() / 2 + 1));
		//}

		std::map< std::vector<Contestant>::const_iterator, bool> l_contantIsTaken;
		for (auto itContant = l_contantsToMatch.begin(); itContant != l_contantsToMatch.end(); ++itContant)
		{
			l_contantIsTaken[itContant] = false;
		}

		for (const auto& l_contant : l_contantsToMatch)
		{
			//for Debug
			const auto l_midIt = l_contantsToMatch.cbegin() + divideUintRoundUp< std::size_t >(l_contantsToMatch.size(), 2);

			std::vector< std::vector<Contestant>::const_iterator > l_upperBracket/*{ l_contantsToMatch.cbegin(), l_midIt }*/; //TODO uprounding div
			for (auto itUppBra = l_contantsToMatch.cbegin(); itUppBra != l_midIt; ++itUppBra)
			{
				l_upperBracket.push_back(itUppBra);
			}

			std::vector< std::vector<Contestant>::const_iterator > l_lowerBracket/*{ l_midIt, l_contantsToMatch.cend() }*/;
			for(auto itUppBra = l_midIt; itUppBra != l_contantsToMatch.cend(); ++itUppBra)
			{
				l_lowerBracket.push_back(itUppBra);
			}

			//std::map< std::vector<Contestant>::const_iterator, bool> l_contantIsTaken;
			//for (auto itContant = l_upperBracket.begin(); itContant != l_upperBracket.end(); ++itContant)
			//{
			//	l_contantIsTaken[itContant] = false;
			//}
			//for (auto itContant = l_lowerBracket.begin(); itContant != l_lowerBracket.end(); ++itContant)
			//{
			//	l_contantIsTaken[itContant] = false;
			//}

			for (const auto& l_itUppBraContant : l_upperBracket)
				//auto ituppBraContant = l_upperBracket.cbegin(); ituppBraContant != l_upperBracket.cend(); ++ituppBraContant)
			{
				//get all previous Opponents
				std::vector< Contestant > l_pastOpponents;
				for (const auto& l_pastRound : l_furtherInfos.m_history)
				{
					const auto l_curPastOpponents = l_pastRound.getOpponents(*l_itUppBraContant);
					l_pastOpponents.insert(l_curPastOpponents.cbegin(), l_curPastOpponents.cend(), l_pastOpponents.cend());
				}

				for (const auto& l_itLowBraContant : l_lowerBracket)
					//auto itLowBraContant = l_lowerBracket.cbegin(); itLowBraContant != l_lowerBracket.cend(); ++itLowBraContant)
				{
					if (!l_contantIsTaken.at(l_itLowBraContant)) //not already taken
					{
						if (l_pastOpponents.empty() || std::find(l_pastOpponents.cbegin(), l_pastOpponents.cend(), *l_itLowBraContant) != l_pastOpponents.cend()) //haven't been opponents before
						{
							r_matches.emplace_back(*l_itUppBraContant, *l_itLowBraContant);
							l_contantIsTaken[l_itUppBraContant] = true;
							l_contantIsTaken[l_itLowBraContant] = true;
							break;
						}
					}					
				}
			}

			for (const auto& l_contantTakenEntry : l_contantIsTaken)
			{
				if (!l_contantTakenEntry.second)
				{
					l_remainingContants.push_back(*l_contantTakenEntry.first);
				}
			}
		}

	}
	if (l_remainingContants.size() > 1)
	{
		//TODO error
	}
	
	//TODO get all Scores from highest to lowest
	//{
	//	std::vector< Score > l_existingScores;
	//	//TODO to set with right adjustments
	//	//std::set< Score > l_existingScores;
	//	for (const auto& l_score : l_scoreOfAskedContants)
	//	{
	//		for (const auto& l_existingScore : l_existingScores)
	//		{
	//			if(l_score.second.m_wins+ l_score.second.m_freeTickets == )
	//		}
	//		//l_existingScores.insert(l_Score.second);
	//	}
	//}

	// 
	//using namespace b3m::sst;
	//for (
	//	auto iScore = std::min_element(l_scoreOfAskedContants.cbegin(), l_scoreOfAskedContants.cend(),
	//		[](const std::pair< std::vector<Contestant>::const_iterator, Score >& i_a, const std::pair< std::vector<Contestant>::const_iterator, Score >& i_b)
	//		{
	//			
	//			i_a.second < i_b.second;
	//		}
	//)->second;
	//	iScore <= std::max_element(l_scoreOfAskedContants.cbegin(), l_scoreOfAskedContants.cend(),
	//		[](const std::pair< std::vector<Contestant>::const_iterator, Score >& i_a, const std::pair< std::vector<Contestant>::const_iterator, Score >& i_b)
	//		{
	//			i_a.second < i_b.second;
	//		}
	//)->second;
	//++iScore)
	//{

	//}


	return r_matches;
}
