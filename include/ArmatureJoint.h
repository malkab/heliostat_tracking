#pragma once

#include "heliostat_tracking_export.h"
#include "Transform.h"
#include "IntervalPeriodic.h"
#include "gcf.h"



struct HELIOSTAT_TRACKING_EXPORT ArmatureJoint
{
    ArmatureJoint(
        const vec3d& shift = vec3d::Zero,
        const vec3d& axis = vec3d::UnitZ,
        const IntervalPeriodic& angles = IntervalPeriodic(-90.*gcf::degree, 90.*gcf::degree));

    vec3d shift;
    vec3d axis;
    IntervalPeriodic angles;

    Transform getTransform(double angle) const;
};


struct HELIOSTAT_TRACKING_EXPORT ArmatureVertex
{
    ArmatureVertex(
        const vec3d& shift = vec3d::Zero,
        const vec3d& normal = vec3d::UnitZ
    );

    vec3d shift;
    vec3d normal;
};
