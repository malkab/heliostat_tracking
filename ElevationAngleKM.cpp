#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include <limits> // For std::numeric_limits
#include "ElevationAngleKM.h"

// Implementation of the function that calculates actuator length from elevation angle
double ElevationAngleKM::getActuatorLengthFromElevationAngle(double elevation_angle) const
{
    double rab2 = m_rab * m_rab;
    double rad2 = m_rad * m_rad;
    double rbc2 = m_rbc * m_rbc;

    double xSquare = rab2 + rad2 - rbc2 + 2.0 * m_rab * m_rad * std::cos(elevation_angle - m_alpha2 + m_gamma);

    // Check if xSquare is negative
    if (xSquare < 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return std::sqrt(xSquare) - m_offset;
}

// Implementation of the function that calculates elevation angle from actuator length
double ElevationAngleKM::getElevationAngleFromActuatorLength(double actuator_length) const 
{
    double rab2 = m_rab * m_rab;
    double rad2 = m_rad * m_rad;
    double rbc2 = m_rbc * m_rbc;
    double x = actuator_length + m_offset;
    double x2 = x * x;

    double cos_arg = (rbc2 + x2 - rab2 - rad2) / (2.0 * m_rab * m_rad );

    // Check if the argument of acos is within the valid range [-1, 1]
    if (cos_arg < -1.0 || cos_arg > 1.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return  m_alpha2 - m_gamma - std::acos(cos_arg);
}
