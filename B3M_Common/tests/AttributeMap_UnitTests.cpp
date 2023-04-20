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

using attribute_t = std::string;
using data_t = std::vector< std::string >;

template< std::ranges::input_range AttributeRange =std::initializer_list<attribute_t> >
bool checkProperAttributes(const AttributeMap<>& i_participant, const AttributeRange& i_attributes);


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("AttributeMap set attributes from different source types")
{
	AttributeMap< attribute_t, data_t > dut;

	REQUIRE(dut.getAttributes().empty());

	//set attribute with single data
	SECTION("set from 2 string literals")
	{
		REQUIRE(dut.setAttribute("Name", "TestMap"));
		REQUIRE(dut.getAttributeData("Name") == data_t{ "TestMap" });
		CHECK(checkProperAttributes(dut, { "Name" }));
	}

	SECTION("set from 2 temporary strings")
	{
		REQUIRE(dut.setAttribute(attribute_t("Date"), 
			AttributeMap<>::attribute_element_t{ "27.03.2023" }));
		REQUIRE(dut.getAttributeData(attribute_t("Date")) == data_t{ "27.03.2023" });
		CHECK(checkProperAttributes(dut, { "Date" }));
	}
	
	SECTION("set from two const strings")
	{
		const std::string attribute{ "Color" };
		const std::string attributeData{ "colorful" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		REQUIRE(dut.getAttributeData(attribute) == data_t{ attributeData });
		CHECK(checkProperAttributes(dut, { attribute }));
	}

	SECTION("set from two const c strings")
	{
		const char* attribute{ "Color" };
		const char* attributeData{ "colorful" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttributeData(attribute) == data_t{ attributeData });
		CHECK(checkProperAttributes(dut, { attribute }));
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
		CHECK(dut.getAttributeData("Friends") == data_t{ "Chery", "Jack", "Ahmed" });
		CHECK(checkProperAttributes(dut, { "Friends" }));
	}

	SECTION("set from temporary string and temporary array of string")
	{
		REQUIRE(dut.setAttribute(std::string("other Friends"), 
			std::array<std::string, 4>{ "Milo of Croton", "Cleopatra", "300", "..." }));
		CHECK(dut.getAttributeData("other Friends") == 
			data_t{ "Milo of Croton", "Cleopatra", "300", "..." });
		CHECK(checkProperAttributes(dut, { "other Friends" }));
	}

	SECTION("set from temporary string and vector of const char*")
	{
		REQUIRE(dut.setAttribute(std::string("even more Friends"), 
			std::vector<const char*>{ "Karl", "Gilgamesh" }));
		CHECK(dut.getAttributeData("even more Friends") == data_t{ "Karl", "Gilgamesh" });
		CHECK(checkProperAttributes(dut, { "even more Friends" }));
	}

	SECTION("set from const string and const vector of string")
	{
		const std::string attribute{ "books" };
		const std::vector< std::string > attributeData{ "Book1", "Book2" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttributeData(attribute) == attributeData);
		CHECK(checkProperAttributes(dut, { attribute }));
	}

	SECTION("set from const string and const array of string")
	{
		const std::string attribute{ "Cloths" };
		const std::array< std::string, 5 > attributeData{ 
			"Shirt", "Pullover", "Jeans", "Cap", "Sneaker" };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttributeData(attribute) == data_t{ attributeData.cbegin(), attributeData.cend() });
		CHECK(checkProperAttributes(dut, { attribute }));
	}

	SECTION("set from const string and static constexpr array of string_view")
	{
		const std::string attribute{ "Comments" };
		static constexpr std::array< std::string_view, 3 > attributeData{ 
			"great", "rofl u said lol", " . " };
		REQUIRE(dut.setAttribute(attribute, attributeData));
		CHECK(dut.getAttributeData(attribute) == data_t{ attributeData.cbegin(), attributeData.cend() });
		CHECK(checkProperAttributes(dut, { attribute }));
	}
}

TEST_CASE("set attributes")
{
	AttributeMap< attribute_t, data_t > dut;

	SECTION("set single value append single value")
	{
		const std::string attribute{ "A" };
		const std::vector < std::string > data{ "6", "fourtytwo" };

		REQUIRE(dut.setAttribute(attribute, data.front()));
		REQUIRE(dut.getAttributeData(attribute) == data_t{ data.front() });
		REQUIRE(dut.setAttribute(attribute, data.at(1), true));
		CHECK(dut.getAttributeData(attribute) == data);
		CHECK(checkProperAttributes(dut, { attribute }));
	}

	SECTION("set single value, append multiple values")
	{
		const std::string attribute{ "A" };
		const std::vector < std::string > data{ "6", "fourtytwo", "365" };

		REQUIRE(dut.setAttribute(attribute, data.front()));
		REQUIRE(dut.getAttributeData(attribute) == data_t{ data.front() });
		REQUIRE(dut.setAttribute(attribute, data_t{ ++data.cbegin(), data.cend() }, true));
		CHECK(dut.getAttributeData(attribute) == data);
		CHECK(checkProperAttributes(dut, { attribute }));
	}

	SECTION("set multiple values, append multiple values step by step")
	{
		const std::string attribute{ "likes" };
		const std::vector< std::string > data{ "sndkv", "sodv", "i-a", "z", "jwiod vndsa", "mvak..." };
		
		std::size_t index = 3;
		const auto firstElements = std::ranges::take_view(data, index);

		REQUIRE(dut.setAttribute(attribute, firstElements));
		REQUIRE(dut.getAttributeData(attribute) == 
			data_t{ firstElements.begin(), firstElements.begin() + index });
		for (; index < data.size(); ++index)
		{
			REQUIRE(dut.setAttribute(attribute, data.at(index), true));
			auto curView = std::ranges::take_view(data, index+1);
			REQUIRE(dut.getAttributeData(attribute) == data_t{ curView.begin(), curView.end() });
		}
		CHECK(checkProperAttributes(dut, { attribute }));
	}

	SECTION("set different attributes")
	{
		//data
		const std::map< attribute_t, data_t > toSetData{
			{ "shoe size", { "39" }},
			{ "colours", {"cyan", "ultramarine blue", "y"} },
			{ "enemies", {} }
		};

		REQUIRE(dut.getAttributes().empty());
		std::vector< std::string > setAttributes;
		for (const auto& [attribute, data] : toSetData)
		{
			REQUIRE(!dut.getAttributeData(attribute));
			if (!data.empty())
			{
				REQUIRE(dut.setAttribute(attribute, data.front()));
				REQUIRE(dut.getAttributeData(attribute) == data_t{ data.front() });
			}
			else
			{
				REQUIRE(dut.setAttribute(attribute, data));
				REQUIRE(dut.getAttributeData(attribute) == data);
			}
			setAttributes.push_back(attribute);
			REQUIRE(dut.getAttributes() == setAttributes);
		}

		auto toSetDataAttributes = std::views::keys(toSetData);
		REQUIRE(dut.getAttributes() == 
			std::vector< attribute_t >{ toSetDataAttributes.begin(), toSetDataAttributes.end()});
		for (const auto& [attribute, data] : toSetData)
		{
			REQUIRE(dut.setAttribute(attribute, data, true));
			REQUIRE(dut.getAttributeData(attribute) == data);
		}
	}

	dut.setAttribute("test", std::vector< std::string >{}, true);
}

TEST_CASE("replace attribute data")
{
	AttributeMap< attribute_t, data_t > dut;

	const std::map< attribute_t, data_t > initData
	{
		{ "color", { "black", "green", "blue" }},
		{ "world formula", {} },
		{ "cards", {"credit card"} }
	};
	
	REQUIRE(dut.getAttributes().empty());
	for (const auto [attribute, data] : initData)
	{
		REQUIRE(!dut.getAttributeData(attribute));
		REQUIRE(dut.setAttribute(attribute, data));
		REQUIRE(dut.getAttributeData(attribute) == data);
	}
	auto setDataAttributes = std::views::keys(initData);
	REQUIRE(dut.getAttributes() == 
		std::vector< attribute_t >{ setDataAttributes.begin(), setDataAttributes.end() });

	const std::map< attribute_t, data_t > finalDataToSet
	{
		{ "shape", { }},
		{ "world formula", { "42" }},
		{ "cards", {"credit card", "glurak", "id", "gf number" }}
	};

	
	for (const auto [attribute, data] : finalDataToSet)
	{
		REQUIRE(dut.setAttribute(attribute, data));
		REQUIRE(dut.getAttributeData(attribute) == data);
	}

	const std::string keptAttribute{ "color" };
	const auto keptAttributeData = initData.at(keptAttribute);

	auto setFinalDataAttributes = std::views::keys(finalDataToSet);
	std::vector< attribute_t > finalDataAttributes{ 
		setFinalDataAttributes.begin(), setFinalDataAttributes.end() };
	finalDataAttributes.push_back(keptAttribute);
	std::ranges::sort(finalDataAttributes);
	REQUIRE(dut.getAttributes() == finalDataAttributes);
	

	REQUIRE(dut.getAttributeData(keptAttribute) == keptAttributeData);
}


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

template< std::ranges::input_range AttributeRange >
bool checkProperAttributes(const AttributeMap<>& i_attrMap, const AttributeRange& i_attributes)
{
	const auto attributesOfDut = i_attrMap.getAttributes();

	REQUIRE(attributesOfDut.size() == i_attributes.size());
	REQUIRE(std::ranges::is_permutation(attributesOfDut, i_attributes));

	return true;
}


//END OF FILE --------------------------------------------------------------------------------------