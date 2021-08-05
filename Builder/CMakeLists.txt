set(UTILS_DIRECTORY ${BUILDER_DIRECTORY}/utils)

# Setting compiler flags
if (${CMAKE_CXX_COMPILER} MATCHES "em\\+\\+")
	SET(COMPILER_FLAGS " --bind")
	SET(LINKER_FLAGS " -s MODULARIZE=1 -s EXPORT_NAME=ardUI -s EXPORTED_FUNCTIONS=[_setup,_loop]")

	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS})
	SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
endif ()

# Linking emulator and ardUI to main code
link_libraries(ardUI)
target_sources(ardUI PRIVATE ${UTILS_DIRECTORY}/display.cpp)
link_libraries(arduinoEmulator)


# Adding examples
add_executable(
		Builder.js
		${UTILS_DIRECTORY}/BuilderInterface.cpp
		${UTILS_DIRECTORY}/builder.cpp
)
