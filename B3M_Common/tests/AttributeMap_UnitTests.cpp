//--------------------------------------------------------------------------------------------------
/**
 * \brief Unit Tests for the AttributeMap class.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.common;

//Catch2 - Test Framework
#include <catch2/catch_test_macros.hpp>

//std
#include <string>
#include <array>
#include <vector>
#include <string_view>
#include <ranges>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using namespace b3m::common;


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("AttributeMap set attributes from different source types")
{
	using attribute_t = std::string;
	using data_t = std::vector< std::string >;

	AttributeMap< attribute_t, data_t > dut;

	//set attribute with single data
	SECTION("set from 2 string literals")
	{
		REQUIRE(dut.setAttribute("Name", "TestMap"));
		CHECK(dut.getAttribute("Name") == data_t{ "TestMap" });
	}

	SECTION("set from 2 temporary strings")
	{
		REQUIRE(dut.setAttribute(attribute_t("Date"), AttributeMap<>::attribute_element_t{ "27.03.2023" }));
		CHECK(dut.getAttribute(attribute_t("Date")) == data_t{ "27.03.2023" });
	}
	
	SECTION("set from two const strings")
	{
		const std::string attribute{ "Color" };
		const std::string attributeData{ "colorful" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttribute(attribute) == data_t{ attributeData });
	}

	SECTION("set from two const c strings")
	{
		const char* attribute{ "Color" };
		const char* attributeData{ "colorful" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttribute(attribute) == data_t{ attributeData });
	}
	// the following can't work because std:.string_view is not convertible to std::string and 
	// std::constructable_from can't be used because this will be ambigious for a array of string
	//SECTION("set from const string and static constexpr string_view")
	//{
	//	const char* attribute{ "aaa" };
	//	static constexpr std::string_view attributeData{ "klingeling" };
	//	REQUIRE(dut.setAttribute(attribute, attributeData));
	//}

	//set attribute with multiple data
	SECTION("set from temporary string literal and braced init list")
	{
		REQUIRE(dut.setAttribute("Friends", { "Chery", "Jack", "Ahmed" }));
		CHECK(dut.getAttribute("Friends") == data_t{ "Chery", "Jack", "Ahmed" });
	}

	SECTION("set from temporary string and temporary array of string")
	{
		REQUIRE(dut.setAttribute(std::string("other Friends"), std::array<std::string, 4>{ "Milo of Croton", "Cleopatra", "300", "..." }));
		CHECK(dut.getAttribute("other Friends") == data_t{ "Milo of Croton", "Cleopatra", "300", "..." });
	}

	SECTION("set from temporary string and vector of const char*")
	{
		REQUIRE(dut.setAttribute(std::string("even more Friends"), std::vector<const char*>{ "Karl", "Gilgamesh" }));
		CHECK(dut.getAttribute("even more Friends") == data_t{ "Karl", "Gilgamesh" });
	}

	SECTION("set from const string and const vector of string")
	{
		const std::string attribute{ "books" };
		const std::vector< std::string > attributeData{ "Book1", "Book2" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttribute(attribute) == attributeData);
	}

	SECTION("set from const string and const array of string")
	{
		const std::string attribute{ "Cloths" };
		const std::array< std::string, 5 > attributeData{ "Shirt", "Pullover", "Jeans", "Cap", "Sneaker" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttribute(attribute) == data_t{ attributeData.cbegin(), attributeData.cend() });
	}

	SECTION("set from const string and static constexpr array of string_view")
	{
		const std::string attribute{ "Comments" };
		static constexpr std::array< std::string_view, 3 > attributeData{ "great", "rofl u said lol", " . " };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttribute(attribute) == data_t{ attributeData.cbegin(), attributeData.cend() });
	}
}

TEST_CASE("append attributes")
{
	using attribute_t = std::string;
	using data_t = std::vector< std::string >;

	AttributeMap< attribute_t, data_t > dut;

	SECTION("set single value append single value")
	{
		const std::string attribute{ "A" };
		const std::vector < std::string > data{ "6", "fourtytwo" };

		REQUIRE(dut.setAttribute(attribute, data.front()));
		REQUIRE(dut.getAttribute(attribute) == data_t{ data.front() });
		REQUIRE(dut.setAttribute(attribute, data.at(1), true));
		CHECK(dut.getAttribute(attribute) == data);
	}

	SECTION("set single value, append multiple values")
	{
		const std::string attribute{ "A" };
		const std::vector < std::string > data{ "6", "fourtytwo", "365" };

		REQUIRE(dut.setAttribute(attribute, data.front()));
		REQUIRE(dut.getAttribute(attribute) == data_t{ data.front() });
		REQUIRE(dut.setAttribute(attribute, data_t{ ++data.cbegin(), data.cend() }, true));
		CHECK(dut.getAttribute(attribute) == data);
	}

	SECTION("set multiple values, append multiple values step by step")
	{
		const std::string attribute{ "likes" };
		const std::vector< std::string > data{ "sndkv", "sodv", "i-a", "z", "jwiod vndsa", "mvak..." };
		
		std::size_t index = 3;
		const auto firstElements = std::ranges::take_view(data, index);

		REQUIRE(dut.setAttribute(attribute, firstElements));
		REQUIRE(dut.getAttribute(attribute) == data_t{ firstElements.begin(), firstElements.begin() + index });
		for (; index < data.size(); ++index)
		{
			REQUIRE(dut.setAttribute(attribute, data.at(index), true));
			auto curView = std::ranges::take_view(data, index+1);
			REQUIRE(dut.getAttribute(attribute) == data_t{ curView.begin(), curView.end() });
		}
	}
}


//END OF FILE --------------------------------------------------------------------------------------