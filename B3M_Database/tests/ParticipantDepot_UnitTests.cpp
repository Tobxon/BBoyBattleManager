//--------------------------------------------------------------------------------------------------
/**
 * \brief Unit Tests for the Participant class.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//std
//import <memory>;
#include <memory>
#include <array>

//Catch2 - Test Framework
#include <catch2/catch_test_macros.hpp>

//b3m
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using participant_name_t = b3m::database::participant_t;
using b3m::database::attribute_t;


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("create Participants")
{
    auto dut = std::make_unique< b3m::database::ParticipantsDepot >();

	SECTION("check for empty ParticipantsDepot")
	{
		CHECK(dut->numOfParticipants() == 0);
	}

    SECTION("simply try adding a same named participant twice")
    {
        static const participant_name_t player1{ "Storm" };
        REQUIRE(dut->newParticipant(player1));
        CHECK(dut->numOfParticipants() == 1);
        CHECK(!dut->newParticipant(player1));
        CHECK(dut->numOfParticipants() == 1);
    }

    SECTION("adding multiple participants")
    {
        static const std::array< participant_name_t, 4 > players{
                "Storm", "Hong10", "Lil Kev", "Tynee" };

        std::size_t curSize = 0;
        for (const auto& player : players)
        {
            REQUIRE(dut->numOfParticipants() == curSize);
            REQUIRE(dut->newParticipant(player));
            CHECK(dut->numOfParticipants() == ++curSize);
        }
    }
}

TEST_CASE("remove Participants")
{
	auto dut = std::make_unique< b3m::database::ParticipantsDepot >();

	static const std::array< participant_name_t, 5 > players{
			"Limit", "Mav", "Luisa", "Elina", "another contestant" };

	for (const auto& player : players)
	{
		static const participant_name_t nonContestant{ "Larry" };

		CHECK(!dut->getParticipant(nonContestant));

		REQUIRE(!dut->getParticipant(participant_name_t{ player }));
		REQUIRE(!dut->removeParticipant(participant_name_t{ player }));
		REQUIRE(!dut->getParticipant(participant_name_t{ player }));

		REQUIRE(dut->numOfParticipants() == 0);
		CHECK(!dut->getParticipant(nonContestant));
	}

	//populate dut with participants from "players"
	std::size_t curSize = 0;
	for (const auto& player : players)
	{
		REQUIRE(dut->numOfParticipants() == curSize);
		CHECK(!dut->getParticipant(player));

		REQUIRE(dut->newParticipant(player));

		CHECK(dut->getParticipant(player));
		REQUIRE(dut->numOfParticipants() == ++curSize);
	}

	SECTION("removing all participants")
	{
		for (const auto& player : players)
		{
			REQUIRE(dut->numOfParticipants() == curSize);
			CHECK(dut->getParticipant(player));

			REQUIRE(dut->removeParticipant(player));

			CHECK(!dut->getParticipant(player));
			REQUIRE(dut->numOfParticipants() == --curSize);
		}
		for (const auto& player : players)
		{
			CHECK(dut->numOfParticipants() == 0);
			CHECK(!dut->getParticipant(player));
			REQUIRE(!dut->removeParticipant(player));
			CHECK(!dut->getParticipant(player));
		}
	}
}

TEST_CASE("modifying attributes of participants")
{
	auto dut = std::make_unique< b3m::database::ParticipantsDepot >();

	SECTION("add participant without attribute and add attribute later")
	{
		static const participant_name_t contestantName{ "Tyra" };
		static const attribute_t attribute{ "color" };
		static const std::string attributeData{ "orange" };

		//create participant
		REQUIRE(dut->newParticipant(contestantName));
		const auto curParticipantData = dut->getParticipantsAttributes(contestantName);
		REQUIRE(curParticipantData);
		REQUIRE(curParticipantData.value().empty());

		//set attribute of participant
		REQUIRE(dut->updateParticipantsAttributes(contestantName, attribute, attributeData));
		REQUIRE(dut->numOfParticipants() == 1);

		const auto updatedParticipantData = dut->getParticipantsAttributes(contestantName);
		REQUIRE(updatedParticipantData);
		REQUIRE(dut->numOfParticipants() == 1);

		CHECK(updatedParticipantData.value().size() == 1);
		CHECK(updatedParticipantData.value().at(attribute) == attributeData);
	}
}


//END OF FILE --------------------------------------------------------------------------------------