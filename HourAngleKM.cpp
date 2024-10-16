#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include <limits> // For std::numeric_limits
#include "HourAngleKM.h"

// Implementation of the function that calculates actuator length from elevation angle
double HourAngleKM::getActuatorLengthFromHourAngle(double hour_angle) const
{
    double rab2 = m_rab * m_rab;
    double rad2 = m_rad * m_rad;
    double rbc2 = m_rbc * m_rbc;
    double ySquare = rab2 + rad2 - rbc2 + 2.0 * m_rab * m_rad * std::sin( hour_angle - m_gamma );

    // Check if ySquare is negative
    if (ySquare < 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return std::sqrt(ySquare) - m_offset;
}

// Implementation of the function that calculates elevation angle from actuator length
double HourAngleKM::getHourAngleFromActuatorLength(double actuator_length) const 
{
    double rab2 = m_rab * m_rab;
    double rad2 = m_rad * m_rad;
    double rbc2 = m_rbc * m_rbc;
    double y = actuator_length + m_offset;
    double y2 = y * y;

    double sin_arg = (rbc2 + y2 - rab2 - rad2) / (2.0 * m_rab * m_rad );

    // Check if the argument of asin is within the valid range [-1, 1]
    if (sin_arg < -1.0 || sin_arg > 1.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return m_gamma + std::asin(sin_arg);
}