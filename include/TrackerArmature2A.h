#pragma once

#include "ArmatureJoint.h"

struct vec3d;
class TrackerTarget;
class TrackerSolver2A;

class TrackerArmature2A
{
public:
    TrackerArmature2A();
    ~TrackerArmature2A(); // should be protected later

    void update(const Transform& toGlobal,
                const vec3d& vSun, TrackerTarget* target);

    vec3d primaryShift;
    vec3d primaryAxis;
    vec2d primaryAngles;

    vec3d secondaryShift;
    vec3d secondaryAxis;
    vec2d secondaryAngles;

    vec3d facetShift;
    vec3d facetNormal;

    vec2d anglesDefault;

    ArmatureJoint primary;
    ArmatureJoint secondary;
    ArmatureVertex facet;
    vec2d angles0;


protected:
    void onModified();

    TrackerSolver2A* m_solver;
};
