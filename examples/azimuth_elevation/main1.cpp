#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Transform.h"


int main(int argc, char *argv[])
{

    // Defining the scene. Assuming global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith 
    TrackerTarget* myTarget = new TrackerTarget;
    TrackerArmature2A myTracker;
    Transform myTransform = Transform::translate(0.0, 100.0, 0.0);

    // Defining the sun vector in the global coordinate system from sun angles.
    // Considering azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
    double sun_azimuth = 180.0 * gcf::degree;
    double sun_elevation = 45.0 * gcf::degree;

    vec3d sunVector(cos(sun_elevation)*sin(sun_azimuth), 
                    cos(sun_elevation)*cos(sun_azimuth),
                    sin(sun_elevation));
    
    myTracker.update(myTransform, sunVector, myTarget);
 
    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    std::cout << "Sun Position" << std::endl;
    std::cout << " - Azimuth (North towards East): " << sun_azimuth/gcf::degree << " degrees" << std::endl;
    std::cout << " - Elevation in degrees: " << sun_elevation/gcf::degree << " degrees" << std::endl;
    std::cout << "Rotation angles in degrees: " << myTarget->angles << std::endl;

    //Facet's reference point
    vec3d r = myTracker.get_secondary().getTransform(myTarget->angles.y).transformPoint(myTracker.get_facet().shift);
    r = myTracker.get_primary().getTransform(myTarget->angles.x).transformPoint(r);
    std::cout << "Facet reference point location: " << r << std::endl;

    //Heliostat normal
    vec3d n = myTracker.get_secondary().getTransform(myTarget->angles.y*gcf::degree).transformNormal(myTracker.get_facet().normal);
    n = myTracker.get_primary().getTransform(myTarget->angles.x*gcf::degree).transformPoint(n);
    std::cout << "Facet normal: " << n << std::endl;

    std::cout << "DONE" <<std::endl;
    return 1;
}