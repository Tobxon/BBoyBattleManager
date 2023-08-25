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

auto b3m::database::readTeams(const ParticipantsDepot& i_participantsSource) -> TeamsWithMemberList
{
	TeamsWithMemberList o_teams;

	for(const auto& [participant, participantsAttributes] : i_participantsSource)
	{
		if(participantsAttributes.contains(b3m::common::teamAttribute))
		{
			const auto& team = participantsAttributes.at(b3m::common::teamAttribute);

			const auto ranking = [](const auto& i_participantsAttributes){
				if(i_participantsAttributes.contains(b3m::common::rankingPointsAttribute))
				{
					return std::stoi(i_participantsAttributes.at(b3m::common::rankingPointsAttribute));
				}

				return 0;
			}(participantsAttributes);

			if(o_teams.contains(team))
			{
				o_teams.at(team).emplace_back(participant, ranking);
			}
			else
			{

				const b3m::common::memberList members{{participant, ranking}};
				o_teams.try_emplace(team, members);
			}
		}
	}

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