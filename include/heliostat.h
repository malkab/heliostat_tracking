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
        struct TrackingInfo {
            double ideal_efficiency;            
            int aiming_at_receiver_id;
        };

        Heliostat(Scenario& scenario, vec3d center);

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
        virtual Heliostat* Create(Scenario& scenario, vec3d center) = 0; // Pure virtual function
        virtual TrackingInfo Track(vec3d& sun_vector, double sun_subtended_angle) const = 0; // Pure virtual function
        virtual ~Heliostat() { }
        double Spillage(int receiver_id, double sun_subtended_angle) const;
        double ReceiverShadowing(int receiver_id, vec3d& sun_vector) const;

        double m_annual_ideal_efficiency;

    protected:
        Scenario& m_scenario;
        vec3d m_center;

        std::vector<double> m_transmittance;
        std::vector<double> m_slant_range;
        std::vector<vec3d> m_reflected_unit_vector;
    };
}
#endif // HELIOSTAT_H