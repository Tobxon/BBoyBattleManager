//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for basic types used across the whole program.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.common:types;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <string>;
import <map>;
import <vector>;
import <optional>;
import <utility>;
import <functional>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::common
{



constexpr const char* nameAttribute{ "name" };
constexpr const char* teamAttribute{ "crew" };
constexpr const char* ratingAttribute{ "ranking points" };


using Rating = int;
using Attribute = std::string;
using ParticipantAttributes = std::map< Attribute, std::string >;
class Participant;


//Team
class Team
{
public:
	using Name_t = std::string;

	explicit Team(const Name_t&, const std::vector< Participant >& = {});
	//TODO range constructor to set members initially

	[[nodiscard]] Name_t getName() const{ return m_name; }
	[[nodiscard]] Rating getRating() const;

	bool addMember(Participant&);

	bool operator==(const Team& i_other) const;
private:
	Name_t m_name{"unknown Crew"};
	std::vector< Participant > m_members;
};


//Participant
class Participant
{
public:
	using Name_t = std::string;
	using Team_t = Team*; //TODO team as pointer to the Team object?

	Participant(const Name_t&, const Team_t&, const Rating&);
	explicit Participant(const Name_t&, const Team_t& = {});
	Participant(const Name_t&, const Rating& = {});

	[[nodiscard]] Name_t getName() const{ return m_name; }
	[[nodiscard]] std::optional< Team::Name_t > getTeam() const;
	[[nodiscard]] Rating getRating() const{ return m_rating; }

	bool setTeam(const Team_t&);
//	bool setTeam(const Team::Name_t&);
private:
	Name_t m_name{"unknown Breaker"};
	Team_t m_team{};
	Rating m_rating{};
};


//Match
using Contestant = b3m::common::Team; //TODO contestant as template or polymorphic type?
using Judgement = float;


//TODO enable Matches with 3 contestants
class Match
{
public:
	enum class Result{
		win,
		loose,
		tie,
		bye
	};
	using FullResult = std::pair< Result, Judgement >;

	Match(const Contestant&, const Contestant&);

	[[nodiscard]] std::pair< Contestant::Name_t, Contestant::Name_t > getContestantNames() const;
	[[nodiscard]] bool isFinished() const;
	[[nodiscard]] std::optional< std::map< Contestant::Name_t, FullResult >> getResults() const;

	bool setResult(const Contestant::Name_t&, const Judgement&);
	bool clearResult();

	bool changeContestant(const Contestant::Name_t& i_oldContestantName, const Contestant::Name_t& i_newContestant);
	mutable std::function< void(const std::pair< Contestant::Name_t, Contestant::Name_t >&) > m_contestantsChangedCallback; //TODO
private:
	std::pair< Contestant::Name_t, Contestant::Name_t > m_contestants; //TODO to reference_wrapper< Contestant > oder Contestant::Name_t
	std::pair< std::optional< Judgement >, std::optional< Judgement >> m_result{ std::nullopt, std::nullopt };
};

constexpr Match::FullResult freeTicket{ Match::Result::bye, 1.5 };


struct TournamentRating
{
	int m_numOfWins{ 0 };
	int m_numOfTies{ 0 };
	int m_numOfLooses{ 0 };
	int m_numOfByes{ 0 };

	Judgement m_numOfVotes{ 0 };

	TournamentRating& operator+=(const Match::FullResult&);
	bool operator==(const TournamentRating&) const = default;
	//TODO implement ordering?

	[[nodiscard]] int getCombinedRating() const;
	[[nodiscard]] int getNumberOfRatings() const;
};



} //namespace b3m::common


//END OF FILE --------------------------------------------------------------------------------------