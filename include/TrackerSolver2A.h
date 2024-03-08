#pragma once

#include <cstddef> 
#include<vector>

#include "heliostat_tracking_export.h"
#include "TrackerArmature2A.h"

typedef vec2d Angles;

class HELIOSTAT_TRACKING_EXPORT TrackerSolver2A
{
public:
    TrackerSolver2A(TrackerArmature2A* armature) : m_armature(armature) {}

    virtual std::vector<Angles> solveReflectionGlobal(const vec3d& vSun, const vec3d& rAim) const;
    vec3d findFacetPoint(const Angles& angles) const;
    std::vector<Angles> solveFacetNormal(const vec3d& normal) const;
    std::vector<Angles> solveRotation(const vec3d& v0, const vec3d& v) const;
    virtual std::vector<Angles> solveReflectionSecondary(const vec3d& vSun, const vec3d& rAim) const;
    virtual Angles selectSolution(const std::vector<Angles>& solutions) const;

private:
    TrackerArmature2A* m_armature;
};
