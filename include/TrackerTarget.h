#pragma once

#include "vec2d.h"
#include "vec3d.h"

class TrackerTarget
{

public:
    TrackerTarget();
    ~TrackerTarget();

    enum AimingType {
        local,
        global
    };

    AimingType aimingType;
    vec3d aimingPoint;
    vec2d angles;
};

