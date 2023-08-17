//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.database;
import :ParticipantsDepot;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

bool b3m::database::ParticipantsDepot::newParticipant(const participant_t& i_participant, const participantAttributes_t& i_attributes)
{
    if(m_participants.contains(i_participant))
    {
        return false;
    }

    auto emplaceResult = m_participants.try_emplace(i_participant, i_attributes);

    return emplaceResult.second;
}

bool b3m::database::ParticipantsDepot::updateParticipantsAttributes(const participant_t& i_participant, const attribute_t& i_attribute, const std::string& i_attributeData)
{
    if(m_participants.contains(i_participant))
    {
        auto& curAttributes = m_participants.at(i_participant);
        curAttributes[i_attribute] = i_attributeData;
        return true;
    }

    return false;
}

bool b3m::database::ParticipantsDepot::removeParticipant(const participant_t& i_participant)
{
	if(m_participants.contains(i_participant))
	{
		return m_participants.erase(i_participant);
	}

	return false; //
}

bool b3m::database::ParticipantsDepot::removeParticipantsAttribute(const participant_t&, const attribute_t&)
{
	//TODO
	return false;
}

std::size_t b3m::database::ParticipantsDepot::numOfParticipants() const
{
	//TODO
	return m_participants.size();
}

auto b3m::database::ParticipantsDepot::getParticipant(const participant_t& i_participant) const
-> std::optional<std::pair<participant_t, participantAttributes_t>>
{
	if(m_participants.contains(i_participant))
	{
		const auto& participantsAttributes = m_participants.at(i_participant);
		return std::make_pair(i_participant, participantsAttributes);
	}

	return std::nullopt;
}

auto b3m::database::ParticipantsDepot::getParticipantsAttributes(const participant_t& i_participant) const
-> std::optional< participantAttributes_t >
{
	if(m_participants.contains(i_participant))
	{
		return m_participants.at(i_participant);
	}

	return std::nullopt;
}


//END OF FILE --------------------------------------------------------------------------------------