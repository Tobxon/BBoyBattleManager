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
#include <string_view>
#include <array>

//Catch2 - Test Framework
#include <catch2/catch_test_macros.hpp>

//b3m
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using participant_name_t = b3m::database::participant_t;


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("create Participants")
{
    auto dut = std::make_unique< b3m::database::ParticipantsDepot >();

    SECTION("simply try adding a same named participant twice")
    {
        static constexpr std::string_view player1{ "Storm" };
        REQUIRE(dut->newParticipant(participant_name_t{ player1 }));
        CHECK(dut->numOfParticipants() == 1);
        CHECK(!dut->newParticipant(participant_name_t{ player1 }));
        CHECK(dut->numOfParticipants() == 1);
    }

    SECTION("adding multiple participants")
    {
        static const std::array< std::string_view, 4 > players{
                "Storm", "Hong10", "Lil Kev", "Tynee" };

        std::size_t curSize = 0;
        for (const auto& player : players)
        {
            REQUIRE(dut->numOfParticipants() == curSize);
            REQUIRE(dut->newParticipant(participant_name_t{ player }));
            CHECK(dut->numOfParticipants() == ++curSize);
        }
    }
}


//END OF FILE --------------------------------------------------------------------------------------