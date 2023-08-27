//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.common;
import :types;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <numeric>;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//Participant --------------------------------------------------------------------------------------
b3m::common::Participant::Participant(const Name_t& i_name)
	: m_name(i_name)
{
}

auto b3m::common::Participant::getTeam() const -> std::optional< Team_t >
{
	if(!m_team.empty())
	{
		return m_team;
	}

	return std::nullopt;
}


//Team ---------------------------------------------------------------------------------------------
b3m::common::Team::Team(const Name_t& i_name)
	: m_name(i_name)
{
}

auto b3m::common::Team::getRating() const -> Rating
{
	return std::accumulate(m_members.cbegin(), m_members.cend(), 0,
		[](Rating i_curSum, const Participant& i_participant){
			return i_curSum + i_participant.getRating();
	});
}



//END OF FILE --------------------------------------------------------------------------------------