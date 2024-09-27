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

	REQUIRE_NOTHROW(firstParticipant == std::string(firstName));
}


//END OF FILE --------------------------------------------------------------------------------------