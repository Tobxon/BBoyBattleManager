//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.database;
import :participants_container;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

bool b3m::database::SimpleParticipantsContainer::addParticipant(const b3m::common::Participant& i_participant)
{
	return m_data.insert(i_participant).second;
}

bool b3m::database::SimpleParticipantsContainer::removeParticipant(const b3m::common::Participant& i_participant)
{
	return m_data.erase(i_participant) > 0;
}

bool b3m::database::SimpleParticipantsContainer::cmpParticipantsOnlyName(
	const participant& i_a, const participant& i_b)
{
	const auto cmpResult = i_a.getName().compare(i_b.getName());
	if (cmpResult < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//END OF FILE --------------------------------------------------------------------------------------