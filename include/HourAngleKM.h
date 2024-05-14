#pragma once

#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include "heliostat_tracking_export.h"

class HELIOSTAT_TRACKING_EXPORT HourAngleKM
{
    public:
        HourAngleKM(double gamma, double rab, double rbc, double rad)
            : m_gamma(gamma), m_rab(rab), m_rbc(rbc), m_rad(rad) { }

         ~HourAngleKM() = default;

        // Getter functions
        double get_gamma() const { return m_gamma; }
        double get_rab() const { return m_rab; }
        double get_rbc() const { return m_rbc; }
        double get_rad() const { return m_rad; }

        // Setter functions
        void set_gamma(double gamma) { m_gamma = gamma; }
        void set_rab(double rab) { m_rab = rab; }
        void set_rbc(double rbc) { m_rbc = rbc; }
        void set_rad(double rad) { m_rad = rad; }

        // Additional functions for calculation
        double getActuatorLengthFromHourAngle(double hour_angle) const;
        double getHourAngleFromActuatorLength(double actuator_length) const;

    private:
        double m_gamma; // Angle between the line AB and the vertical plane that contains Axis 1 and is oriented in the North – South direction
        double m_rab; // Minimum, i.e., perpendicular, distance between Axis 1 and Axis 3
        double m_rbc; // Minimum, i.e., perpendicular, distance between Axis 3 and the plane containing Axis 2 and the axis of the actuator
        double m_rad; // Minimum, i.e., perpendicular, distance between Axis 1 and Axis 2
};