#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Ray.h"
#include "Transform.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"

void BluesolarHeliostatArmature(TrackerArmature2A& armature);
ElevationAngleKM CreateBluesolarElevationAngleKM();
HourAngleKM CreateBluesolarHourAngleKM();

int main(int argc, char *argv[])
{
     // Check if the correct number of arguments is passed
    if (argc != 9) {
        std::cerr << "Usage: " << argv[0] << " xHeliostat yHeliost zHeliostat xAimingPoint yAimingPoint zAimingPoint sunAzimuth sunElevation" << std::endl;
        return 1; // Return with error code
    }

    // Assuming the arguments are correctly ordered: xHeliostat yHeliost zHeliostat xAimingPoint yAimingPoint zAimingPoint sunAzimuth sunElevation
    // Convert the arguments from strings to doubles
    char* end;
    double xHeliostat = std::strtod(argv[1], &end);
    double yHeliostat = std::strtod(argv[2], &end);
    double zHeliostat = std::strtod(argv[3], &end);
    double xAimingPoint = std::strtod(argv[4], &end);
    double yAimingPoint = std::strtod(argv[5], &end);
    double zAimingPoint = std::strtod(argv[6], &end);
    double sunAzimuth = std::strtod(argv[7], &end);
    double sunElevation = std::strtod(argv[8], &end);

    // Global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith
    // Positive angles in the counterclockwise direction according to the direction of the rotation axis

    // Defining the target
    TrackerTarget* target = new TrackerTarget;
    target->aimingPoint = vec3d(xAimingPoint, yAimingPoint, zAimingPoint); // target center 20 above the ground

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
    return 0;
}

void BluesolarHeliostatArmature(TrackerArmature2A& armature)
{
    armature.set_primaryShift(vec3d(0.0, 0.0, 2.415)); // primary shift vector.
    armature.set_primaryAxis(vec3d(-1.0, 0.0, 0.0)) ; // unit vector in the direction of the first axis of rotation while in default position.
    armature.set_primaryAngles(vec2d(0.0, 90.0)); // min and max rotation angles around the primary axis of rotation in degrees.

    armature.set_secondaryShift(vec3d(0.0, -0.0816, 0.0)); // secondary shift vector.
    armature.set_secondaryAxis(vec3d(0.0, 0.0, -1.0)); // unit vector in the direction of the second axis of rotation.
    armature.set_secondaryAngles(vec2d(-70.0, 55.0)); // min and max rotation angles around the secondary axis of rotation in degrees.

    armature.set_facetShift(vec3d(0., -0.105, 0.035)); // facet shift vector.
    armature.set_facetNormal(vec3d(0.0, -1.0, 0.0)); // unit vector in the direction of the facet's normal when in default position.

    armature.set_anglesDefault(vec2d(0.0, 0.0)); // values of the rotation angles in the default position in degrees.
}

ElevationAngleKM CreateBluesolarElevationAngleKM() {
    double gamma = 90.75 * gcf::degree; // radians
    double rab = 0.39254; // meters
    double rbc = 0.0465; // meters
    double rad = 0.43061; // meters
    double ra = 0.082; // meters
    double rd = 0.045; // meters
    return ElevationAngleKM(gamma, rab, rbc, rad, ra, rd);
}

HourAngleKM CreateBluesolarHourAngleKM() {
    double gamma = 22.0 * gcf::degree; // radians
    double rab = 0.35033; // meters
    double rbc = 0.0465; // meters
    double rad = 0.36527; // meters
    return HourAngleKM(gamma, rab, rbc, rad);
}