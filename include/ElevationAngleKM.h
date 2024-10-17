#pragma once

#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include "heliostat_tracking_export.h"

class HELIOSTAT_TRACKING_EXPORT ElevationAngleKM
{
    public:
        ElevationAngleKM(double gamma, double rab, double rbc, double rad, double alpha2, double offset)
            : m_gamma(gamma), m_rab(rab), m_rbc(rbc), m_rad(rad), m_alpha2(alpha2), m_offset(offset) { }

         ~ElevationAngleKM() = default;

        // Getter functions
        double get_gamma() const { return m_gamma; }
        double get_rab() const { return m_rab; }
        double get_rbc() const { return m_rbc; }
        double get_rad() const { return m_rad; }
        double get_alpha2() const { return m_alpha2; }
        double get_offset() { return m_offset; }

        // Setter functions
        void set_gamma(double gamma) { m_gamma = gamma; }
        void set_rab(double rab) { m_rab = rab; }
        void set_rbc(double rbc) { m_rbc = rbc; }
        void set_rad(double rad) { m_rad = rad; }
        void set_alpha2(double alpha2) { m_alpha2 = alpha2; }
        void set_offset(double offset) { m_offset = offset; }

        // Additional functions for calculation
        double getActuatorLengthFromElevationAngle(double elevation_angle) const;
        double getElevationAngleFromActuatorLength(double actuator_length) const;

    private:
        double m_gamma; // Angle between the line AB and the vertical direction
        double m_rab; // Minimum, i.e., perpendicular distance between Axis 1 and Axis 3
        double m_rbc; // Minimum, i.e., perpendicular distance between Axis 3 and the plane containing Axis 2 and the axis of the actuator
        double m_rad; // Minimum, i.e., perpendicular distance between Axis 1 and Axis 2
        double m_alpha2; // Additional parameter alpha2
        double m_offset;  // Extension offset.        
};