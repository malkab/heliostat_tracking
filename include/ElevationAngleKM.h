#pragma once

#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include "heliostat_tracking_export.h"

class HELIOSTAT_TRACKING_EXPORT ElevationAngleKM
{
    public:
        ElevationAngleKM(double gamma, double rab, double rbc, double rad, double ra, double rd)
            : m_gamma(gamma), m_rab(rab), m_rbc(rbc), m_rad(rad), m_ra(ra), m_rd(rd) { computeAlpha2(); }

         ~ElevationAngleKM() = default;

        // Getter functions
        double get_gamma() const { return m_gamma; }
        double get_rab() const { return m_rab; }
        double get_rbc() const { return m_rbc; }
        double get_rad() const { return m_rad; }
        double get_ra() const { return m_ra; }
        double get_rd() const { return m_rd; }

        // Setter functions
        void set_gamma(double gamma) { m_gamma = gamma; }
        void set_rab(double rab) { m_rab = rab; }
        void set_rbc(double rbc) { m_rbc = rbc; }
        void set_rad(double rad) { m_rad = rad; computeAlpha2(); }
        void set_ra(double ra) { m_ra = ra; computeAlpha2(); }
        void set_rd(double rd) { m_rd = rd; computeAlpha2(); }

        // Additional functions for calculation
        double getActuatorLengthFromElevationAngle(double elevation_angle) const;
        double getElevationAngleFromActuatorLength(double actuator_length) const;

    private:
        double m_gamma; // Angle between the line AB and the vertical direction
        double m_rab; // Minimum, i.e., perpendicular distance between Axis 1 and Axis 3
        double m_rbc; // Minimum, i.e., perpendicular distance between Axis 3 and the plane containing Axis 2 and the axis of the actuator
        double m_rad; // Minimum, i.e., perpendicular distance between Axis 1 and Axis 2
        double m_ra; // Minimum distance between Axis 1 and the plane of the faced
        double m_rd; // Minimum distance between Axis 2 and the plane of the faced
        double m_alpha2; // Additional parameter alpha2

        void computeAlpha2() { m_alpha2 = std::asin((m_ra - m_rd) / m_rad); }
};