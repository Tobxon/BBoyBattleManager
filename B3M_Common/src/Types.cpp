//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx).


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


module b3m.common;
import :types;
//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

auto b3m::common::calculateTeamRanking(const MemberList& i_members) -> Ranking
{
	Ranking o_teamRanking = 0;

	for (const auto &[participant, ranking]: i_members)
	{
		o_teamRanking += ranking;
	}
	return o_teamRanking;
}


//END OF FILE --------------------------------------------------------------------------------------