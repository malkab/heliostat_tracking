#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Ray.h"
#include "Transform.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"
#include "BluesolarHelpers.h"

// Function to compare floating point values with a tolerance
bool CompareDoubles(double a, double b, double tolerance = 1e-6) {
    return std::abs(a - b) < tolerance;
}

// Function to check if the heliostat location matches any in the calibrated set
std::tuple<bool, int> IdentifyHeliostatByLocation(double x, double y, double z, const std::map<int, std::tuple<double, double, double>>& calibratedHeliostats) {
    for (const auto& entry : calibratedHeliostats) {
        const auto& [calX, calY, calZ] = entry.second;
        if (CompareDoubles(x, calX) && CompareDoubles(y, calY) && CompareDoubles(z, calZ)) {
            return {true, entry.first}; // Return true and the corresponding heliostatID
        }
    }
    return {false, -1}; // No match found
}

struct CalibrationPoint {
    double azimuth;        // Azimuth in degrees
    double elevation;      // Elevation in degrees
    double correctionElevation; // Correction for the elevation actuator
    double correctionHour;      // Correction for the hour actuator
};

struct CalibrationDataScattered {
    std::vector<CalibrationPoint> points; // List of scattered calibration points
};

// Hardcoded map for calibrated heliostats identified by heliostatID
std::map<int, std::tuple<double, double, double>> calibratedHeliostatLocations = {
    {78, {3.05075, 42.68150, 1.64000}},
    {79, {-0.80225, 42.69550, 1.49000}},
    {81, {-4.63725, 42.71550, 1.37000}},
    {89, {3.02575, 46.91250, 1.66000}},
    {90, {-0.79425, 46.91350, 1.66000}},
    {92, {-4.59025, 46.91950, 1.53000}},
    {100, {3.03675, 51.15050, 1.84000}},
    {101, {-0.79125, 51.16450, 1.78000}},
    {103, {-4.59325, 51.11450, 1.63000}}                       
    // Add more calibrated heliostats here
};

std::map<int, CalibrationDataScattered> heliostatCorrections = {
    {78, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {79, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {81, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {89, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {90, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {92, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {100, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {101, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }},
    {103, {
        {   // List of scattered calibration points for heliostat 78
            { { -90.0, 10.0, 0.001, 0.004 },  // {azimuth, elevation, correctionElevation, correctionHour}
              { -45.0, 20.0, 0.0015, 0.0045 },
              { 0.0, 30.0, 0.002, 0.005 },
              { 45.0, 40.0, 0.0015, 0.0045 },
              { 90.0, 50.0, 0.001, 0.004 } }
        }
    }}
    // Add more corrections here for other heliostats
};

CalibrationPoint WeightedInterpolation(
    const CalibrationDataScattered& data, 
    double targetAzimuth, double targetElevation)
{
    double weightSum = 0.0;
    double weightedCorrectionElevation = 0.0;
    double weightedCorrectionHour = 0.0;

    for (const auto& point : data.points) {
        double distance = sqrt(pow(point.azimuth - targetAzimuth, 2) + pow(point.elevation - targetElevation, 2));
        if (distance == 0.0) {
            // If the point matches exactly, return its correction
            return point;
        }
        double weight = 1.0 / distance;  // Inverse distance weighting
        weightedCorrectionElevation += weight * point.correctionElevation;
        weightedCorrectionHour += weight * point.correctionHour;
        weightSum += weight;
    }

    CalibrationPoint result;
    result.azimuth = targetAzimuth;
    result.elevation = targetElevation;
    result.correctionElevation = weightedCorrectionElevation / weightSum;
    result.correctionHour = weightedCorrectionHour / weightSum;

    return result;
}

int main(int argc, char *argv[])
{
    // Global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith
    // Positive angles in the counterclockwise direction according to the direction of the rotation axis

    // Declaracion of variables to store the input values to the program passed as line arguments
    double xHeliostat, yHeliostat, zHeliostat; // Heliostat position on the field.
    double xAimingPoint, yAimingPoint, zAimingPoint; // Aiming point.
    double sunAzimuth, sunElevation; // Azimuth and elevation of the Sun in degrees.

    // Conversion and validation of line argument values from string to doubles
    if ( !ConvertAndValidateArguments(argc, argv, xHeliostat, yHeliostat, zHeliostat, 
                                     xAimingPoint, yAimingPoint, zAimingPoint, 
                                     sunAzimuth, sunElevation) ) return 1; // Return with error code

    // Defining the target
    TrackerTarget* target = new TrackerTarget;
    target->aimingPoint = vec3d(xAimingPoint, yAimingPoint, zAimingPoint);

    // Setting up the tracker armature for the BlueSolar heliostat
    TrackerArmature2A armature;
    BluesolarHeliostatArmature(armature);

    // Moving the heliostat armature to the location defined by the user
    Transform heliostatLocation = Transform::translate(xHeliostat, yHeliostat, zHeliostat); // actual location of a heliostat in the bluesolar field

    // Defining the sun vector in the global coordinate system from sun angles (azimuth and elevation) in degrees provided by the user.
    // Azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
    double sun_azimuth = sunAzimuth * gcf::degree;
    double sun_elevation = sunElevation * gcf::degree;
    vec3d sunVector(cos(sun_elevation)*sin(sun_azimuth), cos(sun_elevation)*cos(sun_azimuth),sin(sun_elevation));

    // Computing the angles the heliostat armature should turn to reflect the direct solar radiation to the target
    armature.update(heliostatLocation, sunVector, target);

    double elevation_angle = (target->angles.x) * gcf::degree; // radians
    double hour_angle = (target->angles.y) * gcf::degree; // radians

     // Setting up the elevation and hour angle kinematic models for the BlueSolar heliostat
    ElevationAngleKM elevation_angle_km = CreateBluesolarElevationAngleKM();
    HourAngleKM hour_angle_km = CreateBluesolarHourAngleKM();

    double length_elevation_angle_actuator = elevation_angle_km.getActuatorLengthFromElevationAngle(elevation_angle);
    double length_hour_angle_actuator = hour_angle_km.getActuatorLengthFromHourAngle(hour_angle);

    // Identify the heliostat by its location
    auto [isCalibrated, heliostatID] = IdentifyHeliostatByLocation(xHeliostat, yHeliostat, zHeliostat, calibratedHeliostatLocations);

    if (isCalibrated && heliostatCorrections.find(heliostatID) != heliostatCorrections.end()) {
        const CalibrationDataScattered& data = heliostatCorrections[heliostatID];

        // Interpolate corrections using scattered data based on sun azimuth and elevation
        CalibrationPoint correction = WeightedInterpolation(data, sunAzimuth, sunElevation);

        // Apply the corrections to the actuator lengths
        length_elevation_angle_actuator += correction.correctionElevation;
        length_hour_angle_actuator += correction.correctionHour;
    }

    // Printing the results
    std::cout << target->angles << ", " << length_elevation_angle_actuator << ", " << length_hour_angle_actuator << std::endl;

    delete target;
    return 0; // Return with success code
}