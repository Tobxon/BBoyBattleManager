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



using Rating = int;


constexpr const char* nameAttribute{ "name" };
constexpr const char* teamAttribute{ "crew" };
constexpr const char* rankingPointsAttribute{ "ranking points" };


//Participant
class Participant
{
public:
	using Name_t = std::string;
	using Team_t = std::string;

	Participant(const Name_t&);

	[[nodiscard]] Name_t getName() const{ return m_name; }
	[[nodiscard]] std::optional< Team_t > getTeam() const;
	[[nodiscard]] Rating getRating() const{ return m_rating; }
private:
	Name_t m_name{"unknown Breaker"};
	Team_t m_team{};
	Rating m_rating{};
};

using Attribute = std::string;
using ParticipantAttributes = std::map< Attribute, std::string >;


//Team
class Team
{
public:
	using Name_t = std::string;

	Team(const Name_t&);
	//TODO range constructor to set members initially

	[[nodiscard]] Name_t getName() const{ return m_name; }
	[[nodiscard]] Rating getRating() const;

private:
	Name_t m_name{"unknown Crew"};
	std::vector< Participant > m_members;
};



} //namespace b3m::common


//END OF FILE --------------------------------------------------------------------------------------