//--------------------------------------------------------------------------------------------------
/**
 * \brief Unit Tests for the ParticipantsContainer class.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m_database;

//std
//import <string_view>; //TODO

//Catch2 - Test Framework
#include <catch2/catch_test_macros.hpp>

//std
#include <string_view>


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("addParticipant")
{
	std::unique_ptr< b3m::database::IParticipantsContainer > dut = 
		std::make_unique< b3m::database::SimpleParticipantsContainer >();

	SECTION("simply try adding a same named participant twice")
	{
		static constexpr std::string_view player1{ "Storm" };
		REQUIRE(dut->addParticipant(b3m::common::Participant(std::string(player1))));
		CHECK(!dut->addParticipant(b3m::common::Participant(std::string(player1))));
	}

	SECTION("adding multiple participants")
	{
		static const std::vector< std::string_view > players{ "Storm", "Hong10", "Lil Kev", "Tynee" };
		for (const auto& player : players)
		{
			REQUIRE(dut->addParticipant(b3m::common::Participant(std::string(player))));
		}
	}
}

TEST_CASE("removeParticipant")
{
	std::unique_ptr< b3m::database::IParticipantsContainer > dut =
		std::make_unique< b3m::database::SimpleParticipantsContainer >();

	static const std::vector< std::string_view > players{ "Limit", "Mav", "Luisa", "Elina" };
	for (const auto& player : players)
	{
		REQUIRE(dut->addParticipant(b3m::common::Participant(std::string(player))));
	}

	SECTION("removing all participants")
	{
		for (const auto& player : players)
		{
			REQUIRE(dut->removeParticipant(b3m::common::Participant(std::string(player))));
		}
		for (const auto& player : players)
		{
			REQUIRE(!dut->removeParticipant(b3m::common::Participant(std::string(player))));
		}
	}
}


//END OF FILE --------------------------------------------------------------------------------------