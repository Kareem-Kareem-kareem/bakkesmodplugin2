cmake_minimum_required(VERSION 3.10)
project(HelloPlugin)

set(CMAKE_CXX_STANDARD 17)
set(BAKKESMOD_SDK $ENV{BAKKESMOD_SDK})
if(NOT BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/sdk")
endif()
include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(HelloPlugin SHARED src/main.cpp)
target_link_libraries(HelloPlugin BakkesModPlugin)
set_target_properties(HelloPlugin PROPERTIES PREFIX "" SUFFIX ".dll")
