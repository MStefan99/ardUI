# Linking emulator and ardUI to main code
link_libraries(ardUI)
target_sources(ardUI PRIVATE ${SOURCE_DIRECTORY}/display.cpp)
link_libraries(arduinoEmulator)


# Adding examples
add_executable(
		Basic_Widgets
		basic_widgets.cpp
)

add_executable(
		Activity_Result
		activity_result.cpp
)


add_executable(
		Compiled_Layout
		compiled_layout.cpp
)

