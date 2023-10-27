#include "TrackerArmature2A.h"
#include "TrackerSolver2A.h"
#include "TrackerTarget.h"

TrackerArmature2A::TrackerArmature2A()
{
    m_primaryShift = vec3d(0.f, 0.f, 0.f); // original value vec3d(0.f, 0.f, 1.f)
    m_primaryAxis = vec3d(0.f, 0.f, -1.f); // azimuth original value vec3d(0.f, 0.f, -1.f)
    m_primaryAngles = vec2d(-90.f, 90.f);

    m_secondaryShift = vec3d(0.f, 0.f, 0.f);
    m_secondaryAxis = vec3d(1.f, 0.f, 0.f); // elevation
    m_secondaryAngles = vec2d(-90.f, 90.f);

    m_facetShift = vec3d(0.f, 0.f, 0.f);
    m_facetNormal = vec3d(0.f, 0.f, -1.f);

    m_anglesDefault = vec2d(0., 0.);

    m_solver = new TrackerSolver2A(this);
    onModified(); 
}

void TrackerArmature2A::onModified()
{
    vec2d pa = m_primaryAngles * gcf::degree;
    m_primary = ArmatureJoint(
        m_primaryShift,
        m_primaryAxis,
        IntervalPeriodic(pa.x, pa.y)
    );

    vec2d pb = m_secondaryAngles * gcf::degree;
    m_secondary = ArmatureJoint(
        m_secondaryShift,
        m_secondaryAxis,
        IntervalPeriodic(pb.x, pb.y)
    );

    m_facet = ArmatureVertex(
        m_facetShift,
        m_facetNormal
    );

    m_angles0 = m_anglesDefault * gcf::degree; // It is assumed that m_anglesDefault is given in degrees.
}

TrackerArmature2A::~TrackerArmature2A()
{
    delete m_solver;
    m_solver = nullptr;
}

void TrackerArmature2A::update(const Transform& toGlobal, const vec3d& vSun, TrackerTarget* target)
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
