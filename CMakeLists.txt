cmake_minimum_required(VERSION 3.16)

project(hello VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components (Widgets and Charts)
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

qt_standard_project_setup()

# Main executable
qt_add_executable(main
    main.cpp
    dashboard.cpp
    pop.cpp
    eli.cpp
    getLakes.cpp
)

# Link Widgets and Charts to the main executable
target_link_libraries(main PRIVATE Qt6::Widgets Qt6::Charts)

set_target_properties(main PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)

# Test executable
qt_add_executable(testRead
    testRead.cpp
    sampleset.cpp
    sample.cpp
    determinand.cpp
)

# Link only Qt Widgets for the test executable
target_link_libraries(testRead PRIVATE Qt6::Widgets)

set_target_properties(testRead PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)
