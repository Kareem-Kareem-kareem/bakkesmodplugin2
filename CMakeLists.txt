cmake_minimum_required(VERSION 3.12)
project(SpawnMiddle CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use CMake CACHE for SDK path so it can be overridden easily
set(BAKKESMOD_SDK "$ENV{BAKKESMOD_SDK}" CACHE PATH "Path to BakkesMod SDK")
if(NOT BAKKESMOD_SDK)
    set(BAKKESMOD_SDK "C:/path/to/bakkesmodsdk")
endif()

message(STATUS "Using BakkesMod SDK at: ${BAKKESMOD_SDK}")

# Define the shared library target
add_library(SpawnMiddle SHARED src/main.cpp)

# Target-specific includes & link directories (Modern CMake)
target_include_directories(SpawnMiddle PRIVATE ${BAKKESMOD_SDK}/include)
target_link_directories(SpawnMiddle PRIVATE ${BAKKESMOD_SDK}/lib)

# FIX: Link against 'pluginsdk' (the library inside the SDK lib directory)
target_link_libraries(SpawnMiddle PRIVATE pluginsdk)

# Set DLL properties and force output settings
set_target_properties(SpawnMiddle PROPERTIES 
    PREFIX "" 
    SUFFIX ".dll"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)
