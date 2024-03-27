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
import <catch2/catch_test_macros.hpp>;

//std
import <string_view>;
import <string>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using b3m::common::Participant;
using b3m::common::Team;
using b3m::common::Rating;


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

//Participant --------------------------------------------------------------------------------------
TEST_CASE("b3m Participant - simple constructor test", "[B3M, Participant, Constructor]")
{
	REQUIRE_NOTHROW(Participant( "AnyBot" ));
}

TEST_CASE("Participants are identified by their name")
{
	static constexpr std::string_view firstName{ "npc1" };
	Participant firstParticipant{ std::string(firstName) };

	CHECK(firstParticipant.getName() == std::string(firstName));
}

TEST_CASE("default Participants only have a name")
{
	Participant dut{ "Alfred" };

	CHECK(!dut.getTeamName());
	CHECK(dut.getRating() == b3m::common::emptyRating);
}

TEST_CASE("Participants can be member of a Team")
{
	Team blueTeam("Blue");

	SECTION("Team is directly passed to Participant while constructing")
	{
		Participant dut{ "Player1", blueTeam };

		const auto& possibleTeamName = dut.getTeamName();
		REQUIRE(possibleTeamName);
		CHECK(possibleTeamName.value() == blueTeam.getName());
	}

	SECTION("Team can be set and changed after constructing")
	{
		std::string newPlayerName{ "SlimShady" };
		Participant dut{ newPlayerName };

		REQUIRE(!dut.getTeamName());

		Team redTeam{ "Red" };
		REQUIRE(dut.changeTeam(redTeam));
		{
			const auto& possibleTeamName = dut.getTeamName();
			REQUIRE(possibleTeamName);
			CHECK(possibleTeamName.value() == redTeam.getName());
		}

		REQUIRE(dut.changeTeam(blueTeam));
		{
			const auto& possibleTeamName = dut.getTeamName();
			REQUIRE(possibleTeamName);
			CHECK(possibleTeamName.value() == blueTeam.getName());
		}
	}
}

TEST_CASE("Participants can have a Rating used for Ranking these later")
{
	SECTION("set Rating while constructing")
	{
		static constexpr Rating testRating = 17;
		Participant dut{ "B-Girl Kotya", testRating };

		CHECK(dut.getRating() == testRating);
	}

	SECTION("the Participants Rating can be set and changed after construction")
	{
		Participant dut{ std::string("BigObvious")};

		Rating firstRating{ -5 };
		dut.setRating(firstRating);
		CHECK(dut.getRating() == firstRating);

		Rating newRating{ 13 };
		dut.setRating(newRating);
		CHECK(dut.getRating() == newRating);

		Rating resetRating{ b3m::common::emptyRating };
		dut.setRating(resetRating);
		CHECK(dut.getRating() == resetRating);
	}
}

//TODO add unit tests for Team


//END OF FILE --------------------------------------------------------------------------------------