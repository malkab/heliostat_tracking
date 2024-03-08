#pragma once

#include "heliostat_tracking_export.h"
#include "vec2d.h"
#include "vec3d.h"

class HELIOSTAT_TRACKING_EXPORT TrackerTarget
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

