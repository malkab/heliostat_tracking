#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include <limits> // For std::numeric_limits
#include "ElevationAngleKM.h"

// Implementation of the function that calculates actuator length from elevation angle
double ElevationAngleKM::getActuatorLengthFromElevationAngle(double elevation_angle) const
{
    double term1 = m_rab * m_rab;
    double term2 = m_rad * m_rad;
    double term3 = m_rbc * m_rbc;
    double term4 = 2.0 * m_rab * m_rad * std::cos(elevation_angle - m_alpha2 + m_gamma);

    return std::sqrt(term1 + term2 - term3 + term4);
}

// Implementation of the function that calculates elevation angle from actuator length
double ElevationAngleKM::getElevationAngleFromActuatorLength(double actuator_length) const 
{
    double term1 = m_rbc * m_rbc;
    double term2 = actuator_length * actuator_length;
    double term3 = m_rab * m_rab;
    double term4 = m_rad * m_rad;
    double term5 = 2 * m_rab * m_rad;

    double cos_arg = (term1 + term2 - term3 - term4) / term5;

    // Check if the argument of acos is within the valid range [-1, 1]
    if (cos_arg < -1.0 || cos_arg > 1.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return -m_gamma + std::acos(cos_arg) + m_alpha2;
}