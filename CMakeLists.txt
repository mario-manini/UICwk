# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Project declaration with version and language
project(testRead VERSION 1.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories for headers (assuming headers are in the same directory as cpp files)
include_directories(${CMAKE_SOURCE_DIR})

# Add the executable target and specify source files
add_executable(testRead 
    testRead.cpp       
    sampleset.cpp      
    sample.cpp         
    determinand.cpp    
)

# Create Pthreads
target_link_libraries(testRead pthread)