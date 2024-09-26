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

	updateObservers();

	return emplaceResult.second;
}

bool b3m::database::ParticipantsDepot::updateParticipantsAttributes(const participant_t& i_participant, const attribute_t& i_attribute, const std::string& i_attributeData)
{
	if(m_participants.contains(i_participant))
	{
		if(i_attribute == b3m::common::nameAttribute)
		{
			auto participantElement = m_participants.extract(i_participant);
			participantElement.key() = i_attributeData;
			m_participants.insert(std::move(participantElement));
		} else {
			m_participants.at(i_participant).insert_or_assign(i_attribute, i_attributeData);
		}

		updateObservers();

		return true;
	}

	return false;
}

bool b3m::database::ParticipantsDepot::removeParticipant(const participant_t& i_participant)
{
	if(m_participants.contains(i_participant))
	{
		const auto eraseResult = m_participants.erase(i_participant);
		updateObservers();
		return eraseResult;
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

auto b3m::database::ParticipantsDepot::begin() const noexcept -> decltype(m_participants)::const_iterator
{
	return m_participants.cbegin();
}

auto b3m::database::ParticipantsDepot::cbegin() const noexcept -> decltype(m_participants)::const_iterator
{
	return m_participants.cbegin();
}

auto b3m::database::ParticipantsDepot::end() const noexcept -> decltype(m_participants)::const_iterator
{
	return m_participants.cend();
}

auto b3m::database::ParticipantsDepot::cend() const noexcept -> decltype(m_participants)::const_iterator
{
	return m_participants.cend();
}

//TODO to use of boost.signals2 / proper observer pattern implementation
void b3m::database::ParticipantsDepot::registerCallback(const std::function<void (const ParticipantsDepot&)>& i_callback)
{
	m_reportChangesSignal = i_callback;
}

void b3m::database::ParticipantsDepot::updateObservers() const
{
	if(m_reportChangesSignal)
	{
		m_reportChangesSignal(*this);
	}
}


//END OF FILE --------------------------------------------------------------------------------------