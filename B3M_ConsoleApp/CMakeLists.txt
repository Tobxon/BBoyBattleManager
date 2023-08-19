add_executable(B3M_console
	"src/B3M_console_main.cpp"
)

target_link_libraries(B3M_console 
	PRIVATE
		B3M_Common
)