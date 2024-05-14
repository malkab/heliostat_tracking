#include <cmath>  // For std::cos, std::sqrt, std::asin, and std::acos
#include <limits> // For std::numeric_limits
#include "HourAngleKM.h"

// Implementation of the function that calculates actuator length from elevation angle
double HourAngleKM::getActuatorLengthFromHourAngle(double hour_angle) const
{
    double term1 = m_rab * m_rab;
    double term2 = m_rad * m_rad;
    double term3 = m_rbc * m_rbc;
    double term4 = 2.0 * m_rab * m_rad * std::sin(hour_angle + m_gamma);

    return std::sqrt(term1 + term2 - term3 - term4);
}

// Implementation of the function that calculates elevation angle from actuator length
double HourAngleKM::getHourAngleFromActuatorLength(double actuator_length) const 
{
    double term1 = m_rab * m_rab;
    double term2 = m_rad * m_rad;
    double term3 = m_rbc * m_rbc;
    double term4 = actuator_length * actuator_length;
    double term5 = 2 * m_rab * m_rad;

    double sin_arg = (term1 + term2 - term3 - term4) / term5;

    // Check if the argument of asin is within the valid range [-1, 1]
    if (sin_arg < -1.0 || sin_arg > 1.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return -m_gamma + std::asin(sin_arg);
}