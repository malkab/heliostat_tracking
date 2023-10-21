cmake_minimum_required(VERSION 3.25.1)

set(This heliostat_tracking)

project(${This} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()
add_subdirectory(googletest)

include_directories(./include)

set(Headers 
    ./include/ArmatureJoint.h
    ./include/gcf.h
    ./include/Interval.h
    ./include/IntervalPeriodic.h
    ./include/Matrix4x4.h
    ./include/TrackerArmature2A.h 
    ./include/TrackerSolver2A.h
    ./include/TrackerTarget.h
    ./include/Transform.h          
    ./include/vec2d.h
    ./include/vec3d.h        
)

set(Sources
    ArmatureJoint.cpp
    gfc.cpp
    Interval.cpp
    IntervalPeriodic.cpp
    Matrix4x4.cpp
    TrackerTarget.cpp
    TrackerArmature2A.cpp
    TrackerSolver2A.cpp
    Transform.cpp
    vec2d.cpp
    vec3d.cpp
)
    add_library(${This} STATIC ${Sources} ${Headers})