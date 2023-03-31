//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include <unordered_map>
#include <string>
#include <memory>
#include <algorithm>
#include <set>
#include <ranges>


module b3m.database;
import :participants_container;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

std::size_t b3m::database::SimpleParticipantsContainer::numOfParticipant() const
{
	return m_participants.size();
}

std::size_t b3m::database::SimpleParticipantsContainer::numOfAttributes() const
{
	std::set< participant::attribute_name_t > attributes;

	for (const auto& participant : m_participants)
	{
		const auto& curAttributes = participant->getAttributes();
		for (const auto& curAttribute : curAttributes)
		{
			attributes.insert(curAttribute);
		}
	}

	return attributes.size();
	//return std::size_t();
}

auto b3m::database::SimpleParticipantsContainer::readAttributeOfParticipant(
	const participant::name_t&, const participant::attribute_name_t&) 
	-> std::optional<participant::attribute_data_t>
{
	return std::optional<participant::attribute_data_t>();
}

bool b3m::database::SimpleParticipantsContainer::createParticipant(
	const participant::name_t& i_participantName)
{
	if (std::ranges::find_if(m_participants, 
		[i_participantName](const decltype(m_participants)::value_type& i_participant)
		{ 
			return i_participant->getName().has_value() && 
				(i_participant->getName().value() == i_participantName); 
		}) != m_participants.cend())
	{
		return false;
	}

	try
	{
		m_participants.push_back(std::make_unique<b3m::common::Participant>(i_participantName));
	}
	catch (const std::bad_alloc&)
	{
		return false;
	}
	return true;
}

bool b3m::database::SimpleParticipantsContainer::removeParticipant(
	const participant::name_t& i_participantName)
{
	const auto itMatchingParticipant = std::ranges::find_if(m_participants, 
		[&i_participantName](const decltype(m_participants)::value_type& i_findParticipant)
		{
			const auto findPaticipantNameOpt = i_findParticipant->getName();
			return (!findPaticipantNameOpt) ? false : findPaticipantNameOpt.value() == i_participantName;
		});

	if (itMatchingParticipant != m_participants.cend())
	{
		m_participants.erase(itMatchingParticipant);
		return true;
	}

	return false;;
}

bool b3m::database::SimpleParticipantsContainer::setAttributeOfParticipant(
	const participant::name_t&, const participant::attribute_name_t&, 
	const participant::attribute_element_t&)
{
	return false;
}

bool b3m::database::SimpleParticipantsContainer::setAttributeOfParticipant(
	const participant::name_t&, const participant::attribute_name_t&, 
	const participant::attribute_data_t&)
{
	return false;
}


//END OF FILE --------------------------------------------------------------------------------------