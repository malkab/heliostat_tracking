#include <iomanip>
#include <iostream>

#include "vec2d.h"
#include "vec3d.h"
#include "Ray.h"
#include "Transform.h"
#include "TrackerArmature2A.h"
#include "TrackerTarget.h"

vec2d GetVector2DFromUser();
vec3d GetVector3DFromUser();
int GetUserSelection(Interval validRange);
void ShowOptionsMainMenu();
void ShowInputData(const TrackerArmature2A& armature, const TrackerTarget* target, const Transform& location, const vec2d& sunAngles);
void ShowResults(const TrackerArmature2A& armature, const TrackerTarget* target, const Transform& location, const vec2d& sunAngles, 
                     const vec3d& facetReferencePoint, const vec3d& facetNormal, const vec3d& intersectAtTarget);
void InitializeElements(TrackerTarget* target, Transform& heliostatLocation, vec2d& sunAngles);
void ChangeInputData(TrackerArmature2A& armature, TrackerTarget* target, Transform& location, vec2d& sunAngles);
void ComputeResults(TrackerArmature2A& armature, TrackerTarget* target, const Transform& location, const vec3d& sunVector,
                     vec3d& facetReferencePoint, vec3d& heliostatNormal, vec3d& intersectionAtTarget);
vec3d IntersectionWithTarget(Ray reflectedRay, vec3d aimingPoint);


int main(int argc, char *argv[])
{
    // Global coordinate system x > 0 towards East, y > 0 towards North, z > 0 towards Zenith
    // Positive angles in the counterclockwise direction according to the direction of the rotation axis

    TrackerArmature2A armature;
    TrackerTarget* target = new TrackerTarget;
    Transform heliostatLocation;
    vec2d sunAngles;

    InitializeElements(target, heliostatLocation, sunAngles);
    
    Interval optionsRange(0, 2);
    int userSelection;

    do
    {
        ShowOptionsMainMenu();
        userSelection = GetUserSelection(optionsRange);

        switch (userSelection)
        {
            case 1:
                ChangeInputData(armature, target, heliostatLocation, sunAngles);           
                break;
            case 2:
                std::cout << "Thansk for selecting option 2. Aim heliostat." << std::endl;
                // Defining the initial sun vector in the global coordinate system from sun angles (azimuth and elevation).
                // Azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
                double sun_azimuth = sunAngles.x * gcf::degree;
                double sun_elevation = sunAngles.y * gcf::degree;
                vec3d sunVector(cos(sun_elevation)*sin(sun_azimuth), cos(sun_elevation)*cos(sun_azimuth),sin(sun_elevation));

                // COMPUTING THE RESULTS
                vec3d facetReferencePoint, facetNormal, intersectAtTarget;
                ComputeResults(armature, target, heliostatLocation, sunVector, facetReferencePoint, facetNormal, intersectAtTarget);
                ShowInputData(armature, target, heliostatLocation, sunAngles);
                ShowResults(armature, target, heliostatLocation, sunAngles, facetReferencePoint, facetNormal, intersectAtTarget);
                break;                          
        }
    }
    while(optionsRange.isInside(userSelection) && userSelection != 0);

    std::cout << "Thansk for using the program!" << userSelection << std::endl;   

    return 1;
}

vec2d GetVector2DFromUser()
{
    double x, y, z;

    std::cout << "Please, enter x: ";
    std::cin >> x;
    std::cout << "Please, enter y: ";
    std::cin >> y;

    vec2d vector(x, y);
    std::cout << "The 2D vector entered is: (" << vector << ")." << std::endl;
    return vector;
}

vec3d GetVector3DFromUser()
{
    double x, y, z;

    std::cout << "Please, enter x: ";
    std::cin >> x;
    std::cout << "Please, enter y: ";
    std::cin >> y;
    std::cout << "Please, enter z: ";
    std::cin >> z;

    vec3d vector(x, y, z);
    std::cout << "The 3D vector entered is: (" << vector << ")." << std::endl;
    return vector;
}

int GetUserSelection(Interval selectionRange)
{
    int selection = -1;
    while(selectionRange.isInside(selection) == false) 
    {

        std::cout << "\nPlease enter the option you want to select (from " << int(selectionRange.min()) << " to " << int(selectionRange.max()) << "): ";
        std::cin >>  selection;
        if(selectionRange.isInside(selection) == false) std::cout << "Invalid selection. Please, try again." << std::endl;
    }

    return selection;
}

void ShowOptionsMainMenu()
{
    std::cout << "\n------------------------- MAIN ----------------------------" << std::endl; 

    std::cout << "OPTIONS" << std::endl;
    std::cout << "  0. Exit the program." << std::endl;
    std::cout << "  1. Change input data." << std::endl;
    std::cout << "  2. Aim heliostat." << std::endl;
}

void ShowInputData(const TrackerArmature2A& armature, const TrackerTarget* target, const Transform& location, const vec2d& sunAngles)
{
        std::cout << "\n-------------------------- INPUT DATA -----------------------" << std::endl;
    // Printing the example
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    std::cout << "Armature characteristics" << std::endl;

    std::cout << "  1. Primary shift:    " << armature.get_primaryShift() << std::endl;
    std::cout << "  2. Primary axis:     " << armature.get_primaryAxis() << std::endl;
    std::cout << "  3. Primary angles:   " << armature.get_primaryAngles() << std::endl;

    std::cout << "  4. Secondary shift:  " << armature.get_secondaryShift() << std::endl;
    std::cout << "  5. Secondary axis:   " << armature.get_secondaryAxis() << std::endl;
    std::cout << "  6. Secondary angles: " << armature.get_secondaryAngles() << std::endl;

    std::cout << "  7. Facet shift:      " << armature.get_facetShift() << std::endl;
    std::cout << "  8. Facet normal:     " << armature.get_facetNormal() << std::endl;
    std::cout << "  9. Default angles:   " << armature.get_anglesDefault() << std::endl << std::endl;
  
    std::cout << "Heliostat location and aiming point" << std::endl;
    std::cout << " 10. Location:        " << location.transformPoint(vec3d(0.,0.,0)) << std::endl;
    std::cout << " 11. Aiming point:    " << target->aimingPoint << std::endl << std::endl;

    std::cout << "Sun position" << std::endl;
    std::cout << " 12. Azimuth (North towards East): " << sunAngles.x << " degrees" << std::endl;
    std::cout << " 13. Elevation in degrees        : " << sunAngles.y << " degrees" << std::endl;
}

void ShowResults(const TrackerArmature2A& armature, const TrackerTarget* target, const Transform& location, const vec2d& sunAngles, 
                     const vec3d& facetReferencePoint, const vec3d& facetNormal, const vec3d& intersectAtTarget)
{
    std::cout << "\n---------------------------- RESULTS ------------------------" << std::endl;    
    std::cout << "Rotation angles in degrees: " << target->angles << std::endl;
    std::cout << "Facet reference point     : " << facetReferencePoint << std::endl;
    std::cout << "Facet normal              : " << facetNormal << std::endl;
    std::cout << "Reflected ray intersection with target: " << intersectAtTarget << std::endl;
}

void InitializeElements(TrackerTarget* target, Transform& heliostatLocation, vec2d& sunAngles)
{
    target->aimingPoint = vec3d(0.0, 0.0, 100.0); // target 100 above the pivot point of the heliostat

    // Defining initial heliostat location
    heliostatLocation = Transform::translate(0.0, 100.0, 0.0); // heliostat 100 to the North of the target

    // Defining the initial sun sun angles (azimuth and elevation).
    // Azimuth = 0 at North and > 0 towards East. Elevation = 0 at the horizontal plane and > 0 towards zentihg
    sunAngles.x = 180.0; // Azimuth in degrees
    sunAngles.y = 45.0;  // Elevation in degree
}

void ChangeInputData(TrackerArmature2A& armature, TrackerTarget* target, Transform& location, vec2d& sunAngles)
{
    Interval optionsRange(0, 13);   
    int selection;
    vec3d vector3d;
    vec2d vector2d;

    do
    {
        ShowInputData(armature, target, location, sunAngles);
        selection = GetUserSelection(optionsRange);
        switch (selection)
        {
            case 0:
                std::cout << "Finish changing the Input Data. Returning to main menu." << std::endl; 
                break;            
            case 1:
                std::cout << "Changing primary shift 3d vector." << std::endl;
                vector3d = GetVector3DFromUser();
                armature.set_primaryShift(vector3d);
                break;
            case 2:
                std::cout << "Changing primary axis 3d unit vector." << std::endl;
                vector3d = GetVector3DFromUser();
                armature.set_primaryAxis(vector3d);                 
                break;
            case 3:
                std::cout << "Changing primary angles." << std::endl;
                vector2d = GetVector2DFromUser();
                armature.set_primaryAngles(vector2d);
                break;
            case 4:
                std::cout << "Changing secondary shift." << std::endl;  
                vector3d = GetVector3DFromUser();
                armature.set_secondaryShift(vector3d);
                break;
            case 5:
                std::cout << "Changing secondary axis." << std::endl;  
                vector3d = GetVector3DFromUser();
                armature.set_secondaryAxis(vector3d);
                break;
            case 6:
                std::cout << "Changing secondary angles." << std::endl;  
                vector2d = GetVector2DFromUser();
                armature.set_secondaryAngles(vector2d);
                break;
            case 7:
                std::cout << "Changing facet shift." << std::endl;
                vector3d = GetVector3DFromUser();
                armature.set_facetShift(vector3d);               
                break;
            case 8:
                std::cout << "Changing facet normal." << std::endl;
                vector3d = GetVector3DFromUser();
                armature.set_facetNormal(vector3d);                
                break;
            case 9:
                std::cout << "Changing default angles." << std::endl;
                vector2d = GetVector2DFromUser();
                armature.set_anglesDefault(vector2d);                
                break;
            case 10:
                std::cout << "Changing location." << std::endl;
                vector3d = GetVector3DFromUser();
                location = Transform::translate(vector3d);;
                break;
            case 11:
                std::cout << "Changing aiming point." << std::endl;
                vector3d = GetVector3DFromUser();
                target->aimingPoint = vector3d;
                break;
            case 12:
                std::cout << "Changking sun azimuth." << std::endl;
                std::cout << "Please, enter sun azimuth in degrees (positive from North to East): ";
                std::cin >> sunAngles.x; 
                break;
            case 13:
                std::cout << "Changing sun elevation." << std::endl;
                std::cout << "Please, enter sun elevation in degrees: ";
                std::cin >> sunAngles.y; 
                break;                                                                                                                                                    
        }
    }
    while(optionsRange.isInside(selection) && selection != 0);
}

void ComputeResults(TrackerArmature2A& armature, TrackerTarget* target, const Transform& location, const vec3d& sunVector,
                     vec3d& facetReferencePoint, vec3d& facetNormal, vec3d& intersectionAtTarget)
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

vec3d IntersectionWithTarget(Ray reflectedRay, vec3d aimingPoint)
{   
    double alpha = -(reflectedRay.origin.y / reflectedRay.direction().y);
    vec3d intersection = reflectedRay.point(alpha);
    return vec3d(intersection);
}











