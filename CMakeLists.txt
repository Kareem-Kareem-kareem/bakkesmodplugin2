cmake_minimum_required(VERSION 3.10)
project(SpawnMiddle)

set(CMAKE_CXX_STANDARD 17)

# Read SDK path from environment variable
set(BAKKESMOD_SDK $ENV{BAKKESMOD_SDK})

# Fallback for local builds
if(NOT BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/path/to/bakkesmodsdk")
endif()

message(STATUS "Using BakkesMod SDK at: ${BAKKESMOD_SDK}")

include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(SpawnMiddle SHARED src/main.cpp)
target_link_libraries(SpawnMiddle BakkesModPlugin)
set_target_properties(SpawnMiddle PROPERTIES PREFIX "" SUFFIX ".dll")
