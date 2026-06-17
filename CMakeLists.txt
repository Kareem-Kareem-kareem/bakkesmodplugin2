cmake_minimum_required(VERSION 3.10)
project(SpawnMiddle)

set(CMAKE_CXX_STANDARD 17)

# Get SDK path from environment variable
set(BAKKESMOD_SDK $ENV{BAKKESMOD_SDK})

# If not set, use a default (for local builds)
if(NOT BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/path/to/bakkesmodsdk")
endif()

message(STATUS "Using BakkesMod SDK at: ${BAKKESMOD_SDK}")

include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(SpawnMiddle SHARED src/main.cpp)

# FIX #1: Correct library name (pluginsdk.lib, not BakkesModPlugin)
target_link_libraries(SpawnMiddle pluginsdk)

# FIX #2: Required preprocessor definitions for BakkesMod SDK headers
target_compile_definitions(SpawnMiddle PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
)

# FIX #3: Set output directory so DLL is easy to find / deploy
set_target_properties(SpawnMiddle PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)
