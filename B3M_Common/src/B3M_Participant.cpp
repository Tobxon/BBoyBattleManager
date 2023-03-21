//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include <optional>
#include <string>
#include <any>


module b3m.common;
import :participant;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//Participant --------------------------------------------------------------------------------------
b3m::common::Participant::Participant(const name_t& i_name) 
	: m_name(i_name)
{
}

auto b3m::common::Participant::getData(const data_header_t& i_header) const 
-> std::optional< data_entry_t >
{
	if (m_data.contains(i_header))
	{
		return m_data.at(i_header);
	}

	return std::nullopt;
}

bool b3m::common::Participant::setDataSingle(const data_header_t& i_header, 
	const data_element_t& i_value, bool append)
{
	if (append && m_data.contains(i_header))
	{
		m_data.at(i_header).push_back(i_value);

		return true;
	}
	else
	{
		m_data.insert_or_assign(i_header, data_entry_t(1, i_value));

		return true;
	}

	return false;
}

bool b3m::common::Participant::setDataImpl(const data_header_t& i_header, 
	const std::any& i_values, bool append)
{
	if (!i_values.has_value())
	{
		return false;
	}

	auto values = std::any_cast<data_entry_t>(i_values);
	//TODO make assignment work with every iterateable data structure holding the right (or convertible to) type of elements
	if constexpr (std::convertible_to<decltype(values), data_entry_t>)
	{
		if (append && m_data.contains(i_header))
		{
			for (const auto& value : values)
			{
				m_data.at(i_header).push_back(value);
			}

			return true;
		}
		else
		{
			m_data.insert_or_assign(i_header, values);

			return true;
		}
	}

    return false;
}


//END OF FILE --------------------------------------------------------------------------------------