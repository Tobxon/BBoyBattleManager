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
import <functional>;

//b3m
import :ParticipantsDepot;
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using b3m::database::ParticipantsDepot;
//using b3m::common::Team;

template< typename container_t >
using container_value_t = container_t::value_type;


//template< typename teamsContainer_t >
//teamsContainer_t readCrewsFromParticipantDepot(const ParticipantsDepot&,
//	std::function<container_value_t<teamsContainer_t>(std::string)>);

using TeamsWithMemberList = std::map< b3m::common::TeamName, b3m::common::memberList >;
using TeamsWithRanking = std::vector<std::pair< b3m::common::TeamName, b3m::common::Ranking >>;

TeamsWithMemberList readTeams(const ParticipantsDepot&);
TeamsWithRanking readTeamsWithRanking(const ParticipantsDepot&);


} //namespace b3m::database


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//TeamsCollector -----------------------------------------------------------------------------------


//free functions -----------------------------------------------------------------------------------
//template< typename teamsContainer_t >
//auto b3m::database::readCrewsFromParticipantDepot(const ParticipantsDepot& i_participants,
//	std::function<container_value_t<teamsContainer_t>(std::string)> i_conversion)
//-> teamsContainer_t
//{
//	teamsContainer_t teams;
//
//	for(const auto& participantWithAttributes : i_participants)
//	{
//		if(participantWithAttributes.second.contains(b3m::common::teamAttribute))
//		{
//			const auto teamOfParticipant =
//					i_conversion(participantWithAttributes.second.at(b3m::common::teamAttribute));
//
//			if (!teams.contains(teamOfParticipant))
//			{
//				teams.append(teamOfParticipant);
//			}
//		}
//	}
//
//	return teams;
//}


//END OF FILE --------------------------------------------------------------------------------------