//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.database;

import :TournamentProxy;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

bool b3m::database::TournamentProxy::startTournament(const std::vector <Contestant>& i_contestants)
{
	if(m_curTournament && m_curTournament->isRunning())
	{
		return false;
	}

	if(m_curTournament && !m_curTournament->isRunning())
	{
		return m_curTournament->updateContestants(i_contestants);
	}

	m_curTournament = std::make_unique<Tournament>(i_contestants);
	return true;
}

auto b3m::database::TournamentProxy::startRound() -> std::vector<Match>
{
	if(m_curTournament)
	{
		//TODO
//		return m_curTournament->createRound();
		return {Match(Contestant("Crew left"),Contestant("Crew right"))};
	}

	return {};
}


//END OF FILE --------------------------------------------------------------------------------------