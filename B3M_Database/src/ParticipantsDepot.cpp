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

void b3m::database::ParticipantsDepot::newParticipant(const participant_t& i_participant, const participantAttributes_t& i_attributes)
{
    m_participants.insert_or_assign(i_participant, i_attributes);
}

bool b3m::database::ParticipantsDepot::updateParticipantsAttributes(const participant_t& i_participant, const attribute_t& i_attribute, const std::string& i_attributeData)
{
    if(m_participants.contains(i_participant))
    {
        auto& curAttributes = m_participants.at(i_participant);
        curAttributes[i_attribute] = i_attributeData;
        return true;
    }
    else
    {
        return false;
    }
}

void b3m::database::ParticipantsDepot::removeParticipant(const participant_t&)
{
	//TODO
}

void b3m::database::ParticipantsDepot::removeParticipantsAttribute(const participant_t&, const attribute_t&)
{
	//TODO
}



//END OF FILE --------------------------------------------------------------------------------------