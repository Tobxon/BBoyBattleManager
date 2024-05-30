add_library(Utility)
target_sources(Utility
	PUBLIC FILE_SET interfaces TYPE CXX_MODULES FILES
		"interfaces/Utility.ixx"
		"interfaces/integer.ixx"
		"interfaces/type_traits.ixx"
)


# Unit Tests ---------------------------------------------------------------------------------------
find_package(Catch2)

if(Catch2_FOUND)
	add_executable(Utility_UnitTests)
	target_sources(Utility_UnitTests
		PRIVATE
			"tests/integer_UnitTests.cpp"
	)

	target_link_libraries(Utility_UnitTests
		PRIVATE
			Catch2::Catch2WithMain
			Utility
	)

	include(CTest)
	include(Catch)
	catch_discover_tests(Utility_UnitTests)
endif()