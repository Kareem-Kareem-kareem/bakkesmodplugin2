cmake_minimum_required(VERSION 3.10)
project(TeleportPlugin)

set(CMAKE_CXX_STANDARD 17)

# Point this to where your BakkesMod SDK is (e.g., C:\dev\bakkesmodsdk)
set(BAKKESMOD_SDK "C:/path/to/bakkesmodsdk" CACHE PATH "Path to BakkesMod SDK")

include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(TeleportPlugin SHARED src/main.cpp)
target_link_libraries(TeleportPlugin BakkesModPlugin)
set_target_properties(TeleportPlugin PROPERTIES PREFIX "" SUFFIX ".dll")
