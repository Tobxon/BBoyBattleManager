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

auto b3m::database::TournamentProxy::startRound() -> TournamentRound*
{
	if(!m_curTournament)
	{
		return nullptr;
	}

	const auto contestants = m_curTournament->getContestants();

	TournamentRound curRound;
	for(std::size_t i = 1; i < contestants.size(); i = i+2)
	{
		curRound.emplace_back(contestants.at(i-1),contestants.at(i));
	}
	//TODO create Round by using MatchMaker

	return m_curTournament->addNewRound(std::make_unique<TournamentRound>(curRound));
}


//END OF FILE --------------------------------------------------------------------------------------