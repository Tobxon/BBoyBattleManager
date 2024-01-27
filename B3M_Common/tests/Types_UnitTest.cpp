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


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

//Participant --------------------------------------------------------------------------------------
TEST_CASE("b3m Participant - simple constructor test", "[B3M, Participant, Constructor]")
{
	REQUIRE_NOTHROW(b3m::common::Participant{ "AnyBot" });
}

TEST_CASE("b3m Participant - creating a participant and check for valid state")
{
	static constexpr std::string_view firstName{ "npc1" };
	b3m::common::Participant firstParticipant{ std::string(firstName) };

	REQUIRE_NOTHROW(firstParticipant.getName() == std::string(firstName));
}

//TODO add unit tests for Participant

//TODO add unit tests for Team


//END OF FILE --------------------------------------------------------------------------------------