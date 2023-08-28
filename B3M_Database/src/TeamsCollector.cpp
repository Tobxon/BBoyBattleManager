//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.database;
import :TeamsCollector;
//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//b3m
import b3m.common;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

//free Functions -----------------------------------------------------------------------------------
auto b3m::database::readTeams(const ParticipantsDepot& i_participantsSource) -> std::vector< Team >
{
	//TODO to ParticipantsDepot method getTeams()
	std::vector< Team > o_teams;

	for(const auto& [participantName, participantsAttributes] : i_participantsSource)
	{
		if(participantsAttributes.contains(b3m::common::teamAttribute))
		{
			const auto& teamName = participantsAttributes.at(b3m::common::teamAttribute);

			const auto rating = [](const auto& i_participantsAttributes) -> b3m::common::Rating {
				if(i_participantsAttributes.contains(b3m::common::ratingAttribute))
				{
					return std::stoi(i_participantsAttributes.at(b3m::common::ratingAttribute));
				}

				return {};
			}(participantsAttributes);

			b3m::common::Participant curParticipant(participantName, rating);

			auto teamIt = std::ranges::find_if(o_teams,
				[teamName](const Team& i_team){ return i_team.getName() == teamName; });
			if(teamIt == o_teams.cend())
			{
				o_teams.push_back(Team(teamName,{curParticipant}));
//				o_teams.emplace_back(teamName,{curParticipant}); //TODO use emplace_back
			}
			else
			{
				teamIt->addMember(curParticipant);
			}
		}
	}

	return o_teams;
}


//END OF FILE --------------------------------------------------------------------------------------