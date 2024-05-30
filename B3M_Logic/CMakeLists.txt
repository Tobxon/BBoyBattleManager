add_library(B3M_Logic)
target_sources(B3M_Logic
	PRIVATE
		"src/MatchMaker.cpp"
		"src/MatchMakingUtility.cpp"
	PUBLIC FILE_SET interfaces TYPE CXX_MODULES FILES
		"interface/B3M_Logic.ixx"
		"interface/MatchMaker.ixx"
		"interface/MatchMakingUtility.ixx"
)

target_link_libraries(B3M_Logic
	PRIVATE
		B3M_Common
		Utility
)


# Unit Tests ---------------------------------------------------------------------------------------
find_package(Catch2)

if(Catch2_FOUND)
	add_executable(B3M_Logic_UnitTests)
	target_sources(B3M_Logic_UnitTests
		PRIVATE
			"tests/MatchMaker_UnitTests.cpp"
			"tests/MatchMakingUtility_UnitTests.cpp"
	)

	target_link_libraries(B3M_Logic_UnitTests
		PRIVATE
			Catch2::Catch2WithMain
			B3M_Logic
	)

	include(CTest)
	include(Catch)
	catch_discover_tests(B3M_Logic_UnitTests)
endif()