cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Azimuth Elevation example
add_executable(azimuth_elevation azimuth_elevation/main1.cpp)
target_link_libraries(azimuth_elevation PRIVATE ${This})

# Bluesolar Angles example
add_executable(bluesolar_angles bluesolar_angles/main2.cpp bluesolar_angles/BluesolarHelpers.cpp)
target_include_directories(bluesolar_angles PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/examples/bluesolar_angles
)
target_link_libraries(bluesolar_angles PRIVATE ${This})

# Heliostat Studio example
add_executable(heliostat_studio heliostat_studio/main3.cpp)
target_link_libraries(heliostat_studio PRIVATE ${This})

# Bluesolar Angles example as a shared library

# Esta compilación sencilla, sin dependencias, funciona correctamente y la
# librería .so resultante (dinámica de Linux) es accesible desde Python.

add_library(bluesolarangles SHARED bluesolar_angles/BluesolarAngles.cpp)

# Sin embargo, esta versión con los includes activados en BluesolarAngles.cpp
# es lo que no consigo compilar.

# add_library(bluesolarangles SHARED bluesolar_angles/BluesolarAngles.cpp bluesolar_angles/BluesolarHelpers.cpp ../TrackerArmature2A.cpp ../TrackerTarget.cpp ../Transform.cpp ../ElevationAngleKM.cpp ../HourAngleKM.cpp ../TrackerSolver2A.cpp ../gcf.cpp ../vec3d.cpp ../vec2d.cpp ../Interval.cpp ../IntervalPeriodic.cpp ../Matrix4x4.cpp)
