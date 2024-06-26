cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Azimuth Elevation
add_executable(azimuth_elevation azimuth_elevation/main1.cpp)
target_link_libraries(azimuth_elevation PRIVATE ${This})

# Bluesolar Angles
add_executable(bluesolar_angles bluesolar_angles/main2.cpp bluesolar_angles/BluesolarHelpers.cpp)
target_include_directories(bluesolar_angles PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/examples/bluesolar_angles
)
target_link_libraries(bluesolar_angles PRIVATE ${This})

# Bluesolar Points
add_executable(bluesolar_points bluesolar_points/main3.cpp bluesolar_points/BluesolarPointsHelpers.cpp)
target_include_directories(bluesolar_points PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/examples/bluesolar_points
)
target_link_libraries(bluesolar_points PRIVATE ${This})

# Heliostat Studio
add_executable(heliostat_studio heliostat_studio/main4.cpp)
target_link_libraries(heliostat_studio PRIVATE ${This})