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
using b3m::common::ContestantsRanking;
using b3m::common::SortedContestantsRanking;


//using ContestantsRanking = std::map< Contestant::Name_t, TournamentRating, std::function<bool(const Contestant::Name_t&, const Contestant::Name_t&)>>;


ContestantsRanking calculateRating(const History&, const std::optional<std::vector< Contestant >>& = std::nullopt);
SortedContestantsRanking getSortedRanking(const History&, const std::vector< Contestant >&);
SortedContestantsRanking getSortedRanking(const std::vector< Contestant >&, const ContestantsRanking&);
void sortTeamsByResults(std::vector< Contestant >& i_contestantsToSort, const History& i_history);



} //namespace b3m::logic


//END OF FILE --------------------------------------------------------------------------------------