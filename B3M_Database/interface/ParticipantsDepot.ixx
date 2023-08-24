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
import <string>;
import <optional>;
import <functional>;

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace b3m::database
{



using participant_t = b3m::common::Participant;
using attribute_t = b3m::common::Attribute;
using participantAttributes_t = b3m::common::ParticipantAttributes;

class ParticipantsDepot
{
public:
	bool newParticipant(const participant_t&, const participantAttributes_t& = {});
	bool updateParticipantsAttributes(const participant_t&, const attribute_t&, const std::string&);

	bool removeParticipant(const participant_t&);
	bool removeParticipantsAttribute(const participant_t&, const attribute_t&);

	[[nodiscard]] std::size_t numOfParticipants() const;

	[[nodiscard]] std::optional< std::pair< participant_t, participantAttributes_t >> getParticipant(const participant_t&) const;
	[[nodiscard]] std::optional< participantAttributes_t > getParticipantsAttributes(const participant_t&) const;

	void registerCallback(const std::function<void (const ParticipantsDepot&)>&); //TODO to use of boost
private:
	std::map< participant_t, participantAttributes_t> m_participants{};

	std::function<void (const ParticipantsDepot&)> m_reportChangesSignal{}; //TODO to use of boost
	void updateObservers() const;

public:
	decltype(m_participants)::const_iterator begin() const noexcept;
	decltype(m_participants)::const_iterator cbegin() const noexcept;
	decltype(m_participants)::const_iterator end() const noexcept;
	decltype(m_participants)::const_iterator cend() const noexcept;
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------