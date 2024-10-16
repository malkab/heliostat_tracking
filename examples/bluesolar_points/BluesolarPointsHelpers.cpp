#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Ray.h"
#include "Transform.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"
#include "BluesolarPointsHelpers.h" //

bool ConvertAndValidateArguments(int argc, char* argv[], 
                                 double& xHeliostat, double& yHeliostat, double& zHeliostat, 
                                 double& sunAzimuth, double& sunElevation, double& yTarget,
                                 double& lengthElevationActuator, double& lengthHourAngleActuator) {
    if (argc != 9) {
        std::cerr << "Usage: " << argv[0] << " xHeliostat yHeliostat zHeliostat sunAzimuth sunElevation yTarget lengthElevationActuator lengthHourAngleActuator" << std::endl;
        return false;
    }

    char* end;
    xHeliostat = std::strtod(argv[1], &end);
    if (end == argv[1]) { std::cerr << "Invalid argument: " << argv[1] << std::endl; return false; }
    yHeliostat = std::strtod(argv[2], &end);
    if (end == argv[2]) { std::cerr << "Invalid argument: " << argv[2] << std::endl; return false; }
    zHeliostat = std::strtod(argv[3], &end);
    if (end == argv[3]) { std::cerr << "Invalid argument: " << argv[3] << std::endl; return false; }
    sunAzimuth = std::strtod(argv[4], &end);
    if (end == argv[4]) { std::cerr << "Invalid argument: " << argv[4] << std::endl; return false; }
    sunElevation = std::strtod(argv[5], &end);
    if (end == argv[5]) { std::cerr << "Invalid argument: " << argv[5] << std::endl; return false; }
    yTarget = std::strtod(argv[6], &end);
    if (end == argv[6]) { std::cerr << "Invalid argument: " << argv[6] << std::endl; return false; }
    lengthElevationActuator = std::strtod(argv[7], &end);
    if (end == argv[7]) { std::cerr << "Invalid argument: " << argv[7] << std::endl; return false; }
    lengthHourAngleActuator = std::strtod(argv[8], &end);
    if (end == argv[8]) { std::cerr << "Invalid argument: " << argv[8] << std::endl; return false; }

    return true;
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
    double gamma = 1.5566945190927768; // radians  
    double rab = 0.3679941188052566; // meters  
    double rbc = 0.08587871211683747; // meters
    double rad = 0.45469491923653677; // meters      
    double alpha2 = 0.08155204289894769; // radians
    double offset = 0.04037; // meters
    return ElevationAngleKM(gamma, rab, rbc, rad, alpha2, offset);
}

HourAngleKM CreateBluesolarHourAngleKM() {
    double gamma = 0.543717625543648; // radians
    double rab = 0.3716059721933388; // meters
    double rbc = 0.05209218963038278; // meters    
    double rad = 0.3390154085801952; // meters    
    double offset = 0.04037; // meters    
    return HourAngleKM(gamma, rab, rbc, rad, offset);
}