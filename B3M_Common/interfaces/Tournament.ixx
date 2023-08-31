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
import <memory>;

//b3m
import :types;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::common
{



using b3m::common::Match;
using TournamentRound = std::vector<Match>;
using b3m::common::Contestant;


class Tournament
{
public:
	explicit Tournament(const std::vector <Contestant>&); //TODO to ranges?

	bool updateContestants(const std::vector <Contestant>&); //TODO to ranges?

	TournamentRound* createRound(); //TODO const and list round in other object?

	[[nodiscard]] bool isRunning() const;
private:
	std::vector< Contestant > m_contestants;

	std::vector<std::unique_ptr< TournamentRound >> m_rounds;
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------