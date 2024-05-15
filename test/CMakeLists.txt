cmake_minimum_required(VERSION 3.25.1)

set(This heliostat_tracking_tests)

project(${This} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(Sources
    ArmatureJointTests.cpp
    ElevationAngleKMTests.cpp
    gcfTests.cpp
    HourAngleKMTests.cpp
    IntervalTests.cpp    
    IntervalPeriodicTests.cpp
    Matrix4x4Tests.cpp
    TrackerArmature2ATests.cpp
    TrackerSolver2ATests.cpp
    TrackerTargetTests.cpp
    TransformTests.cpp
    vec2dTests.cpp
    vec3dTests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    gmock_main
    heliostat_tracking
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
