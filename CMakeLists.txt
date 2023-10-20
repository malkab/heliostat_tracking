cmake_minimum_required(VERSION 3.25.1)

project(heliostat_tracking VERSION 0.1.0 LANGUAGES CXX)


include_directories(./include)

set(-DCMAKE_PREFIX_PATH="/opt/homebrew/lib")

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
    main.cpp
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

add_executable(heliostat_tracking ${Sources} ${Headers})

target_compile_features(heliostat_tracking PRIVATE cxx_std_20)