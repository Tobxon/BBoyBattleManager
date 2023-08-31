//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the Tournament class. Tournament is the main class when
 *        processing with knowledge of a tournament holding multiple rounds.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.common:Tournament;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <vector>;

//b3m
import :types;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::common
{



using b3m::common::Match;
using TournamentRound = std::vector<Match>;


class Tournament
{
	using Contestant = b3m::common::Team;

public:
	explicit Tournament(const std::vector <Contestant>&); //TODO to ranges?

	[[nodiscard]] bool isRunning() const;

	bool updateContestants(const std::vector <Contestant>&); //TODO to ranges?

	TournamentRound createRound() const;
private:
	std::vector <Contestant> m_contestants;
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------