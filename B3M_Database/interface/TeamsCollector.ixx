//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the TeamsCollector class. This class is meant to be a spectator
 *        of a participants collection to filter the information of available teams that can compete
 *        and their members to create tournaments based on these information.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.database:TeamsCollector;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------;

//std
import <vector>;

//b3m
import :ParticipantsDepot;
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using b3m::database::ParticipantsDepot;
using b3m::common::Team;

template< typename teamsContainer_t >
class TeamsCollector
{
public:
	explicit TeamsCollector(ParticipantsDepot&, teamsContainer_t* = nullptr);

private:
	teamsContainer_t* m_teams{ nullptr };

	ParticipantsDepot* m_participants{ nullptr };
};


template< typename teamsContainer_t >
teamsContainer_t readCrewsFromParticipantDepot(const ParticipantsDepot&);



} //namespace b3m::database


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//TeamsCollector -----------------------------------------------------------------------------------
template< typename teamsContainer_t >
b3m::database::TeamsCollector<teamsContainer_t>::TeamsCollector(ParticipantsDepot& i_participants, teamsContainer_t* i_teamsSink)
		: m_participants(&i_participants), m_teams((i_teamsSink) ? i_teamsSink: new teamsContainer_t(readCrewsFromParticipantDepot<teamsContainer_t>(i_participants))) //TODO memory leak when creating container here
{
	if(i_teamsSink)
	{
		*m_teams = readCrewsFromParticipantDepot<teamsContainer_t>(i_participants);
	}

	m_participants->registerCallback([this](const ParticipantsDepot& i_participants){
		*m_teams = readCrewsFromParticipantDepot<teamsContainer_t>(i_participants);
	});

	//TEST - remove in next commit
	m_teams->append("team1");
	m_teams->append("team2");
	m_teams->append("team3");
}


//free functions -----------------------------------------------------------------------------------
template< typename teamsContainer_t >
auto b3m::database::readCrewsFromParticipantDepot(const ParticipantsDepot&) -> teamsContainer_t
{
	//TODO
	return {};
}


//END OF FILE --------------------------------------------------------------------------------------