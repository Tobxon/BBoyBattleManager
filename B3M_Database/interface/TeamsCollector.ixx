//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the TeamsCollector classs. This class is meant to be a spectator
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



using participantsStorage_t = b3m::database::ParticipantsDepot;
using team_t = b3m::common::Team;

class TeamsCollector
{
public:
	explicit TeamsCollector(participantsStorage_t&);

private:
	std::vector< team_t > m_teams{};

	participantsStorage_t* m_participants{ nullptr };
};

std::vector< team_t > readCrewsFromParticipantDepot(const participantsStorage_t&);



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------