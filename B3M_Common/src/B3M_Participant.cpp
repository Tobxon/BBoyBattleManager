//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include <optional>


module b3m.common;
import :participant;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::common::Participant::Participant(const name_t& i_name) 
	: m_name(i_name)
{
}

auto b3m::common::Participant::getData(const data_header_t&) const -> std::optional< data_entry_t >
{
	//TODO
	return std::nullopt;
}

bool b3m::common::Participant::setData(const data_header_t&, const data_element_t&, bool append)
{
	//TODO
	return false;
}

bool b3m::common::Participant::setData(const data_header_t&, const data_entry_t&, bool append)
{
	//TODO
    return false;
}


//END OF FILE --------------------------------------------------------------------------------------