# Setting compiler flags
add_compile_options(-Weverything -Werror
		-Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-unknown-argument -Wno-unused-function
		-Wno-unused-parameter -Wno-global-constructors -Wno-exit-time-destructors -Wno-unknown-pragmas)


# Adding ardUI framework
add_library(ardUI STATIC)
target_sources(ardUI PRIVATE
		${CORE_SRC_DIRECTORY}/DisplayController.cpp
		${CORE_SRC_DIRECTORY}/Color.cpp
		${CORE_SRC_DIRECTORY}/Bundle.cpp
		${CORE_SRC_DIRECTORY}/Rect.cpp
		${CORE_SRC_DIRECTORY}/Drawable.cpp
		${CORE_SRC_DIRECTORY}/View.cpp
		${CORE_SRC_DIRECTORY}/EventManager.cpp
		${CORE_SRC_DIRECTORY}/Dialog.cpp
		${CORE_SRC_DIRECTORY}/Activity.cpp
		${CORE_SRC_DIRECTORY}/ActivityManager.cpp
		${CORE_SRC_DIRECTORY}/ardUI.cpp
		)

target_sources(ardUI PRIVATE
		${WIDGETS_SRC_DIRECTORY}/ProgressBar.cpp
		${WIDGETS_SRC_DIRECTORY}/TextView.cpp
		${WIDGETS_SRC_DIRECTORY}/ButtonView.cpp
		${WIDGETS_SRC_DIRECTORY}/ViewGroup.cpp
		${WIDGETS_SRC_DIRECTORY}/LinearLayout.cpp
		${WIDGETS_SRC_DIRECTORY}/ScrollLayout.cpp
		${WIDGETS_SRC_DIRECTORY}/ConstraintLayout.cpp
		)

target_include_directories(ardUI PUBLIC ${TL_DIRECTORY})
target_include_directories(ardUI PUBLIC ${CONFIG_DIRECTORY})
target_include_directories(ardUI PUBLIC ${CORE_INC_DIRECTORY})
target_include_directories(ardUI PUBLIC ${WIDGETS_INC_DIRECTORY})
target_link_libraries(ardUI arduinoEmulator)
