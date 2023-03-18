add_library(B3M_Database)
target_sources(B3M_Database
	PRIVATE
		"src/ParticipantsContainer.cpp"
	#C++20 Modules
	PUBLIC
		FILE_SET cxx_modules TYPE CXX_MODULES FILES
		"interface/B3M_Database.ixx"
		"interface/ParticipantsContainer.ixx"
)

target_compile_features(B3M_Database PUBLIC cxx_std_20)

target_link_libraries(B3M_Database
	PUBLIC
		B3M_Common
)


# Unit Tests ---------------------------------------------------------------------------------------
find_package(Catch2)

if(Catch2_FOUND)
	add_executable(B3M_Database_UnitTests)
	target_sources(B3M_Database_UnitTests
		PRIVATE
			"tests/ParticipantsContainer_UnitTest.cpp"
	)

	target_link_libraries(B3M_Database_UnitTests
		PRIVATE
			Catch2::Catch2WithMain
			B3M_Database
	)

	include(CTest)
	include(Catch)
	catch_discover_tests(B3M_Database_UnitTests)
endif()