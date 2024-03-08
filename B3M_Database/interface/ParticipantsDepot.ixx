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
using b3m::common::Team;


class ParticipantsDepot
{
public:
	ParticipantsDepot(const std::map< ParticipantName, ParticipantAttributes>& = {});

	bool newParticipant(const ParticipantName&, const ParticipantAttributes& = {});
	bool updateParticipantsAttributes(const ParticipantName&, const Attribute&, const std::string&);

	bool removeParticipant(const ParticipantName&);
	bool removeParticipantsAttribute(const ParticipantName&, const Attribute&);

	[[nodiscard]] std::size_t numOfParticipants() const;
	[[nodiscard]] std::vector< Team > getTeams() const;
	[[nodiscard]] std::vector< ParticipantName > getParticipantNames() const;
	[[nodiscard]] std::optional< std::pair< ParticipantName, ParticipantAttributes >> getParticipantInformation(const ParticipantName&) const;
	[[nodiscard]] std::optional< ParticipantAttributes > getParticipantsAttributes(const ParticipantName&) const;

	void registerCallback(const std::function<void (const ParticipantsDepot&)>&); //TODO to use of boost.signals2
private:
	std::map< ParticipantName, ParticipantAttributes> m_participants{};

	std::function<void (const ParticipantsDepot&)> m_reportChangesSignal{}; //TODO to use of boost.signals2
	void updateObservers() const;
};



} //namespace b3m::database


//END OF FILE --------------------------------------------------------------------------------------