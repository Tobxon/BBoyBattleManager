add_library(B3M_Logic)
target_sources(B3M_Logic
	PRIVATE FILE_SET implementations TYPE CXX_MODULES FILES
		"src/MatchMaker.cpp"
	PUBLIC FILE_SET interfaces TYPE CXX_MODULES FILES
		"interface/B3M_Logic.ixx"
		"interface/MatchMaker.ixx"
)

target_link_libraries(B3M_Logic
	PRIVATE
		B3M_Common
)


# Unit Tests ---------------------------------------------------------------------------------------
find_package(Catch2)

if(Catch2_FOUND)
	add_executable(B3M_Logic_UnitTests)
	target_sources(B3M_Logic_UnitTests
		PRIVATE FILE_SET tests TYPE CXX_MODULES FILES
			"tests/MatchMaker_UnitTests.cpp"
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