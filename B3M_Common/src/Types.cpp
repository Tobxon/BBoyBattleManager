//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.common;
import :participant;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

// Team --------------------------------------------------------------------------------------------
b3m::common::Team::Team(const teamName& i_name, const memberList& i_members)
	: m_name(i_name), m_members(i_members)
{
}

void b3m::common::Team::rename(const teamName&)
{
	//TODO
}

bool b3m::common::Team::addMember(const Participant&)
{
	//TODO
	return false;
}

bool b3m::common::Team::removeMember(const Participant&)
{
	//TODO
	return false;
}

auto b3m::common::Team::getName() const -> teamName
{
	//TODO
	return {};
}

auto b3m::common::Team::getMembers() const -> memberList
{
	//TODO
	return {};
}

std::size_t b3m::common::Team::getNumOfMembers() const
{
	//TODO
	return {};
}


//END OF FILE --------------------------------------------------------------------------------------