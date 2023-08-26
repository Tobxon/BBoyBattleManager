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
import <functional>;
import <map>;
import <vector>;
import <utility>;

//b3m
import :ParticipantsDepot;
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::database
{



//external Types
using b3m::database::ParticipantsDepot;
using b3m::common::TeamName;
using b3m::common::MemberList;
using b3m::common::Ranking;


//Types
export using TeamsWithMemberList = std::map< TeamName, MemberList >;
export using TeamsWithRanking = std::vector<std::pair< TeamName, Ranking >>;

//free Functions
export TeamsWithMemberList readTeams(const ParticipantsDepot&);
export TeamsWithRanking readTeamsWithRanking(const ParticipantsDepot&);



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------