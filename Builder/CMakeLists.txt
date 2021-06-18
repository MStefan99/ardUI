set(UTILS_DIRECTORY ${BUILDER_DIRECTORY}/utils)

# Setting compiler flags
if (${CMAKE_C_COMPILER} MATCHES "emcc")
	SET(COMPILER_FLAGS " --bind -s MODULARIZE=1 -s EXPORT_NAME=ardUI -s EXPORTED_RUNTIME_METHODS=[downcastPointer] -s EXPORTED_FUNCTIONS=[_setup,_loop]")
	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS})
endif ()

# Linking emulator and ardUI to main code
link_libraries(ardUI)
target_sources(ardUI PRIVATE ${UTILS_DIRECTORY}/llpi.cpp)
link_libraries(arduinoEmulator)


# Adding examples
add_executable(
		Builder.js
		${UTILS_DIRECTORY}/builder.cpp
)
