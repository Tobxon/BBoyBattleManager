//--------------------------------------------------------------------------------------------------
/**
 * \brief Object that holds the currently handled Tournament for GUI or other classes that life in
 *        an outer layer.
 *        Later loading Tournaments from files it should be loaded into this.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.database:TournamentProxy;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <memory>;
import <vector>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using b3m::common::Tournament;
using b3m::common::Team;
using b3m::common::Match;


class TournamentProxy
{
	using Contestant = Team;

public:
	bool startTournament(const std::vector< Contestant >&);
	std::vector<Match> startRound();

	[[nodiscard]] Tournament* getTournament() const{ return m_curTournament.get(); }

private:
	std::unique_ptr< Tournament > m_curTournament{ nullptr };
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------