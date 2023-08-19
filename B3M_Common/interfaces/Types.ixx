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
export module b3m.common:participant;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
import <string>;
import <map>;
import <vector>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::common
{



export using Participant = std::string;

export using ParticipantName = std::string;
export using Attribute = std::string;
export using ParticipantAttributes = std::map< Attribute, std::string >;

export constexpr const char* nameAttribute{ "name" };
export constexpr const char* teamAttribute{ "crew" };

export class Team
{
public:
	using teamName = std::string;
	using memberList = std::vector< Participant >;

	explicit Team(const teamName&, const memberList& = {}); //TODO constructor taking range of Participants?

	void rename(const teamName&);
	bool addMember(const Participant&);
	bool removeMember(const Participant&);

	[[nodiscard]] teamName getName() const;
	[[nodiscard]] memberList getMembers() const;
	[[nodiscard]] std::size_t getNumOfMembers() const;
private:
	std::string m_name{ "unnamed Team" };
	memberList m_members{};
};



} //namespace b3m::common


//END OF FILE --------------------------------------------------------------------------------------