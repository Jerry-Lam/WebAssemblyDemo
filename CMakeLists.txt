project (client)
cmake_minimum_required(VERSION 3.15.0)
option(JS_ONLY "Compiles to native JS (No WASM)" OFF)

add_definitions(-std=c++20 -O3)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/include)

file(GLOB SOURCES src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public")
add_executable(a ${SOURCES})

# if(JS_ONLY)
# 	message(STATUS "Setting compilation target to native JavaScript")
# 	set(CMAKE_EXECUTABLE_SUFFIX ".js")
# 	set_target_properties(a PROPERTIES LINK_FLAGS "-s WASM=0 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -lidbfs.js")
# else(JS_ONLY)
# 	message(STATUS "Setting compilation target to WASM")
# 	set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
# 	set_target_properties(a PROPERTIES LINK_FLAGS "-s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -lidbfs.js")
# endif(JS_ONLY)

if(JS_ONLY)
	message(STATUS "Setting compilation target to native JavaScript")
	set(CMAKE_EXECUTABLE_SUFFIX ".js")
	set_target_properties(a PROPERTIES LINK_FLAGS "-s WASM=0 --pre-js pre.js")
else(JS_ONLY)
	message(STATUS "Setting compilation target to WASM")
	set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
	set_target_properties(a PROPERTIES LINK_FLAGS "-s WASM=1 --pre-js pre.js")
endif(JS_ONLY)