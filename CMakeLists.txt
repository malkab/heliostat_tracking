cmake_minimum_required(VERSION 3.25.1)

set(This heliostat_tracking)

project(${This} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Make default visibility hidden for all targets
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# Enable gtest_force_shared_crt option
option(gtest_force_shared_crt "Use shared (DLL) run-time lib even when Google Test is built as static lib." ON)

enable_testing()
add_subdirectory(googletest)

include_directories(./include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})  # Include the binary directory where the export header is generated
include_directories(./googletest/googlemock/include)

set(Headers 
    ./include/ArmatureJoint.h
    ./include/gcf.h
    ./include/Interval.h
    ./include/IntervalPeriodic.h
    ./include/Matrix4x4.h
    ./include/Ray.h
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

# Search for Mathematica include directory
find_path(Mathematica_INCLUDE_DIR
    NAMES WolframLibrary.h

    # Potential paths where WolframLibrary.h can be found
    PATHS "C:/Program Files/Wolfram Research/Mathematica/13.3/SystemFiles/IncludeFiles/C"
    PATHS "/Applications/Mathematica.app/Contents/SystemFiles/IncludeFiles/C"
)

# If Mathematica is found, include the file in the build process
if(Mathematica_INCLUDE_DIR)
    include_directories(${Mathematica_INCLUDE_DIR})
    message(STATUS "Found Mathematica include directory: ${Mathematica_INCLUDE_DIR}")
    message(STATUS "Generating Mathematica wrappers")
    add_library(${This} SHARED ${Sources} ${Headers} MathematicaWrapper.cpp)
else()
    message(STATUS "Not found Mathematica include directory. Assuming Mathematica is not installed in the computer")
    message(STATUS "Not generating Mathematica wrappers")
    add_library(${This} SHARED ${Sources} ${Headers})
endif()

include(GenerateExportHeader)
generate_export_header(${This})
    
add_subdirectory(test)   
add_subdirectory(examples)