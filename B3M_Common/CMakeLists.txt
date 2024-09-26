add_library(B3M_Common)
target_sources(B3M_Common
	PRIVATE
		"src/Types.cpp"
	#C++20 Modules
	PUBLIC
		FILE_SET cxx_modules TYPE CXX_MODULES FILES
		"interfaces/B3M_Common.ixx"
		"interfaces/Types.ixx"
)


# Unit Tests ---------------------------------------------------------------------------------------
find_package(Catch2)

if(Catch2_FOUND)
	add_executable(B3M_Common_UnitTests)
	target_sources(B3M_Common_UnitTests
		PRIVATE
			"tests/Types_UnitTest.cpp"
	)

	target_link_libraries(B3M_Common_UnitTests
		PRIVATE
			Catch2::Catch2WithMain
			B3M_Common
	)

	include(CTest)
	include(Catch)
	catch_discover_tests(B3M_Common_UnitTests)
endif()