//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

//#include <map>
#include <string>
#include <memory>


module b3m.database;
import :participants_container;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

bool b3m::database::SimpleParticipantsContainer::createParticipant(
	const participant::name_t& i_participantName)
{
	return m_data.try_emplace(i_participantName, 
		std::make_unique<b3m::common::Participant>(i_participantName)).second;
}

bool b3m::database::SimpleParticipantsContainer::removeParticipant(const participant::name_t& i_participantName)
{
	return m_data.erase(i_participantName) > 0;
}


//END OF FILE --------------------------------------------------------------------------------------