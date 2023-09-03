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
import b3m.logic;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using b3m::common::Tournament;
using b3m::common::Team;
using b3m::common::Match;
using b3m::common::Contestant;
using b3m::common::TournamentRound;
using b3m::logic::MatchMaker;
using b3m::logic::SwissMatchMaker;


class TournamentProxy
{
public:
	bool startTournament(const std::vector< Contestant >&);
	TournamentRound* startRound();

	[[nodiscard]] Tournament* getTournament() const{ return m_curTournament.get(); }

private:
	std::unique_ptr< Tournament > m_curTournament{ nullptr };

	std::unique_ptr< MatchMaker > m_matchMaker{ std::make_unique<SwissMatchMaker>() };
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------