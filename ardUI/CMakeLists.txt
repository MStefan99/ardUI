# Setting compiler flags
SET(COMPILER_FLAGS " -Weverything -Werror \
-Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-unknown-argument \
-Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-unknown-pragmas")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS})


# Adding ardUI framework
add_library(ardUI STATIC)
target_sources(ardUI PRIVATE
		${SOURCE_DIRECTORY}/Color.cpp
		${SOURCE_DIRECTORY}/DisplayController.cpp
		${SOURCE_DIRECTORY}/Bundle.cpp
		${SOURCE_DIRECTORY}/Rect.cpp
		${SOURCE_DIRECTORY}/Drawable.cpp
		${SOURCE_DIRECTORY}/View.cpp
		${SOURCE_DIRECTORY}/ProgressBar.cpp
		${SOURCE_DIRECTORY}/TextView.cpp
		${SOURCE_DIRECTORY}/ButtonView.cpp
		${SOURCE_DIRECTORY}/ViewGroup.cpp
		${SOURCE_DIRECTORY}/LinearLayout.cpp
		${SOURCE_DIRECTORY}/ConstraintLayout.cpp
		${SOURCE_DIRECTORY}/ScrollLayout.cpp
		${SOURCE_DIRECTORY}/EventManager.cpp
		${SOURCE_DIRECTORY}/Activity.cpp
		${SOURCE_DIRECTORY}/ActivityManager.cpp
		${SOURCE_DIRECTORY}/ardUI.cpp
		)


target_include_directories(ardUI PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(ardUI arduinoEmulator)
