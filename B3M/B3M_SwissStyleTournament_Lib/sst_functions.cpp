#include "pch.h"

#include "sst_functions.h"

void b3m::sst::testPrint(std::ostream& i_streamToPrintTo)
{
	i_streamToPrintTo << "This is the B3M_SwissStyleTournament_Library talkin!" << std::endl;
}

std::string b3m::sst::returnHelloWorld()
{
	return "Hello World!";
}


b3m::TeamName b3m::sst::findFirstMatchOpponent(const std::vector<b3m::TeamName>::const_iterator& i_ownName, const std::map<b3m::Tournament::spot, std::vector<b3m::TeamName>::const_iterator>& i_teamsByRating)
{
	auto result = std::find_if(
		i_teamsByRating.begin(),
		i_teamsByRating.end(),
		[i_ownName](const auto& mo) {return mo.second == i_ownName; })->first;

	const auto l_spotOpponent = result + divideUintRoundUp<std::size_t>(i_teamsByRating.size(), 2);

	if (l_spotOpponent >= i_teamsByRating.size())
	{
		return "";
	}

	return *i_teamsByRating.at(l_spotOpponent);
}

b3m::TeamName b3m::sst::decideWinner(const Match& i_contestants, const Result& i_result)
{
	if (i_result.first > i_result.second)
	{
		return i_contestants.first;
	}
	else if (i_result.second > i_result.first)
	{
		return i_contestants.second;
	}
	else
	{
		return "";
	}
}


b3m::MatchId b3m::createNewUniqueId()
{
	static MatchId s_idCounter = 0;

	return ++s_idCounter;
}