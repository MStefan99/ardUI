# Adding ardUI framework
add_library(ardUI SHARED)
target_sources(ardUI PRIVATE
		${SOURCE_DIRECTORY}/llpi.cpp
		${SOURCE_DIRECTORY}/Bundle.cpp
		${SOURCE_DIRECTORY}/Rect.cpp
		${SOURCE_DIRECTORY}/Drawable.cpp
		${SOURCE_DIRECTORY}/View.cpp
		${SOURCE_DIRECTORY}/TextView.cpp
		${SOURCE_DIRECTORY}/ViewGroup.cpp
		${SOURCE_DIRECTORY}/ButtonView.cpp
		${SOURCE_DIRECTORY}/LinearLayout.cpp
		${SOURCE_DIRECTORY}/EventManager.cpp
		${SOURCE_DIRECTORY}/ActivityManager.cpp
		${SOURCE_DIRECTORY}/Activity.cpp
		${SOURCE_DIRECTORY}/ardUI.cpp
		)
target_include_directories(ardUI PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(ardUI arduinoEmulator)
