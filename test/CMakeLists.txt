# Linking ardUI library to all targets below
link_libraries(ardUI)
target_sources(ardUI PRIVATE ${SOURCE_DIRECTORY}/display.cpp)

add_compile_options(-DTEST)

if (${CMAKE_CXX_COMPILER} MATCHES "clang-cl")
	add_compile_options(/EHs)
endif ()


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
		Test_Color
		${TEST_DIRECTORY}/tests/color.test.cpp
)

add_executable(
		Test_Drawable
		${TEST_DIRECTORY}/tests/drawable.test.cpp
)

add_executable(
		Test_View
		${TEST_DIRECTORY}/tests/view.test.cpp
)

add_executable(
		Test_ProgressBar
		${TEST_DIRECTORY}/tests/progressbar.test.cpp
)

add_executable(
		Test_TextView
		${TEST_DIRECTORY}/tests/textview.test.cpp
)

add_executable(
		Test_Activity
		${TEST_DIRECTORY}/tests/activity.test.cpp
)

add_executable(
		Test_Activity_result
		${TEST_DIRECTORY}/tests/activity_result.test.cpp
)

add_executable(
		Test_ardUI
		${TEST_DIRECTORY}/tests/ardUI.test.cpp
)
