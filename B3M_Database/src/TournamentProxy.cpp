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
	if(!m_curTournament || !m_matchmaker)
	{
		return nullptr;
	}

	//TODO GOON create Round by using MatchMaker
	auto curRound = std::make_unique<TournamentRound, std::initializer_list<Match>>(
		{ {Contestant("Kru"),Contestant("Squad")}
		, {Contestant("Team"),Contestant("Kids")}
		, {Contestant("Horde"),Contestant("Mates")}});

	return m_curTournament->addNewRound(std::move(curRound));
}


//END OF FILE --------------------------------------------------------------------------------------