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
#include <array>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using participant_name_t = b3m::database::IParticipantsContainer::participant::name_t;


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
		REQUIRE(dut->createParticipant(participant_name_t{ player1 }));
		CHECK(dut->numOfParticipant() == 1);
		CHECK(dut->numOfAttributes() == 1);
		CHECK(!dut->createParticipant(participant_name_t{ player1 }));
		CHECK(dut->numOfParticipant() == 1);
		CHECK(dut->numOfAttributes() == 1);
	}

	SECTION("adding multiple participants")
	{
		static const std::array< std::string_view, 4 > players{ 
			"Storm", "Hong10", "Lil Kev", "Tynee" };
		
		REQUIRE(dut->numOfAttributes() == 0);
		std::size_t curSize = 0;
		for (const auto& player : players)
		{
			REQUIRE(dut->numOfParticipant() == curSize);
			REQUIRE(dut->createParticipant(participant_name_t{ player }));
			CHECK(dut->numOfParticipant() == ++curSize);
			CHECK(dut->numOfAttributes() == 1);
		}
	}
}

TEST_CASE("remove Participants")
{
	std::unique_ptr< b3m::database::IParticipantsContainer > dut =
		std::make_unique< b3m::database::SimpleParticipantsContainer >();

	static const std::array< std::string_view, 5 > players{ 
		"Limit", "Mav", "Luisa", "Elina", "another contestant" };

	for (const auto& player : players)
	{
		CHECK(dut->numOfParticipant() == 0);
		CHECK(dut->numOfAttributes() == 0);
		REQUIRE(!dut->removeParticipant(participant_name_t{ player }));
		REQUIRE(dut->numOfParticipant() == 0);
		CHECK(dut->numOfAttributes() == 0);
	}
	
	CHECK(dut->numOfAttributes() == 0);
	std::size_t curSize = 0;
	for (const auto& player : players)
	{
		REQUIRE(dut->numOfParticipant() == curSize);
		REQUIRE(dut->createParticipant(participant_name_t{ player }));
		REQUIRE(dut->numOfParticipant() == ++curSize);
		CHECK(dut->numOfAttributes() == 1); //only names yet
	}

	SECTION("removing all participants")
	{
		for (const auto& player : players)
		{
			REQUIRE(dut->numOfParticipant() == curSize);
			CHECK(dut->numOfAttributes() == 1); //only names yet
			REQUIRE(dut->removeParticipant(participant_name_t{ player }));
			REQUIRE(dut->numOfParticipant() == --curSize);
		}
		CHECK(dut->numOfAttributes() == 0);
		for (const auto& player : players)
		{
			CHECK(dut->numOfParticipant() == 0);
			CHECK(dut->numOfAttributes() == 0);
			REQUIRE(!dut->removeParticipant(participant_name_t{ player }));
			REQUIRE(dut->numOfParticipant() == 0);
			CHECK(dut->numOfAttributes() == 0);
		}
	}
}

TEST_CASE("modifying attributes of participants")
{
	using attribute_t = b3m::database::IParticipantsContainer::participant::attribute_name_t;
	using attribute_data_t = b3m::database::IParticipantsContainer::participant::attribute_data_t;
	using attribute_ele_t = b3m::database::IParticipantsContainer::participant::attribute_element_t;

	std::unique_ptr< b3m::database::IParticipantsContainer > dut =
		std::make_unique< b3m::database::SimpleParticipantsContainer >();

	SECTION("set single attribute with single data on a single participant")
	{
		static constexpr std::string_view contestantName{ "Tyra" };
		static constexpr std::string_view attribute{ "color" };
		static constexpr std::string_view attributeData{ "orange" };

		REQUIRE(dut->numOfParticipant() == 0);
		REQUIRE(dut->numOfAttributes() == 0);
		REQUIRE(dut->createParticipant(participant_name_t{ contestantName }));
		REQUIRE(dut->numOfParticipant() == 1);
		REQUIRE(dut->numOfAttributes() == 1);
		REQUIRE(dut->setAttributeOfParticipant(participant_name_t{ contestantName },
			attribute_t{ attribute }, attribute_ele_t{ attributeData }));
		REQUIRE(dut->numOfParticipant() == 1);
		REQUIRE(dut->numOfAttributes() == 2);
		auto firstAttributeData = dut->readAttributeOfParticipant(
			participant_name_t{ contestantName }, attribute_t{ attribute });
		CHECK(dut->numOfParticipant() == 1);
		CHECK(dut->numOfAttributes() == 2);
		REQUIRE(firstAttributeData);
		REQUIRE(firstAttributeData.value().size() == 1);
		CHECK(firstAttributeData.value().front() == attribute_ele_t{ attributeData });
	}

	SECTION("set multi data attribute on a single participant")
	{
		static constexpr std::string_view contestantName{ "Christian" };
		static constexpr std::string_view attribute{ "jokes" };
		static constexpr std::array< std::string_view, 3 > attributeData{ 
			"a good one", "...", "word play" };

		REQUIRE(dut->numOfParticipant() == 0);
		REQUIRE(dut->numOfAttributes() == 0);
		REQUIRE(dut->createParticipant(participant_name_t{ contestantName }));
		REQUIRE(dut->numOfParticipant() == 1);
		REQUIRE(dut->numOfAttributes() == 1);
		REQUIRE(dut->setAttributeOfParticipant(participant_name_t{ contestantName },
			attribute_t{ attribute }, attribute_data_t{ std::begin(attributeData), 
			std::end(attributeData) }));
		REQUIRE(dut->numOfParticipant() == 1);
		REQUIRE(dut->numOfAttributes() == 2);
		auto firstAttributeData = dut->readAttributeOfParticipant(
			participant_name_t{ contestantName }, attribute_t{ attribute });
		CHECK(dut->numOfParticipant() == 1);
		CHECK(dut->numOfAttributes() == 2);
		REQUIRE(firstAttributeData);
		REQUIRE(firstAttributeData.value().size() == std::size(attributeData));
		CHECK(std::ranges::is_permutation(firstAttributeData.value(), attributeData));
	}

	//TODO set attribute with the same value multiple times -> decide behaviour

	//TODO set multiple values on multiple attributes on multiple participants (not all with the same data on everyone of course)
}


//END OF FILE --------------------------------------------------------------------------------------