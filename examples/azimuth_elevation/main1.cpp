#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Transform.h"


int main(int argc, char *argv[])
{
    // Example 1 - Azimuth - elevation heliostat with the axis crossing in the center

    // Setting up the tracker armature
    TrackerArmature2A aeAxesCrossingH;
   
    aeAxesCrossingH.set_primaryShift(vec3d(0.0, 0.0, 2.0)); // vertical pedestal 2 meters above the horizontal plante
    aeAxesCrossingH.set_primaryAxis(vec3d(0.0, 0.0, 1.0)) ; // unit vector in the direction of the first axis of rotation
    aeAxesCrossingH.set_primaryAngles(vec2d(0.0, 360.0)); // min and max rotation angles around the primary axis 

    aeAxesCrossingH.set_secondaryShift(vec3d(0.0, 0.0, 0.0)); // null distance between the first axist of rotation and the second, i.e., the axes cross 
    aeAxesCrossingH.set_secondaryAxis(vec3d(-1.0, 0.0, 0.0)); // unit vector in the direction of the second axis of rotation
    aeAxesCrossingH.set_secondaryAngles(vec2d(-90.0, 90.0)); // min and max rotation angles around the secondary axis 

    aeAxesCrossingH.set_facetShift(vec3d(0., 0., 0.)); // null distance between the secons axis of rotation and the facet.
    aeAxesCrossingH.set_facetNormal(vec3d(0.0, 1.0, 0.0)); // unit vector in the direction of the facet normal when in default heliostat orientation

    aeAxesCrossingH.set_anglesDefault(vec2d(0.0, 0.0)); // default values of the rotation angles in degrees

    // Defining the scene. 
    // Assuming global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith 
    TrackerTarget* target = new TrackerTarget;
    target->aimingPoint = vec3d(0.0, 0.0, 102.0); // target 100 above the pivot point of the heliostat

    Transform heliostatLocation = Transform::translate(0.0, 100.0, 0.0); // heliostat 100 to the North of the target

    // Defining the sun vector in the global coordinate system from sun angles (azimuth and elevation).
    // Azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
    double sun_azimuth = 180.0 * gcf::degree;
    double sun_elevation = 45.0 * gcf::degree;

    vec3d sunVector(cos(sun_elevation)*sin(sun_azimuth), cos(sun_elevation)*cos(sun_azimuth),sin(sun_elevation));
    
    // Computing the angles the heliostat should turn to reflect the direct solar radiation to the target
    aeAxesCrossingH.update(heliostatLocation, sunVector, target);
 
    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    std::cout << "Sun Position" << std::endl;
    std::cout << " - Azimuth (North towards East): " << sun_azimuth/gcf::degree << " degrees" << std::endl;
    std::cout << " - Elevation in degrees: " << sun_elevation/gcf::degree << " degrees" << std::endl;
    std::cout << "Rotation angles in degrees: " << target->angles << std::endl;

    //Facet's reference point
    vec3d r = aeAxesCrossingH.get_secondary().getTransform(target->angles.y).transformPoint(aeAxesCrossingH.get_facet().shift);
    r = aeAxesCrossingH.get_primary().getTransform(target->angles.x).transformPoint(r);
    std::cout << "Facet reference point location: " << r << std::endl;

    //Heliostat normal
    vec3d n = aeAxesCrossingH.get_secondary().getTransform(target->angles.y*gcf::degree).transformNormal(aeAxesCrossingH.get_facet().normal);
    n = aeAxesCrossingH.get_primary().getTransform(target->angles.x*gcf::degree).transformNormal(n);
    std::cout << "Facet normal: " << n << std::endl;

    std::cout << "DONE" <<std::endl;
    return 1;
}