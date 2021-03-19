# Linking ardUI library to all targets below
link_libraries(ardUI)

# Including Tester library
set(TESTER_DIRECTORY ${TEST_DIRECTORY}/Tester/inc)
include_directories(${TESTER_DIRECTORY})

# Template library test target
add_executable(
		Test_template_library
		${TEST_DIRECTORY}/tests/tl.test.cpp
)

# Bundle test target
add_executable(
		Test_Bundle
		${TEST_DIRECTORY}/tests/bundle.test.cpp
)

# Bundle test target
add_executable(
		Test_Activity
		${TEST_DIRECTORY}/tests/activity.test.cpp
)
