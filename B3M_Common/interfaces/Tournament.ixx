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
import <functional>;
import <string>;

//b3m
import :types;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::common
{



class TournamentRound;


using b3m::common::Match;
using b3m::common::Contestant;
using History = std::vector< TournamentRound* >;
using ContestantsRanking = std::map< Contestant::Name_t, TournamentRating >;
//using SortedContestantsRanking = std::map< Contestant::Name_t, TournamentRating, std::function<bool(const Contestant::Name_t&, const Contestant::Name_t&)>>;
using SortedContestantsRanking = std::vector<std::pair< Contestant::Name_t, TournamentRating >>;


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


class TournamentRound
{
public:
	explicit TournamentRound(const Tournament&, const std::string& = {});

	[[nodiscard]] std::vector< Contestant > getContestants() const;
	[[nodiscard]] const Tournament& getTournament() const{ return *m_tournament; } //TODO bad practice?
	[[nodiscard]] std::string getTitle() const{ return m_title; } //TODO bad practice?
	[[nodiscard]] bool isFinished() const;
	[[nodiscard]] std::vector< Match >& getMatches(){ return m_matches; }

	void setTitle(const std::string&);
	void addMatch(const Match&);
	void addMatch(Match&&);//TODO addMatch with Match-ctor-input arguments to construct it in place addMatch(const std::vector< Contestant >&)

private:
	const Tournament* m_tournament{  }; //must never be nullptr //TODO to gsl

	std::vector<Match> m_matches;

	std::string m_title;
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------