#ifndef HELIOSTAT_H
#define HELIOSTAT_H

#include <vector>

#include "scenario.h"
#include "vec3d.h"

namespace hypl
{
    class Heliostat
    {
 
    public:

        enum IdealEfficiencyType { CosineOnly, CosineAndTransmittance, AllFactors };

        struct TrackingInfo {
            double ideal_efficiency;            
            int aiming_at_receiver_id;
        };

        Heliostat(Scenario& scenario, vec3d center, IdealEfficiencyType ideal_efficiency_type);

        //Accessors
        Scenario const& scenario() const { return m_scenario; }
        vec3d const& center() const { return m_center; }
        std::vector<double> const& transmittance() const { return m_transmittance; }
        std::vector<double> const& slant_range() const { return m_slant_range; }
        std::vector<vec3d> const& reflected_unit_vector() const { return m_reflected_unit_vector; }

        //Mutators
        void set_center(vec3d center) { m_center = center; update(); }
        void update();

        //Public functions
        TrackingInfo Track(vec3d& sun_vector, double sun_subtended_angle) const;
        double Spillage(int receiver_id, double sun_subtended_angle) const;
        double ReceiverShadowing(int receiver_id, vec3d& sun_vector) const;

        double m_annual_ideal_efficiency;

    private:
        // Private functions
        TrackingInfo TrackCosineOnly(vec3d& sun_vector, double sun_subtended_angle) const;
        TrackingInfo TrackCosineAndTransmittance(vec3d& sun_vector, double sun_subtended_angle) const;
        TrackingInfo TrackAllFactors(vec3d& sun_vector, double sun_subtended_angle) const;
        void AssignTrackFunction(IdealEfficiencyType ideal_efficiency_type);       

        // Private variables
        Scenario& m_scenario;
        vec3d m_center;
        IdealEfficiencyType m_ideal_efficiency_type;

        std::vector<double> m_transmittance;
        std::vector<double> m_slant_range;
        std::vector<vec3d> m_reflected_unit_vector;
        TrackingInfo (Heliostat::*m_ptrTrackingFunction)(vec3d&, double) const;
    };
}
#endif // HELIOSTAT_H