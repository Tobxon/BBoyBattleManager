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
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using b3m::logic::getCurrentRanking;


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

	auto curRound = std::make_unique< TournamentRound >(m_matchMaker->createRound(*m_curTournament));

	return m_curTournament->addNewRound(std::move(curRound));
}

auto b3m::database::TournamentProxy::getCurrentContestantsRanking() const -> SortedContestantsRanking
{
	return getCurrentRanking(*m_curTournament);
}

void b3m::database::TournamentProxy::setMatchMaker(std::unique_ptr< MatchMaker > i_newMatchMaker)
{
	m_matchMaker = std::move(i_newMatchMaker);
}


//END OF FILE --------------------------------------------------------------------------------------