//--------------------------------------------------------------------------------------------------
/**
 * \brief Unit Tests for the Participant class.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.common;

//Catch2 - Test Framework
#include <catch2/catch_test_macros.hpp>

//std
#include <string_view>
#include <string>
#include <vector>
#include <optional>


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("b3m Participant - simple constructor test", "[B3M, Participant, Constructor]")
{
	REQUIRE_NOTHROW(b3m::common::Participant{ "AnyBot" });
}

TEST_CASE("b3m Participant - creating a participant and check for valid state")
{
	static constexpr std::string_view firstName{ "npc1" };
	b3m::common::Participant firstParticipant{ std::string(firstName) };
	b3m::common::Participant anotherSameParticipant{ std::string(firstName) };

	REQUIRE_NOTHROW(firstParticipant.getName() == std::string(firstName));
}

TEST_CASE("b3m Participant - create participants and set and check basic data")
{
	static constexpr std::string_view nameOfParticipant{ "Striker" };
	b3m::common::Participant participant{ std::string(nameOfParticipant) };

	static const std::vector< std::string > attributes{ "Crew", "City" };
	for (const auto& attribute : attributes)
	{
		REQUIRE(participant.getData(attribute) == std::nullopt);
	}

	const auto itCrew = std::find(attributes.cbegin(), attributes.cend(), "Crew");
	static constexpr std::string_view crewOfParticipant{ "Powerheadz" };
	participant.setData(*itCrew, std::string(crewOfParticipant) );
	for (const auto& attribute : attributes)
	{
		if (attribute == *itCrew)
		{
			const auto& crewDataOpt = participant.getData(attribute);
			REQUIRE(crewDataOpt.has_value());
			const auto& crewData = crewDataOpt.value();
			REQUIRE(crewData.size() == 1);
			REQUIRE(crewData.front() == std::string(crewOfParticipant));
		}
		else
		{
			REQUIRE(participant.getData(attribute) == std::nullopt);
		}
	}

	//TODO add a data with multiple entrys
}


//END OF FILE --------------------------------------------------------------------------------------