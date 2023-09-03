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
using History = std::vector< TournamentRound* >;


class Tournament
{
public:
	explicit Tournament(const std::vector <Contestant>&); //TODO to ranges?

	bool updateContestants(const std::vector <Contestant>&); //TODO to ranges?
	//TODO update contestants when registered Teams change?

	TournamentRound* addNewRound(std::unique_ptr<TournamentRound>); //TODO to slot?

	[[nodiscard]] bool isRunning() const;
	[[nodiscard]] std::vector< Contestant > getContestants() const{ return m_contestants; }

	[[nodiscard]] History getHistory() const;
private:
	std::vector< Contestant > m_contestants;

	std::vector<std::unique_ptr< TournamentRound >> m_rounds;
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------