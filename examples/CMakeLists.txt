cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# For each example, create an executable and link to the dynamic library
add_executable(azimuth_elevation azimuth_elevation/main1.cpp)
add_executable(bluesolar_angles bluesolar_angles/main2.cpp)
add_executable(heliostat_studio heliostat_studio/main3.cpp)

target_link_libraries(azimuth_elevation ${This})
target_link_libraries(bluesolar_angles ${This})
target_link_libraries(heliostat_studio ${This})