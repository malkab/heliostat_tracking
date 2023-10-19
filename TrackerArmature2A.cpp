#include "TrackerArmature2A.h"
#include "TrackerSolver2A.h"
#include "TrackerTarget.h"

TrackerArmature2A::TrackerArmature2A()
{
    primaryShift = vec3d(0.f, 0.f, 1.f);
    primaryAxis = vec3d(0.f, 0.f, -1.f); // azimuth
    primaryAngles = vec2d(-90.f, 90.f);

    secondaryShift = vec3d(0.f, 0.f, 0.f);
    secondaryAxis = vec3d(1.f, 0.f, 0.f); // elevation
    secondaryAngles = vec2d(-90.f, 90.f);

    facetShift = vec3d(0.f, 0.f, 0.f);
    facetNormal = vec3d(0.f, 0.f, 1.f);

    anglesDefault = vec2d(0., 0.);

    m_solver = new TrackerSolver2A(this);
    onModified(); 
}

void TrackerArmature2A::onModified()
{
    vec2d pa = primaryAngles * gcf::degree;
    primary = ArmatureJoint(
        primaryShift,
        primaryAxis,
        IntervalPeriodic(pa.x, pa.y)
    );

    vec2d pb = secondaryAngles * gcf::degree;
    secondary = ArmatureJoint(
        secondaryShift,
        secondaryAxis,
        IntervalPeriodic(pb.x, pb.y)
    );

    facet = ArmatureVertex(
        facetShift,
        facetNormal
    );

    angles0 = anglesDefault;
}

TrackerArmature2A::~TrackerArmature2A()
{
    delete m_solver;
}

void TrackerArmature2A::update(const Transform& toGlobal,
                               const vec3d& vSun, TrackerTarget* target)
{
    std::vector<Angles> solutions;
    Transform toLocal = toGlobal.inversed();
    vec3d vSunL = toLocal.transformVector(vSun);
    vec3d rAim = target->aimingPoint;
    if (target->aimingType == TrackerTarget::global) {
        rAim = toLocal.transformPoint(rAim);
        solutions = m_solver->solveReflectionGlobal(vSunL, rAim);
    } else if (target->aimingType == TrackerTarget::local) {
        solutions = m_solver->solveReflectionSecondary(vSunL, rAim);
    }
    Angles solution = m_solver->selectSolution(solutions);
    target->angles = vec2d(solution.x/gcf::degree, solution.y/gcf::degree);
}
