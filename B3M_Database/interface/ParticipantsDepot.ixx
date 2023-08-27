//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the ParticipantDepot class. ParticipantDepot is a class meant to
 *        be a central place to collect participants to be accessible from sub applications
 *        (registration, tournament registration, statistics, ...)
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.database:ParticipantsDepot;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <map>;
import <optional>;
import <functional>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using ParticipantName = b3m::common::Participant::Name_t;
using b3m::common::Attribute;
using b3m::common::ParticipantAttributes;


class ParticipantsDepot
{
public:
	bool newParticipant(const ParticipantName&, const ParticipantAttributes& = {});
	bool updateParticipantsAttributes(const ParticipantName&, const Attribute&, const std::string&);

	bool removeParticipant(const ParticipantName&);
	bool removeParticipantsAttribute(const ParticipantName&, const Attribute&);

	[[nodiscard]] std::size_t numOfParticipants() const;

	[[nodiscard]] std::optional< std::pair< ParticipantName, ParticipantAttributes >> getParticipant(const ParticipantName&) const;
	[[nodiscard]] std::optional< ParticipantAttributes > getParticipantsAttributes(const ParticipantName&) const;

	void registerCallback(const std::function<void (const ParticipantsDepot&)>&); //TODO to use of boost.signals2
private:
	std::map< ParticipantName, ParticipantAttributes> m_participants{};

	std::function<void (const ParticipantsDepot&)> m_reportChangesSignal{}; //TODO to use of boost.signals2
	void updateObservers() const;

public:
	decltype(m_participants)::const_iterator begin() const noexcept; //TODO remove
	decltype(m_participants)::const_iterator cbegin() const noexcept; //TODO remove
	decltype(m_participants)::const_iterator end() const noexcept; //TODO remove
	decltype(m_participants)::const_iterator cend() const noexcept; //TODO remove
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------