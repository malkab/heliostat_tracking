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

# Bluesolar Aiming Point example
add_executable(bluesolar_aiming_point bluesolar_aiming_point/main.cpp bluesolar_aiming_point/BluesolarAimingPointHelpers.cpp)
target_include_directories(bluesolar_aiming_point PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/examples/bluesolar_aiming_point
)
target_link_libraries(bluesolar_aiming_point PRIVATE ${This})