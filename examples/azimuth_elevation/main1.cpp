#include <iomanip>
#include <iostream>

#include "TrackerArmature2A.h"
#include "TrackerTarget.h"
#include "Ray.h"
#include "Transform.h"

vec3d IntersectionWithTarget(Ray reflectedRay, vec3d aimingPoint);
void ComputeResults(const Transform& location, const vec3d& sunVector, TrackerTarget* target, 
                    TrackerArmature2A& armature, vec3d& facetReferencePoint, vec3d& heliostatNormal, vec3d& intersectionAtTarget);
void PrintingResults(const TrackerArmature2A& armature, const Transform& location, TrackerTarget* target, const vec2d& sunAngles, 
                     const vec3d& facetReferencePoint, const vec3d& facetNormal, const vec3d& intersectAtTarget);

int main(int argc, char *argv[])
{
    // Example 1 - Azimuth - elevation heliostat with the axes crossing at the center

    // Global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith
    // Positive angles in the counterclockwise direction according to the direction of the rotation axis

    // Setting up the tracker armature
    TrackerArmature2A armature;
   
    armature.set_primaryShift(vec3d(0.0, 0.0, 2.0)); // primary shift vector.
    armature.set_primaryAxis(vec3d(0.0, 0.0, -1.0)) ; // unit vector in the direction of the first axis of rotation.
    armature.set_primaryAngles(vec2d(0.0, 360.0)); // min and max rotation angles around the primary axis of rotation in degrees.

    armature.set_secondaryShift(vec3d(0.0, 0.0, 0.0)); // secondary shift vector.
    armature.set_secondaryAxis(vec3d(1.0, 0.0, 0.0)); // unit vector in the direction of the second axis of rotation.
    armature.set_secondaryAngles(vec2d(-90.0, 90.0)); // min and max rotation angles around the secondary axis of rotation in degrees.

    armature.set_facetShift(vec3d(0., 0., 0.)); // facet shift vector.
    armature.set_facetNormal(vec3d(0.0, 1.0, 0.0)); // unit vector in the direction of the facet's normal when in default position.

    armature.set_anglesDefault(vec2d(0.0, 0.0)); // values of the rotation angles in the default position in degrees.

    // Defining the scene. 
    TrackerTarget* target = new TrackerTarget;
    target->aimingPoint = vec3d(0.0, 0.0, 102.0); // target 100 above the pivot point of the heliostat

    Transform heliostatLocation = Transform::translate(0.0, 100.0, 0.0); // heliostat 100 to the North of the target

    // Defining the sun vector in the global coordinate system from sun angles (azimuth and elevation).
    // Azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
    double sun_azimuth = 180.0 * gcf::degree;
    double sun_elevation = 45.0 * gcf::degree;

    vec3d sunVector(cos(sun_elevation)*sin(sun_azimuth), cos(sun_elevation)*cos(sun_azimuth),sin(sun_elevation));

    // COMPUTING THE RESULTS
    vec3d facetReferencePoint, heliostatNormal, intersectionAtTarget;
    ComputeResults(heliostatLocation, sunVector, target, armature, facetReferencePoint, heliostatNormal, intersectionAtTarget);

    // Printing the results
    std::cout << "EXAMPLE 1 - AZIMUTH - ELEVATION HELIOSTAT WITH CROSSING AXES OF ROTATION" << std::endl << std::endl;
    PrintingResults(armature, heliostatLocation, target, vec2d(sun_azimuth, sun_elevation), facetReferencePoint, heliostatNormal, intersectionAtTarget);

    // Example 2 - Same than Example 1 but varying the angles rage of the primary and secondary axes of rotation
    armature.set_primaryAngles(vec2d(-180.0, 180.0)); // min and max rotation angles around the primary axis of rotation in degrees.  
    armature.set_secondaryAngles(vec2d(0.0, 180.0)); // min and max rotation angles around the secondary axis of rotation in degrees.
    armature.set_facetNormal(vec3d(0.0, 0.0, -1.0)); // unit vector in the direction of the facet's normal when in default position.     

    // Printing the results
    std::cout << "\n\nEXAMPLE 2 - AZIMUTH - ELEVATION HELIOSTAT WITH CROSSING AXES OF ROTATION BUT DIFFERENT ANMGLE RANGES" << std::endl << std::endl;
    ComputeResults(heliostatLocation, sunVector, target, armature, facetReferencePoint, heliostatNormal, intersectionAtTarget);
    PrintingResults(armature, heliostatLocation, target, vec2d(sun_azimuth, sun_elevation), facetReferencePoint, heliostatNormal, intersectionAtTarget);

    // Example 3 - Same than Example 1 but with a secondary shift separating the primary and secondary axes of rotation
    // Returning to Heliostat 1 configuration
    armature.set_primaryAngles(vec2d(0.0, 360.0)); // min and max rotation angles around the primary axis of rotation in degrees.
    armature.set_secondaryAngles(vec2d(-90.0, 90.0)); // min and max rotation angles around the secondary axis of rotation in degrees.
    armature.set_facetNormal(vec3d(0.0, 1.0, 0.0)); // unit vector in the direction of the facet's normal when in default position.

    // Adding a displacement to the second axis of 0.5 m in the y-direction
    armature.set_secondaryShift(vec3d(0.0, 0.5, 0.0)); // end point of the secondary shift, i.e., origin of the second axis of rotation.

    // Printing the results
    std::cout << "\n\nEXAMPLE 3 - AZIMUTH - ELEVATION HELIOSTAT WITH NOT CROSSING AXES OF ROTATION" << std::endl << std::endl;
    ComputeResults(heliostatLocation, sunVector, target, armature, facetReferencePoint, heliostatNormal, intersectionAtTarget);
    PrintingResults(armature, heliostatLocation, target, vec2d(sun_azimuth, sun_elevation), facetReferencePoint, heliostatNormal, intersectionAtTarget);

    // Example 4 - Same than Example 3 but adding a shift separating the facet from the secondary axes of rotation
    armature.set_facetShift(vec3d(0., 0.5, 0.)); // end point of the facet shift, i.e., centre of the facet in the default position.
    // Printing the results
    std::cout << "\n\nEXAMPLE 4 - AZIMUTH - ELEVATION HELIOSTAT WITH NOT CROSSING AXES OF ROTATION AND FACET SHIFT" << std::endl << std::endl;
    ComputeResults(heliostatLocation, sunVector, target, armature, facetReferencePoint, heliostatNormal, intersectionAtTarget);
    PrintingResults(armature, heliostatLocation, target, vec2d(sun_azimuth, sun_elevation), facetReferencePoint, heliostatNormal, intersectionAtTarget);

    std::cout << "DONE" <<std::endl;
    return 1;
}

vec3d IntersectionWithTarget(Ray reflectedRay, vec3d aimingPoint)
{   
    double alpha = -(reflectedRay.origin.y / reflectedRay.direction().y);
    vec3d intersection = reflectedRay.point(alpha);
    return vec3d(intersection);
}

void ComputeResults(const Transform& location, const vec3d& sunVector, TrackerTarget* target, 
                    TrackerArmature2A& armature, vec3d& facetReferencePoint, vec3d& facetNormal, vec3d& intersectionAtTarget)
{
    // Computing the angles the heliostat armature should turn to reflect the direct solar radiation to the target
    armature.update(location, sunVector, target);

    //Facet's reference point
    facetReferencePoint = armature.get_secondary().getTransform((target->angles.y)*gcf::degree).transformPoint(armature.get_facet().shift);
    facetReferencePoint = armature.get_primary().getTransform((target->angles.x)*gcf::degree).transformPoint(facetReferencePoint);
    facetReferencePoint = location.transformPoint(facetReferencePoint);

    //Heliostat normal
    facetNormal = armature.get_secondary().getTransform((target->angles.y)*gcf::degree).transformNormal(armature.get_facet().normal);
    facetNormal = armature.get_primary().getTransform((target->angles.x)*gcf::degree).transformNormal(facetNormal);

    // Reflection on the target
    vec3d t = (2.0*dot(sunVector, facetNormal))*facetNormal - sunVector;
    
    Ray reflectedRay = Ray(facetReferencePoint, t);
    intersectionAtTarget = IntersectionWithTarget(reflectedRay, target->aimingPoint);
}

void PrintingResults(const TrackerArmature2A& armature, const Transform& location, TrackerTarget* target, const vec2d& sunAngles, 
                     const vec3d& facetReferencePoint, const vec3d& facetNormal, const vec3d& intersectAtTarget)
{
   // Printing the example
    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    std::cout << "  Heliostat characteristics" << std::endl;
    std::cout << "      Primary shift:    " << armature.get_primaryShift() << std::endl;
    std::cout << "      Primary axis:     " << armature.get_primaryAxis() << std::endl;
    std::cout << "      Primary angles:   " << armature.get_primaryAngles() << std::endl;

    std::cout << "      Secondary shift:  " << armature.get_secondaryShift() << std::endl;
    std::cout << "      Secondary axis:   " << armature.get_secondaryAxis() << std::endl;
    std::cout << "      Secondary angles: " << armature.get_secondaryAngles() << std::endl;

    std::cout << "      Facet shift:      " << armature.get_facetShift() << std::endl;
    std::cout << "      Facet normal:     " << armature.get_facetNormal() << std::endl;
    std::cout << "      Default angles:   " << armature.get_anglesDefault() << std::endl << std::endl;

    std::cout << "      Location:         " << location.transformPoint(vec3d(0.,0.,0)) << std::endl;
    std::cout << "      Aiming point:     " << target->aimingPoint << std::endl << std::endl;

    std::cout << "  Sun position information" << std::endl;
    std::cout << "      Azimuth (North towards East): " << sunAngles.x/gcf::degree << " degrees" << std::endl;
    std::cout << "      Elevation in degrees        : " << sunAngles.y/gcf::degree << " degrees" << std::endl << std::endl;

    std::cout << "  Results:" << std::endl;    
    std::cout << "      Rotation angles in degrees: " << target->angles << std::endl;
    std::cout << "      Facet reference point     : " << facetReferencePoint << std::endl;
    std::cout << "      Facet normal              : " << facetNormal << std::endl;
    std::cout << "      Reflected ray intersection with target: " << intersectAtTarget << std::endl;
}