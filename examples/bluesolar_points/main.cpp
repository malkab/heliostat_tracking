#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "Transform.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"
#include "BlueSolarAimingPointHelpers.h"

int main(int argc, char *argv[])
{
    // Global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith
    // Positive angles in the counterclockwise direction according to the direction of the rotation axis

    // Declaracion of variables to store the input values to the program passed as line arguments
    double xHeliostat, yHeliostat, zHeliostat; // Heliostat position on the field.
    double sunAzimuth, sunElevation; // Azimuth and elevation of the Sun in degrees.
    double yTarget; // The y-distance of the target plane, which is assume to be paralell to the x-z plane.
    double lengthElevationActuator, lengthHourAngleActuator; // lenght of the two heliostat actuators.

    // Conversion and validation of line argument values from string to doubles
    if ( !ConvertAndValidateArguments(argc, argv, xHeliostat, yHeliostat, zHeliostat, 
                                     sunAzimuth, sunElevation, yTarget, 
                                     lengthElevationActuator, lengthHourAngleActuator) ) return 1; // Return with error code

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

     // Setting up the elevation and hour angle kinematic models for the BlueSolar heliostat
    ElevationAngleKM elevation_angle_km = CreateBluesolarElevationAngleKM();
    HourAngleKM hour_angle_km = CreateBluesolarHourAngleKM();

    double elevation_angle = elevation_angle_km.getElevationAngleFromActuatorLength(lengthElevationActuator); // radians
    double hour_angle = hour_angle_km.getHourAngleFromActuatorLength(lengthHourAngleActuator); // radians

    //Facet's reference point
    vec3d facetReferencePoint = armature.get_secondary().getTransform(hour_angle).transformPoint(armature.get_facet().shift);
    facetReferencePoint = armature.get_primary().getTransform(elevation_angle).transformPoint(facetReferencePoint);
    facetReferencePoint = heliostatLocation.transformPoint(facetReferencePoint);

    //Heliostat facet normal
    vec3d facetNormal = armature.get_secondary().getTransform(hour_angle).transformNormal(armature.get_facet().normal);
    facetNormal = armature.get_primary().getTransform(elevation_angle).transformNormal(facetNormal);

    //Reflected vector
    vec3d reflectedVector = (2.0*dot(sunVector, facetNormal))*facetNormal - sunVector;

    //Aiming point
    double k = (yTarget - facetReferencePoint.y)/reflectedVector.y;
    vec3d aiming_point = facetReferencePoint + k * reflectedVector;

    // Printing the results
    std::cout << aiming_point << std::endl;

    return 0; // Return with success code
}