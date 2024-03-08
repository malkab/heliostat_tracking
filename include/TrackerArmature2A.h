#pragma once

#include "heliostat_tracking_export.h"
#include "ArmatureJoint.h"

struct vec3d;
class TrackerTarget;
class TrackerSolver2A;

class HELIOSTAT_TRACKING_EXPORT TrackerArmature2A
{
public:
    TrackerArmature2A();
    ~TrackerArmature2A();

    // Getter functions
    const vec3d& get_primaryShift() const { return m_primaryShift; }
    const vec3d& get_primaryAxis() const { return m_primaryAxis; }
    const vec2d& get_primaryAngles() const { return m_primaryAngles; }

    const vec3d& get_secondaryShift() const { return m_secondaryShift; }
    const vec3d& get_secondaryAxis() const { return m_secondaryAxis; }
    const vec2d& get_secondaryAngles() const { return m_secondaryAngles; }

    const vec3d& get_facetShift() const { return m_facetShift; }
    const vec3d& get_facetNormal() const { return m_facetNormal; }

    const vec2d& get_anglesDefault() const { return m_anglesDefault; }

    const ArmatureJoint& get_primary() const { return m_primary; }
    const ArmatureJoint& get_secondary() const { return m_secondary; }
    const ArmatureVertex& get_facet() const { return m_facet; }
    const vec2d& get_angles0() const { return m_angles0; }
    TrackerSolver2A* const& get_solver() const { return m_solver; }

    // Setter functions
    void set_primaryShift(vec3d primaryShift) { m_primaryShift = primaryShift; onModified(); }
    void set_primaryAxis(vec3d primaryAxis) { m_primaryAxis = primaryAxis; onModified(); }
    void set_primaryAngles(vec2d primaryAngles) { m_primaryAngles = primaryAngles; onModified(); }

    void set_secondaryShift(vec3d secondaryShift) { m_secondaryShift = secondaryShift; onModified(); }
    void set_secondaryAxis(vec3d secondaryAxis) { m_secondaryAxis = secondaryAxis; onModified(); }
    void set_secondaryAngles(vec2d secondaryAngles) { m_secondaryAngles = secondaryAngles; onModified(); }

    void set_facetShift(vec3d facetShift) { m_facetShift = facetShift; onModified(); }
    void set_facetNormal(vec3d facetNormal) { m_facetNormal = facetNormal; onModified(); }

    void set_anglesDefault(vec2d anglesDefault) { m_anglesDefault = anglesDefault; onModified(); }

    void update(const Transform& toGlobal,
                const vec3d& vSun, TrackerTarget* target);


protected:
    void onModified();

    vec3d m_primaryShift;
    vec3d m_primaryAxis;
    vec2d m_primaryAngles;

    vec3d m_secondaryShift;
    vec3d m_secondaryAxis;
    vec2d m_secondaryAngles;

    vec3d m_facetShift;
    vec3d m_facetNormal;

    vec2d m_anglesDefault;

    ArmatureJoint m_primary;
    ArmatureJoint m_secondary;
    ArmatureVertex m_facet;
    vec2d m_angles0;

    TrackerSolver2A* m_solver;


};
