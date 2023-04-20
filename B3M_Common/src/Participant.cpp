//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include <optional>
#include <string>
#include <vector>
#include <ranges>


module b3m.common;
import :participant;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//Participant --------------------------------------------------------------------------------------
b3m::common::Participant::Participant(const name_t& i_name) 
	: m_attributes()
{
	m_attributes.setAttribute(nameAttribute, i_name); //TODO to initialization
}

auto b3m::common::Participant::getName() const -> std::optional< name_t >
{
	const auto& nameOpt = m_attributes.getAttributeData(nameAttribute);

	if (nameOpt)
	{
		return nameOpt.value().front();
	}
	return std::nullopt;
}

auto b3m::common::Participant::getAttributes() const -> std::vector<attribute_name_t>
{
	return m_attributes.getAttributes();
}

auto b3m::common::Participant::getAttributeData(const attribute_name_t& i_attribute) -> 
std::optional< attribute_data_t >
{
	return m_attributes.getAttributeData(i_attribute);
}

bool b3m::common::Participant::setAttributeSingle(const attribute_name_t& i_attribute, 
	const attribute_data_t::value_type& i_data, bool i_append)
{
	return m_attributes.setAttribute(i_attribute, i_data, i_append);
}

bool b3m::common::Participant::setAttributeMulti(const attribute_name_t& i_attribute, 
	const attribute_data_t& i_data, bool i_append)
{
	return m_attributes.setAttribute(i_attribute, i_data, i_append);
}


//END OF FILE --------------------------------------------------------------------------------------