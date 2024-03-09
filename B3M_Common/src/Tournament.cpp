//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.common;
import :Tournament;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
import <algorithm>;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//Tournament ---------------------------------------------------------------------------------------
b3m::common::Tournament::Tournament(const std::vector <Contestant>& i_contestants)
	: m_contestants(i_contestants)
{
}

bool b3m::common::Tournament::updateContestants(const std::vector <Contestant>& i_contestants)
{
	if(isRunning())
	{
		return false;
	}

	m_contestants = i_contestants;
	return false;
}

auto b3m::common::Tournament::addNewRound(std::unique_ptr<TournamentRound> i_newRound) -> TournamentRound*
{
	return m_rounds.emplace_back(std::move(i_newRound)).get();
}

bool b3m::common::Tournament::isRunning() const
{
	return !m_rounds.empty();
}

auto b3m::common::Tournament::getHistory() const -> History
{
	History o_rounds;
	for(auto& round : m_rounds)
	{
		if(round->isFinished())
		{
			o_rounds.emplace_back(round.get());
		}
	}
	return o_rounds;
}

b3m::common::TournamentRound::TournamentRound(const Tournament& i_tournament, const std::string& i_title)
	: m_tournament(&i_tournament), m_title(i_title)
{
}

auto b3m::common::TournamentRound::getContestants() const -> std::vector< Contestant >
{
	return m_tournament->getContestants();
}

bool b3m::common::TournamentRound::isFinished() const
{
	return std::ranges::find_if(m_matches, [](const Match& i_match){ return !i_match.isFinished(); }) == m_matches.cend();
}

void b3m::common::TournamentRound::setTitle(const std::string& i_newTitle)
{
	m_title = i_newTitle;
}

void b3m::common::TournamentRound::addMatch(const Match& i_match)
{
	m_matches.push_back(i_match);
}

void b3m::common::TournamentRound::addMatch(Match&& i_match)
{
	m_matches.push_back(std::move(i_match));
}


//END OF FILE --------------------------------------------------------------------------------------