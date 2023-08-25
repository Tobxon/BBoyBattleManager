//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.database;
import :TeamsCollector;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

auto b3m::database::readTeams(const ParticipantsDepot&) -> TeamsWithMemberList
{
	TeamsWithMemberList o_teams{{"team2",{{"t2m1",0},{"t2m5", 2}}},{"team4",{{"m2",1},{"m7",2},{"m0",1}}}};

	return o_teams;
}

auto b3m::database::readTeamsWithRanking(const ParticipantsDepot& i_participantsSource) -> TeamsWithRanking
{
	const auto& teamsWithMembers = readTeams(i_participantsSource);

	TeamsWithRanking o_teams;
	for(const auto& [teamName, memberList] : teamsWithMembers)
	{
		const auto& teamRanking = b3m::common::calculateTeamRanking(memberList);

		o_teams.emplace_back(teamName, teamRanking);
	}

	return o_teams;
}


//END OF FILE --------------------------------------------------------------------------------------