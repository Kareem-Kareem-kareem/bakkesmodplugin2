cmake_minimum_required(VERSION 3.10)
project(SpawnMiddle)

set(CMAKE_CXX_STANDARD 17)

if(NOT DEFINED BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/path/to/bakkesmodsdk" CACHE PATH "Path to BakkesMod SDK")
endif()

include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(SpawnMiddle SHARED src/main.cpp)
target_link_libraries(SpawnMiddle BakkesModPlugin)
set_target_properties(SpawnMiddle PROPERTIES PREFIX "" SUFFIX ".dll")
