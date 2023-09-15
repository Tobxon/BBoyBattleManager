//--------------------------------------------------------------------------------------------------
/**
 * \brief Utility Functions that may be needed for different match making algorithms.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.logic:MatchMakingUtility;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <map>;
import <optional>;
import <vector>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::logic
{



using b3m::common::History;
using b3m::common::Contestant;
using b3m::common::TournamentRating;


using ContestantsWithRating_t = std::map< Contestant::Name_t, TournamentRating >;

ContestantsWithRating_t calculateRating(const History&, const std::optional<std::vector< Contestant >>& = std::nullopt);



} //namespace b3m::logic


//END OF FILE --------------------------------------------------------------------------------------