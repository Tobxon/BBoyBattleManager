//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for basic types used across the whole program.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.common:participant;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
import <string>;
import <map>;
import <vector>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::common
{



using Participant = std::string;

using ParticipantName = std::string;
using Attribute = std::string;
using ParticipantAttributes = std::map< Attribute, std::string >;

constexpr const char* nameAttribute{ "name" };
constexpr const char* teamAttribute{ "crew" };
constexpr const char* rankingPointsAttribute{ "ranking points" };



} //namespace b3m::common


//END OF FILE --------------------------------------------------------------------------------------