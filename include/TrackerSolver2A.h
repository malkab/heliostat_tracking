#pragma once

#include <cstddef> 
#include<vector>
#include "TrackerArmature2A.h"

typedef vec2d Angles;

class TrackerSolver2A
{
public:
    TrackerSolver2A(TrackerArmature2A* armature) : m_armature(armature) {}

    virtual std::vector<Angles> solveReflectionGlobal(const vec3d& vSun, const vec3d& rAim);
    vec3d findFacetPoint(const Angles& angles);
    std::vector<Angles> solveFacetNormal(const vec3d& normal);
    std::vector<Angles> solveRotation(const vec3d& v0, const vec3d& v);
    virtual std::vector<Angles> solveReflectionSecondary(const vec3d& vSun, const vec3d& rAim);
    virtual Angles selectSolution(const std::vector<Angles>& solutions);

private:
    TrackerArmature2A* m_armature;
};
