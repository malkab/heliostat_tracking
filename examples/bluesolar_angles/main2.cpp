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

    // Printing the results
    std::cout << target->angles << ", " << length_elevation_angle_actuator << ", " << length_hour_angle_actuator << std::endl;

    delete target;
    return 0; // Return with success code
}