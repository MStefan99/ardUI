# Adding ardUI framework
add_library(ardUI SHARED)
target_sources(ardUI PRIVATE
		${SOURCE_DIRECTORY}/ardUI.cpp
		${SOURCE_DIRECTORY}/layout_inflater.cpp
		${SOURCE_DIRECTORY}/llpi.cpp
		${SOURCE_DIRECTORY}/activity.cpp
		${SOURCE_DIRECTORY}/text_view.cpp
		${SOURCE_DIRECTORY}/view.cpp
		${SOURCE_DIRECTORY}/view_group.cpp
		${SOURCE_DIRECTORY}/button_view.cpp
		${SOURCE_DIRECTORY}/drawable.cpp
		${SOURCE_DIRECTORY}/dialog.cpp
		${SOURCE_DIRECTORY}/linear_layout.cpp
		${SOURCE_DIRECTORY}/rect.cpp
		)
target_include_directories(ardUI PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(ardUI arduinoEmulator)
