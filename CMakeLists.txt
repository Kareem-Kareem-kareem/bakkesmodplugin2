cmake_minimum_required(VERSION 3.10)
project(SpawnMiddle)

set(CMAKE_CXX_STANDARD 17)

# Get SDK path from environment
set(BAKKESMOD_SDK $ENV{BAKKESMOD_SDK})
if(NOT BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/path/to/bakkesmodsdk")
endif()
message(STATUS "Using BakkesMod SDK at: ${BAKKESMOD_SDK}")

include_directories(${BAKKESMOD_SDK}/include)

# Search for BakkesModPlugin.lib in common locations
find_library(BAKKESMOD_PLUGIN_LIB
    NAMES BakkesModPlugin
    PATHS
        ${BAKKESMOD_SDK}/lib
        ${BAKKESMOD_SDK}/lib/Release
        ${BAKKESMOD_SDK}/lib/x64/Release
        ${BAKKESMOD_SDK}/lib/Debug
        ${BAKKESMOD_SDK}/lib/x64/Debug
    NO_DEFAULT_PATH
)

if(NOT BAKKESMOD_PLUGIN_LIB)
    message(FATAL_ERROR "Could not find BakkesModPlugin.lib in ${BAKKESMOD_SDK}/lib")
endif()

message(STATUS "Found BakkesModPlugin.lib at: ${BAKKESMOD_PLUGIN_LIB}")

add_library(SpawnMiddle SHARED src/main.cpp)
target_link_libraries(SpawnMiddle ${BAKKESMOD_PLUGIN_LIB})
set_target_properties(SpawnMiddle PROPERTIES PREFIX "" SUFFIX ".dll")
