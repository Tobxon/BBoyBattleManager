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
#include <array>


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
	REQUIRE(participant.setDataSingle(*itCrew, std::string(crewOfParticipant))); //TODO
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
	const auto itCity = std::find(attributes.cbegin(), attributes.cend(), "City");
	//static constexpr std::array< std::string_view, 3 > citiesOfParticipant{ "Tokyo-Yokohama", "Hum", "New York City" }; //TODO
	static const std::vector< std::string > citiesOfParticipant{ 
		"Tokyo-Yokohama", "Hum", "New York City" };
	REQUIRE(participant.setData("City", citiesOfParticipant));
	for (const auto& attribute : attributes)
	{
		if (attribute == *itCity)
		{
			const auto& cityDataOpt = participant.getData(attribute);
			REQUIRE(cityDataOpt.has_value());
			const auto& cityData = cityDataOpt.value();
			REQUIRE(cityData.size() == citiesOfParticipant.size());
			REQUIRE(std::ranges::equal(cityData, citiesOfParticipant));
		}
		else if (attribute == *itCrew)
		{
			//TODO to common function
			const auto& crewDataOpt = participant.getData(attribute);
			REQUIRE(crewDataOpt.has_value());
			const auto& crewData = crewDataOpt.value();
			REQUIRE(crewData.size() == 1);
			REQUIRE(std::ranges::equal(crewData.front(), crewOfParticipant));
		}
		else
		{
			REQUIRE(participant.getData(attribute) == std::nullopt);
		}
	}
}


//END OF FILE --------------------------------------------------------------------------------------