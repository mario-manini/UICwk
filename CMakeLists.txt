cmake_minimum_required(VERSION 3.16)

project(hello VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(main
    main.cpp
    dashboard.cpp
    pop.cpp
    eli.cpp
)

target_link_libraries(main PRIVATE Qt6::Widgets)

set_target_properties(main PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)

qt_add_executable(testRead
    testRead.cpp
    sampleset.cpp
    sample.cpp
    determinand.cpp
)

target_link_libraries(testRead PRIVATE Qt6::Widgets)

set_target_properties(testRead PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)
