cmake_minimum_required(VERSION 3.25.1)

set(This heliostat_tracking)

project(${This} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Global output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)

# Make default visibility hidden for all targets
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
enable_testing()

# Add subdirectory for Google Test
add_subdirectory(googletest)

include_directories(./include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})  # Include the binary directory where the export header is generated
include_directories(./googletest/googlemock/include)

set(Headers 
    ./include/ArmatureJoint.h
    ./include/ElevationAngleKM.h
    ./include/gcf.h
    ./include/HourAngleKM.h
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
    ElevationAngleKM.cpp
    gfc.cpp
    HourAngleKM.cpp
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

add_library(${This} SHARED ${Sources} ${Headers})

# Search for Mathematica include directory
find_path(Mathematica_INCLUDE_DIR
    NAMES WolframLibrary.h
    PATHS
        "C:/Program Files/Wolfram Research/Mathematica/13.3/SystemFiles/IncludeFiles/C"
        "/Applications/Mathematica.app/Contents/SystemFiles/IncludeFiles/C"
)

# If Mathematica is found, include the file in the build process
if(Mathematica_INCLUDE_DIR)
    include_directories(${Mathematica_INCLUDE_DIR})
    message(STATUS "Found Mathematica include directory: ${Mathematica_INCLUDE_DIR}")
    message(STATUS "Generating Mathematica wrappers")
    target_sources(${This} PRIVATE MathematicaWrapper.cpp)
else()
    message(STATUS "Not found Mathematica include directory. Assuming Mathematica is not installed in the computer")
    message(STATUS "Not generating Mathematica wrappers")
endif()

# Search for pybind11 and set up Python wrapper
set(PYTHON_WRAPPER_ENABLED FALSE)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
if (Python_FOUND)
    message(STATUS "Found Python interpreter at: ${Python_EXECUTABLE}")   

    execute_process(
        COMMAND ${Python_EXECUTABLE} -c "import pybind11; print(pybind11.get_include())"
        OUTPUT_VARIABLE PYBIND11_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (PYBIND11_INCLUDE_DIR AND EXISTS "${PYBIND11_INCLUDE_DIR}/pybind11/embed.h")
        message(STATUS "Found pybind11 include directory: ${PYBIND11_INCLUDE_DIR}")
        include_directories(${PYBIND11_INCLUDE_DIR})
        execute_process(
            COMMAND ${Python_EXECUTABLE} -m pybind11 --cmake
            OUTPUT_VARIABLE pybind11_DIR
            ERROR_VARIABLE error
            RESULT_VARIABLE result
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
        )
        if (result EQUAL 0 AND EXISTS "${pybind11_DIR}/pybind11Config.cmake")
            message(STATUS "Found pybind11 at: ${pybind11_DIR}")
            list(APPEND CMAKE_PREFIX_PATH ${pybind11_DIR})
            find_package(pybind11 CONFIG REQUIRED)
            pybind11_add_module(heliostat_tracking_module PythonWrapper.cpp)
            target_link_libraries(heliostat_tracking_module PRIVATE ${This})
            set(PYTHON_WRAPPER_ENABLED TRUE)
        else()
            message(WARNING "pybind11 not found. Error: ${error}")
        endif()
    else()
        message(WARNING "pybind11 include directory not found.")
    endif()
else()
    message(STATUS "Python not found. Not generating Python wrappers.")
endif()

include(GenerateExportHeader)
generate_export_header(${This})

add_subdirectory(test)
add_subdirectory(examples)