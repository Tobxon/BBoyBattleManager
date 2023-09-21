//--------------------------------------------------------------------------------------------------
/**
 * \brief MatchMaker is the base class for match making algorithm.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.logic:MatchMaker;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <vector>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::logic
{



using b3m::common::TournamentRound;
using b3m::common::Tournament;
using b3m::common::Contestant;
using b3m::common::History;
using b3m::common::ContestantsRanking;
using b3m::common::SortedContestantsRanking;



class MatchMaker
{
public:
	virtual ~MatchMaker() = default;

	virtual TournamentRound createRound(const Tournament&) = 0;
	virtual SortedContestantsRanking getCurrentRanking(const Tournament&) const = 0; //TODO let Matchmaker or an independent RankingJudge decide how contestants get ranked!
};


//SwissMatchMaker ----------------------------------------------------------------------------------
class SwissMatchMaker : public MatchMaker
{
public:
	TournamentRound createRound(const Tournament&) override;
	SortedContestantsRanking getCurrentRanking(const Tournament&) const override;
};


//KOMatchMaker (classic K.O. Tournament) -----------------------------------------------------------
class KOMatchMaker : public SwissMatchMaker //TODO inherit from MatchMaker
{
public:
	explicit KOMatchMaker(unsigned int = 4);

	TournamentRound createRound(const Tournament&) override;
private:
	unsigned int m_currentNumOfContestants{4};
};



} //namespace b3m::logic


//END OF FILE --------------------------------------------------------------------------------------