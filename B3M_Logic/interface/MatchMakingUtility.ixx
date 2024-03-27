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
using b3m::common::TournamentRound;
using b3m::common::Tournament;


using ContestantRef_t = std::reference_wrapper< const Contestant >;
using ContestantsWithRating = std::map< Contestant::Name_t, TournamentRating >;


ContestantsWithRating calculateRating(const History&, const std::optional<std::vector< Contestant >>& = std::nullopt);
ContestantsRanking getSortedRanking(const History&, const std::vector< Contestant >&);
ContestantsRanking getSortedRanking(const std::vector< Contestant >&, const ContestantsWithRating&);
void sortTeamsByResults(std::vector< Contestant >& i_contestantsToSort, const History& i_history);

ContestantsRanking getCurrentRanking(const Tournament&);

std::vector< ContestantRef_t > getFreeTicketContestants(/*const*/ TournamentRound&, const std::vector< Contestant >&);

bool doesContestantParticipateInRound(/*const*/ TournamentRound&, const Contestant&);



} //namespace b3m::logic


//END OF FILE --------------------------------------------------------------------------------------