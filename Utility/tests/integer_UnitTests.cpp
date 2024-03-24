//--------------------------------------------------------------------------------------------------
/**
 * \brief Unit Tests for the integer utility functions..
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Catch2 - Test Framework
import <catch2/catch_test_macros.hpp>;

//b3m
import utility;
import <limits>;
import <random>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

using utility::integer::ceil_pos_uint_division;

template<utility::type_traits::IsUnsignedint numberType>
numberType getRandomNumber(numberType maxNumber = std::numeric_limits<numberType>::max())
{
	std::random_device rand;
	std::mt19937 gen(rand());

	std::uniform_int_distribution<numberType> distribution(1, maxNumber);

	return distribution(gen);
}


//--------------------------------------------------------------------------------------------------
//------ Tests                                                                                ------
//--------------------------------------------------------------------------------------------------

TEST_CASE("Ceil Pos Uint Division - Simple Cases") {
	const auto baseNum = getRandomNumber<unsigned>(std::numeric_limits<unsigned>::max()/20);

	SECTION("Even Division") {
		REQUIRE(ceil_pos_uint_division(16u, 4u) == 4u);
		REQUIRE(ceil_pos_uint_division(baseNum * 2, 2u) == baseNum);
		REQUIRE(ceil_pos_uint_division(baseNum * 16, baseNum) == 16u);
	}

	SECTION("Odd Division with Rounding Up") {
		REQUIRE(ceil_pos_uint_division(11u, 5u) == 3u);
		REQUIRE(ceil_pos_uint_division(baseNum * 17 + 1, 17u) == baseNum + 1);
		REQUIRE(ceil_pos_uint_division(static_cast<unsigned>(baseNum * 4.5), baseNum) == 5u);
	}

	SECTION("Equal Dividend and Divisor") {
		REQUIRE(ceil_pos_uint_division(10u, 10u) == 1u);
		REQUIRE(ceil_pos_uint_division(1u, 1u) == 1u);
		REQUIRE(ceil_pos_uint_division(std::numeric_limits<unsigned>::max(), std::numeric_limits<unsigned>::max()) == 1u);
		REQUIRE(ceil_pos_uint_division(baseNum, baseNum) == 1u);
	}
}

TEST_CASE("Ceil Pos Uint Division - Edge Cases") {
	const auto baseNum = getRandomNumber<unsigned>(std::numeric_limits<unsigned>::max());

	SECTION("Division by Zero") {
		REQUIRE_THROWS(ceil_pos_uint_division(5u, 0u));
		REQUIRE_THROWS(ceil_pos_uint_division(100u, 0u));
		REQUIRE_THROWS(ceil_pos_uint_division(std::numeric_limits<unsigned>::max(), 0u));
		REQUIRE_THROWS(ceil_pos_uint_division(baseNum, 0u));
	}

	SECTION("Max Value with Divisor 1") {
		REQUIRE(ceil_pos_uint_division(std::numeric_limits<unsigned>::max(), 1u) == std::numeric_limits<unsigned>::max());
		REQUIRE(ceil_pos_uint_division(baseNum, 1u) == baseNum);
	}

	SECTION("Dividend is Zero"){
		REQUIRE(ceil_pos_uint_division(0u, 1u) == 0u);
		REQUIRE(ceil_pos_uint_division(0u, getRandomNumber<unsigned>(std::numeric_limits<unsigned>::max())) == 0u);
	}
}

TEST_CASE("Ceil Pos Uint Division - Different Unsigned Types") {
	SECTION("uint8_t") {
		REQUIRE(ceil_pos_uint_division<uint8_t>(std::numeric_limits<uint8_t>::max(), 2) == 128);
		REQUIRE(ceil_pos_uint_division<uint8_t>(3, 2) == 2);
	}

	SECTION("uint16_t") {
		REQUIRE(ceil_pos_uint_division<uint16_t>(std::numeric_limits<uint16_t>::max(), 2) == 32768);
		REQUIRE(ceil_pos_uint_division<uint16_t>(3, 2) == 2);
	}

	SECTION("uint32_t") {
		REQUIRE(ceil_pos_uint_division<uint32_t>(std::numeric_limits<uint32_t>::max(), 2) == 2147483648);
		REQUIRE(ceil_pos_uint_division<uint32_t>(3, 2) == 2);
	}

	SECTION("uint64_t") {
		REQUIRE(ceil_pos_uint_division<uint64_t>(std::numeric_limits<uint64_t>::max(), 2) == 9223372036854775808u);
		REQUIRE(ceil_pos_uint_division<uint64_t>(3, 2) == 2);
	}
}


//END OF FILE --------------------------------------------------------------------------------------