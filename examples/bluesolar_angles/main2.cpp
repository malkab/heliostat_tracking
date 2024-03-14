#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Ray.h"
#include "Transform.h"

void BluesolarHeliostatArmature(TrackerArmature2A& armature);

int main(int argc, char *argv[])
{
     // Check if the correct number of arguments is passed
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " x y z sunAzimuth sunElevation" << std::endl;
        return 1; // Return with error code
    }

    // Assuming the arguments are correctly ordered: x, y, z, sunAzimuth, sunElevation
    // Convert the arguments from strings to doubles
    char* end;
    double x = std::strtod(argv[1], &end);
    double y = std::strtod(argv[2], &end);
    double z = std::strtod(argv[3], &end);
    double sunAzimuth = std::strtod(argv[4], &end);
    double sunElevation = std::strtod(argv[5], &end);

    // Global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith
    // Positive angles in the counterclockwise direction according to the direction of the rotation axis

    // Defining the target
    TrackerTarget* target = new TrackerTarget;
    target->aimingPoint = vec3d(0.0, 0.0, 20.0); // target center 20 above the ground

    // Setting up the tracker armature for the BlueSolar heliostat
    TrackerArmature2A armature;
    BluesolarHeliostatArmature(armature);

    // Moving the heliostat armature to the location defined by the user
    Transform heliostatLocation = Transform::translate(x, y, z); // actual location of a heliostat in the bluesolar field

    // Defining the sun vector in the global coordinate system from sun angles (azimuth and elevation) in degrees provided by the user.
    // Azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
    double sun_azimuth = sunAzimuth * gcf::degree;
    double sun_elevation = sunElevation * gcf::degree;
    vec3d sunVector(cos(sun_elevation)*sin(sun_azimuth), cos(sun_elevation)*cos(sun_azimuth),sin(sun_elevation));

    // Computing the angles the heliostat armature should turn to reflect the direct solar radiation to the target
    armature.update(heliostatLocation, sunVector, target);

    // Printing the results
    std::cout << target->angles << std::endl;

    return 1;
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