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
b3m::common::Participant::Participant(const Name_t& i_name, const Team_t& i_team, const Rating& i_rating)
	: m_name(i_name), m_team(i_team), m_rating(i_rating)
{}

b3m::common::Participant::Participant(const Name_t& i_name, const Team_t& i_team)
	: Participant(i_name, i_team, {})
{}

b3m::common::Participant::Participant(const Name_t& i_name, const Rating& i_rating)
		: Participant(i_name, {}, i_rating)
{}

auto b3m::common::Participant::getTeam() const -> std::optional< Team::Name_t >
{
	if(m_team)
	{
		return m_team->getName();
	}

	return std::nullopt;
}

bool b3m::common::Participant::setTeam(const Team_t& i_team)
{
	m_team = i_team;
	return true;
}


//Team ---------------------------------------------------------------------------------------------
b3m::common::Team::Team(const Name_t& i_name, const std::vector< Participant >& i_members)
	: m_name(i_name), m_members(i_members)
{
}

auto b3m::common::Team::getRating() const -> Rating
{
	return std::accumulate(m_members.cbegin(), m_members.cend(), 0,
		[](Rating i_curSum, const Participant& i_participant){
			return i_curSum + i_participant.getRating();
	});
}

bool b3m::common::Team::addMember(Participant& i_newMember)
{
	if(i_newMember.setTeam(this))
	{
		m_members.push_back(i_newMember);
		return true;
	}
	return false;
}

//Match --------------------------------------------------------------------------------------------
b3m::common::Match::Match(const Contestant& i_contestantA, const Contestant& i_contestantB)
	: m_contestants{i_contestantA, i_contestantB}
{
}

auto b3m::common::Match::getContestantNames() const
-> std::pair< Contestant::Name_t, Contestant::Name_t >
{
	return { m_contestants.first.getName(), m_contestants.second.getName() };
}

bool b3m::common::Match::setResult(const Contestant::Name_t& i_contestantName, const Judgement& i_result)
{
	if(i_contestantName == m_contestants.first.getName())
	{
		m_result.first = i_result;
	}
	else if(i_contestantName == m_contestants.second.getName())
	{
		m_result.second = i_result;
	}
	else
	{
		return false;
	}

	return true;
}

bool b3m::common::Match::isFinished() const
{
	return m_result.first.has_value() && m_result.second.has_value();
}

auto b3m::common::Match::getResults() const
-> std::optional< std::map< Contestant::Name_t, Result >>
{
	if(!isFinished())
	{
		return std::nullopt;
	}

	const auto resultFirst = (m_result.first > m_result.second) ? Result::win : (m_result.first < m_result.second) ? Result::loose : Result::tie;
	const auto resultSecond = (m_result.second > m_result.first) ? Result::win : (m_result.second < m_result.first) ? Result::loose : Result::tie;
	return std::map< Contestant::Name_t, Result >{
		{ m_contestants.first.getName(), resultFirst}
		,{ m_contestants.second.getName(), resultSecond}};
}


//END OF FILE --------------------------------------------------------------------------------------