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
//--------------------------------------------------------------------------------------------------

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



//external Types
using b3m::common::Team;
using b3m::database::ParticipantsDepot;


//free Functions
std::vector< Team > readTeams(const ParticipantsDepot&);



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------