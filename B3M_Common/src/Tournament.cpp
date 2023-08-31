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

bool b3m::common::Tournament::isRunning() const
{
	//TODO
	return false;
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

auto b3m::common::Tournament::createRound() const -> std::vector<Match>
{
	//TODO
	return {};
}


//END OF FILE --------------------------------------------------------------------------------------