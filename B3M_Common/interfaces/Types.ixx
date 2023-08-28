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
class Match
{
public:

private:
	//TODO contestant as template or polymorphic type?
	Team contestantA;
	Team contestantB;
};



} //namespace b3m::common


//END OF FILE --------------------------------------------------------------------------------------