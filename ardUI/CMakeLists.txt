# Setting compiler flags
SET(COMPILER_FLAGS " -Weverything -Wextra -pedantic -Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic \
-Wno-unused-parameter -Wno-shadow-field -Wno-shadow-field-in-constructor -Wno-old-style-cast \
-Wno-global-constructors -Wno-exit-time-destructors -Wno-unknown-pragmas")
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS})


# Adding ardUI framework
add_library(ardUI STATIC)
target_sources(ardUI PRIVATE
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
		${SOURCE_DIRECTORY}/EventManager.cpp
		${SOURCE_DIRECTORY}/ActivityManager.cpp
		${SOURCE_DIRECTORY}/Activity.cpp
		${SOURCE_DIRECTORY}/ardUI.cpp
		)


target_include_directories(ardUI PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(ardUI arduinoEmulator)
