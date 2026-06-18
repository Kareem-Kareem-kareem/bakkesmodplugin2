cmake_minimum_required(VERSION 3.10)
project(UltraSimple)

set(CMAKE_CXX_STANDARD 17)

set(BAKKESMOD_SDK "C:/sdk")
include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(UltraSimple SHARED src/main.cpp)
target_link_libraries(UltraSimple BakkesModPlugin)
set_target_properties(UltraSimple PROPERTIES PREFIX "" SUFFIX ".dll")
