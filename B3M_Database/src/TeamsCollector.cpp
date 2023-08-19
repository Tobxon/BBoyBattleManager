//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.database;
import :TeamsCollector;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//TeamsCollector -----------------------------------------------------------------------------------
b3m::database::TeamsCollector::TeamsCollector(participantsStorage_t& i_participants)
	: m_participants(&i_participants), m_teams(readCrewsFromParticipantDepot(i_participants))
{
	m_participants->registerCallback([this](const participantsStorage_t& i_participants){
		m_teams = readCrewsFromParticipantDepot(i_participants);
	});
}

//free functions -----------------------------------------------------------------------------------
auto b3m::database::readCrewsFromParticipantDepot(const b3m::database::participantsStorage_t &) -> std::vector< team_t >
{
	//TODO
	return {};
}


//END OF FILE --------------------------------------------------------------------------------------