//--------------------------------------------------------------------------------------------------
/**
 * \brief Unit Tests for the ParticipantsContainer class.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.database;

//std
//import <string_view>; //TODO

//Catch2 - Test Framework
#include <catch2/catch_test_macros.hpp>

//std
#include <string_view>
#include <memory>
#include <string>
#include <vector>


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("create Participants")
{
	std::unique_ptr< b3m::database::IParticipantsContainer > dut = 
		std::make_unique< b3m::database::SimpleParticipantsContainer >();

	SECTION("simply try adding a same named participant twice")
	{
		static constexpr std::string_view player1{ "Storm" };
		REQUIRE(dut->createParticipant(std::string(player1)));
		CHECK(dut->size() == 1);
		CHECK(!dut->createParticipant(std::string(player1)));
		CHECK(dut->size() == 1);
	}

	SECTION("adding multiple participants")
	{
		static const std::vector< std::string_view > players{ "Storm", "Hong10", "Lil Kev", "Tynee" };
		std::size_t curSize = 0;
		for (const auto& player : players)
		{
			CHECK(dut->size() == curSize);
			REQUIRE(dut->createParticipant(std::string(player)));
			CHECK(dut->size() == ++curSize);
		}
	}
}

TEST_CASE("remove Participants")
{
	std::unique_ptr< b3m::database::IParticipantsContainer > dut =
		std::make_unique< b3m::database::SimpleParticipantsContainer >();

	static const std::vector< std::string_view > players{ "Limit", "Mav", "Luisa", "Elina" };
	std::size_t curSize = 0;
	for (const auto& player : players)
	{
		CHECK(dut->size() == curSize);
		REQUIRE(dut->createParticipant(std::string(player)));
		CHECK(dut->size() == ++curSize);
	}

	SECTION("removing all participants")
	{
		for (const auto& player : players)
		{
			CHECK(dut->size() == curSize);
			REQUIRE(dut->removeParticipant(std::string(player)));
			CHECK(dut->size() == --curSize);
		}
		for (const auto& player : players)
		{
			CHECK(dut->size() == 0);
			REQUIRE(!dut->removeParticipant(std::string(player)));
			CHECK(dut->size() == 0);
		}
	}
}


//END OF FILE --------------------------------------------------------------------------------------