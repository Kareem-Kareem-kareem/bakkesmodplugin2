cmake_minimum_required(VERSION 3.10)
project(SimpleGreeter)

set(CMAKE_CXX_STANDARD 17)

set(BAKKESMOD_SDK $ENV{BAKKESMOD_SDK})
if(NOT BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/sdk")
endif()

include_directories(${BAKKESMOD_SDK}/include)
link_directories(${BAKKESMOD_SDK}/lib)

add_library(SimpleGreeter SHARED src/main.cpp)
target_link_libraries(SimpleGreeter BakkesModPlugin)
set_target_properties(SimpleGreeter PROPERTIES PREFIX "" SUFFIX ".dll")
