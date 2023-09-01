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

	auto curRound = std::make_unique< TournamentRound >();
	for(std::size_t i = 1; i < contestants.size(); i = i+2)
	{
		const auto& contestantA = contestants.at(i-1);
		const auto& contestantB = contestants.at(i);
		curRound->emplace_back(contestantA, contestantB);
	}
	//TODO create Round by using MatchMaker

	return m_curTournament->addNewRound(std::move(curRound));
}


//END OF FILE --------------------------------------------------------------------------------------