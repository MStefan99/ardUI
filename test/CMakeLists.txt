# Linking ardUI library to all targets below
link_libraries(ardUI)
target_sources(ardUI PRIVATE ${CORE_SRC_DIRECTORY}/display.cpp)

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
		${TEST_DIRECTORY}/tests/Rect.test.cpp
)

add_executable(
		Test_Bundle
		${TEST_DIRECTORY}/tests/Bundle.test.cpp
)

add_executable(
		Test_Color
		${TEST_DIRECTORY}/tests/Color.test.cpp
)

add_executable(
		Test_Drawable
		${TEST_DIRECTORY}/tests/Drawable.test.cpp
)

add_executable(
		Test_View
		${TEST_DIRECTORY}/tests/View.test.cpp
)

add_executable(
		Test_ProgressBar
		${TEST_DIRECTORY}/tests/ProgressBar.test.cpp
)

add_executable(
		Test_TextView
		${TEST_DIRECTORY}/tests/TextView.test.cpp
)

add_executable(
		Test_ButtonView
		${TEST_DIRECTORY}/tests/ButtonView.test.cpp
)

add_executable(
		Test_ListView
		${TEST_DIRECTORY}/tests/ListView.test.cpp
)

add_executable(
		Test_LinearLayout
		${TEST_DIRECTORY}/tests/LinearLayout.test.cpp
)

add_executable(
		Test_ConstraintLayout
		${TEST_DIRECTORY}/tests/ConstraintLayout.test.cpp
)

add_executable(
		Test_Activity
		${TEST_DIRECTORY}/tests/Activity.test.cpp
)

add_executable(
		Test_Dialog
		${TEST_DIRECTORY}/tests/Dialog.test.cpp
)

add_executable(
		Test_Activity_result
		${TEST_DIRECTORY}/tests/Activity_result.test.cpp
)

add_executable(
		Test_ardUI
		${TEST_DIRECTORY}/tests/ardUI.test.cpp
)
