# Linking ardUI library to all targets below
link_libraries(ardUI)
target_sources(ardUI PRIVATE ${SOURCE_DIRECTORY}/display.cpp)


# Including Tester library
add_subdirectory(${TEST_DIRECTORY}/Tester)
link_libraries(Tester)


# Individual test targets
add_executable(
		Test_template_library
		${TEST_DIRECTORY}/tests/tl.test.cpp
)

add_executable(
		Test_Rect
		${TEST_DIRECTORY}/tests/rect.test.cpp
)

add_executable(
		Test_Bundle
		${TEST_DIRECTORY}/tests/bundle.test.cpp
)

add_executable(
		Test_Activity
		${TEST_DIRECTORY}/tests/activity.test.cpp
)
