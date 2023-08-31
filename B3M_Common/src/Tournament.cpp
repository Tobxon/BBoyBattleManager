//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.common;
import :Tournament;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//Tournament ---------------------------------------------------------------------------------------
b3m::common::Tournament::Tournament(const std::vector <Contestant>& i_contestants)
	: m_contestants(i_contestants)
{
}

bool b3m::common::Tournament::updateContestants(const std::vector <Contestant>& i_contestants)
{
	if(isRunning())
	{
		return false;
	}

	m_contestants = i_contestants;
	return false;
}

auto b3m::common::Tournament::createRound() -> TournamentRound*
{
	//TODO
	auto curRound = std::make_unique<TournamentRound, std::initializer_list<Match>>(
		{ {Contestant("Kru"),Contestant("Squad")}
		, {Contestant("Team"),Contestant("Kids")}
		, {Contestant("Horde"),Contestant("Mates")}});

	return m_rounds.emplace_back(std::move(curRound)).get();
}

bool b3m::common::Tournament::isRunning() const
{
	//TODO
	return false;
}


//END OF FILE --------------------------------------------------------------------------------------