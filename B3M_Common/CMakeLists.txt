add_library(B3M_Common)
target_sources(B3M_Common
	PRIVATE
		"src/Participant.cpp"
	#C++20 Modules
	PUBLIC
		FILE_SET cxx_modules TYPE CXX_MODULES FILES
		"interfaces/B3M_Common.ixx"
		"interfaces/Participant.ixx"
		"interfaces/AttributeMap.ixx"
)

target_compile_features(B3M_Common PUBLIC cxx_std_20)


# Unit Tests ---------------------------------------------------------------------------------------
find_package(Catch2)

if(Catch2_FOUND)
	add_executable(B3M_Common_UnitTests)
	target_sources(B3M_Common_UnitTests
		PRIVATE
			"tests/Participant_UnitTest.cpp"
			"tests/AttributeMap_UnitTests.cpp"
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