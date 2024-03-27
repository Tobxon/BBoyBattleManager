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
b3m::common::Participant::Participant(const Name_t& i_name, const Team* i_team, const Rating& i_rating)
	: m_name(i_name), m_team(i_team), m_rating(i_rating)
{}

b3m::common::Participant::Participant(const Name_t& i_name, const Team* i_team)
	: Participant(i_name, i_team, {})
{}

b3m::common::Participant::Participant(const Name_t& i_name, const Rating& i_rating)
	: Participant(i_name, nullptr, i_rating)
{}

b3m::common::Participant::Participant(const Name_t& i_name, const Team& i_team)
	: Participant(i_name, &i_team)
{}

auto b3m::common::Participant::getTeamName() const -> std::optional< Team::Name_t >
{
	if(m_team)
	{
		return m_team->getName();
	}

	return std::nullopt;
}

bool b3m::common::Participant::changeTeam(const Team& i_team)
{
	m_team = &i_team;
	return true;
}

bool b3m::common::Participant::removeTeam()
{
	m_team = nullptr;
	return true;
}

void b3m::common::Participant::setRating(const Rating& i_rating)
{
	m_rating = i_rating;
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
	if(i_newMember.changeTeam(*this))
	{
		m_members.push_back(i_newMember);
		return true;
	}
	return false;
}

bool b3m::common::Team::operator==(const Team& i_other) const
{
	return i_other.m_name == m_name;
}

//Match --------------------------------------------------------------------------------------------
b3m::common::Match::Match(const Contestant& i_contestantA, const Contestant& i_contestantB)
	: m_contestants(i_contestantA.getName(), i_contestantB.getName())
{
}

auto b3m::common::Match::getContestantNames() const
-> std::pair< Contestant::Name_t, Contestant::Name_t >
{
	return { m_contestants.first, m_contestants.second };
}

bool b3m::common::Match::setResult(const Contestant::Name_t& i_contestantName, const Judgement& i_result)
{
	if(i_contestantName == m_contestants.first)
	{
		m_result.first = i_result;
	}
	else if(i_contestantName == m_contestants.second)
	{
		m_result.second = i_result;
	}
	else
	{
		return false;
	}

	if(m_resultsChangedCallback){ m_resultsChangedCallback(m_result); }
	return true;
}

bool b3m::common::Match::clearResult()
{
	m_result = {std::nullopt, std::nullopt};

	return true;
}

bool b3m::common::Match::changeContestant(const Contestant::Name_t& i_oldContestantName, const Contestant::Name_t& i_newContestant)
{
	if(bool isFirst = (m_contestants.first == i_oldContestantName), isSecond = (m_contestants.second == i_oldContestantName);
			isFirst || isSecond)
	{
		if(isFirst)
		{
			if(m_contestants.second == i_newContestant)
			{
				return false;
			}
			m_contestants.first = i_newContestant;
		}
		else if(isSecond)
		{
			if(m_contestants.first == i_newContestant)
			{
				return false;
			}
			m_contestants.second = i_newContestant;
		}

		if(m_contestantsChangedCallback){ m_contestantsChangedCallback(m_contestants); }

		return true;
	}

	return false;
}

bool b3m::common::Match::isFinished() const
{
	return m_result.first.has_value() && m_result.second.has_value();
}

auto b3m::common::Match::getResults() const
-> std::optional< std::map< Contestant::Name_t, FullResult >>
{
	if(!isFinished())
	{
		return std::nullopt;
	}

	const auto resultFirst = (m_result.first > m_result.second) ? Result::win : (m_result.first < m_result.second) ? Result::loose : Result::tie;
	const auto resultSecond = (resultFirst == Result::loose) ? Result::win : (resultFirst == Result::win) ? Result::loose : Result::tie;
	return std::map< Contestant::Name_t, FullResult >{
		{ m_contestants.first, { resultFirst, m_result.first.value() }}
		,{ m_contestants.second, { resultSecond, m_result.second.value() }}};
}


//TournamentRating ---------------------------------------------------------------------------------
auto b3m::common::TournamentRating::operator+=(const Match::FullResult& i_newResult) -> TournamentRating&
{
	switch (i_newResult.first)
	{
		case Match::Result::win:
			++m_numOfWins;
			break;
		case Match::Result::loose:
			++m_numOfLooses;
			break;
		case Match::Result::tie:
			++m_numOfTies;
			break;
		case Match::Result::bye:
			++m_numOfByes;
			break;
	}

	m_numOfVotes += i_newResult.second;

	return *this;
}

int b3m::common::TournamentRating::getCombinedRating() const
{
	return m_numOfWins*3 + m_numOfTies*1;
}

int b3m::common::TournamentRating::getNumberOfRatings() const
{
	return m_numOfWins + m_numOfTies + m_numOfLooses;
}


//END OF FILE --------------------------------------------------------------------------------------