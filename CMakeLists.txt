cmake_minimum_required(VERSION 3.25.1)

project(hyperion VERSION 0.1.0 LANGUAGES CXX)


include_directories(./include)

set(-DCMAKE_PREFIX_PATH="/opt/homebrew/lib")

set(Headers 
    ./include/atmosphere.h 
    ./include/atmosphereLH.h 
    ./include/atmosphereSW.h 
    ./include/atmosphereVB.h  
    ./include/auxfunction.h
    ./include/boundaries.h 
    ./include/heliostat.h 
    ./include/idealefficiencymap.h 
    ./include/location.h 
    ./include/mathconstants.h
    ./include/processheliostatfunctor.h    
    ./include/receiver.h
    ./include/scenario.h
    ./include/vec2d.h 
    ./include/vec3d.h
)

set(Sources
    main.cpp
    auxfunction.cpp 
    scenario.cpp 
    heliostat.cpp
    processheliostatfunctor.cpp
    idealefficiencymap.cpp     
    location.cpp
    vec2d.cpp 
    vec3d.cpp
)

add_executable(hyperion ${Sources} ${Headers})

target_compile_features(hyperion PRIVATE cxx_std_20)