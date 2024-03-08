#include <map>
#include "WolframLibrary.h"

#include "TrackerTarget.h"
#include "TrackerArmature2A.h"


// Define the maps of the managed C++ classes
std::map<mint, TrackerTarget*> trackerTargetInstances;
std::map<mint, TrackerArmature2A*> trackerArmature2AInstances;

// Declare the class managers
void TrackerTarget_manage_instance(WolframLibraryData libData, mbool mode, mint id);
void TrackerArmature2A_manage_instance(WolframLibraryData libData, mbool mode, mint id);

// Register the class managers functions in WolframLibraryData
EXTERN_C DLLEXPORT int WolframLibrary_initialize(WolframLibraryData libData) {
    int err;
    err = libData->registerLibraryExpressionManager("TrackerTargetManager", TrackerTarget_manage_instance);
    if (err != LIBRARY_NO_ERROR) return err;
    return libData->registerLibraryExpressionManager("TrackerArmature2AManager", TrackerArmature2A_manage_instance);
}

EXTERN_C DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData) {
    libData->unregisterLibraryExpressionManager("TrackerTargetManager");
    libData->unregisterLibraryExpressionManager("TrackerArmature2AManager");
}

void TrackerTarget_manage_instance(WolframLibraryData libData, mbool mode, mint id) {
    if (mode == 0) { // Creation
        TrackerTarget* target = new TrackerTarget();
        trackerTargetInstances[id] = target;
    } else if (mode == 1) { // Destruction
        auto it = trackerTargetInstances.find(id);
        if (it != trackerTargetInstances.end()) {
            delete it->second;
            trackerTargetInstances.erase(it);
        }
    }
}

void TrackerArmature2A_manage_instance(WolframLibraryData libData, mbool mode, mint id) {
    if (mode == 0) { // Creation
        TrackerArmature2A* armature = new TrackerArmature2A();
        trackerArmature2AInstances[id] = armature;
    } else if (mode == 1) { // Destruction
        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            delete it->second;
            trackerArmature2AInstances.erase(it);
        }
    }
}

extern "C" {

    // Functions related to the Mathematica wrapping of the TrackerTarget class functionality

    // Wrapper functions for getters
    
    // Wrapper function to get the aiming point of a TrackerTarget
    DLLEXPORT int GetAimingPointTrackerTarget(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        auto it = trackerTargetInstances.find(id);
        if (it != trackerTargetInstances.end()) {
            vec3d aimingPoint = it->second->aimingPoint;

            MTensor out;
            mint dims[1] = {3};
            libData->MTensor_new(MType_Real, 1, dims, &out);
            double* data = libData->MTensor_getRealData(out);

            data[0] = aimingPoint.x;
            data[1] = aimingPoint.y;
            data[2] = aimingPoint.z;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        }
        return LIBRARY_FUNCTION_ERROR;
    }

    // Wrapper function to get the aiming angles of a TrackerTarget
    DLLEXPORT int GetAnglesTrackerTarget(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        auto it = trackerTargetInstances.find(id);
        if (it != trackerTargetInstances.end()) {
            vec2d angles = it->second->angles;

            MTensor out;
            mint dims[1] = {2};
            libData->MTensor_new(MType_Real, 1, dims, &out);
            double* data = libData->MTensor_getRealData(out);

            data[0] = angles.x;
            data[1] = angles.y;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        }
        return LIBRARY_FUNCTION_ERROR;
    }

    // Wrapper functions for setters
    DLLEXPORT int SetAimingPointTrackerTarget(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerTargetInstances.find(id);
        if (it != trackerTargetInstances.end()) {
            it->second->aimingPoint = vec3d(x, y, z);

            // Create an MTensor to hold the three double values
            MTensor out;
            mint dims[1] = {3}; // Create a tensor of rank 1 with 3 elements
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err; // Check for errors in tensor creation
            
            double* data = libData->MTensor_getRealData(out);
            
            // Assign the values to the tensor
            data[0] = it->second->aimingPoint.x;
            data[1] = it->second->aimingPoint.y;
            data[2] = it->second->aimingPoint.z;

            // Set the tensor as the return value
            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Function to set the aiming angles of a TrackerTarget
    DLLEXPORT int SetAnglesTrackerTarget(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);

        auto it = trackerTargetInstances.find(id);
        if (it != trackerTargetInstances.end()) {
            it->second->angles = vec2d(x, y);
            // Create an MTensor to hold the two double values
            MTensor out;
            mint dims[1] = {2}; // Create a tensor of rank 1 with 2 elements
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err; // Check for errors in tensor creation
            
            double* data = libData->MTensor_getRealData(out);
            
            // Assign the values to the tensor
            data[0] = it->second->angles.x;
            data[1] = it->second->angles.y;

            // Set the tensor as the return value
            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }  
    }

    // Functions related to the TrackerArmature2A class

    // Wrapper functions for getters
    DLLEXPORT int GetPrimaryShift(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        // Look up the TrackerArmature2A instance by ID
        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            // Extract the primary shift data from the instance
            const vec3d& shift = it->second->get_primaryShift();

            // Create an MTensor to hold the three double values
            MTensor out;
            mint dims[1] = {3}; // Create a tensor of rank 1 with 3 elements
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err; // Check for errors in tensor creation

            double* data = libData->MTensor_getRealData(out);

            // Assign the values to the tensor
            data[0] = shift.x;
            data[1] = shift.y;
            data[2] = shift.z;

            // Set the tensor as the return value
            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR; // Instance not found
        }
    }

    DLLEXPORT int GetPrimaryAxisTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec3d& axis = it->second->get_primaryAxis();

            MTensor out;
            mint dims[1] = {3};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = axis.x;
            data[1] = axis.y;
            data[2] = axis.z;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for get_primaryAngles
    DLLEXPORT int GetPrimaryAnglesTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec2d& angles = it->second->get_primaryAngles();

            MTensor out;
            mint dims[1] = {2};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = angles.x;
            data[1] = angles.y;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for get_secondaryShift
    DLLEXPORT int GetSecondaryShiftTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec3d& shift = it->second->get_secondaryShift();

            MTensor out;
            mint dims[1] = {3};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = shift.x;
            data[1] = shift.y;
            data[2] = shift.z;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for get_secondaryAxis
    DLLEXPORT int GetSecondaryAxisTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec3d& axis = it->second->get_secondaryAxis();

            MTensor out;
            mint dims[1] = {3};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = axis.x;
            data[1] = axis.y;
            data[2] = axis.z;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for get_secondaryAngles
    DLLEXPORT int GetSecondaryAnglesTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec2d& angles = it->second->get_secondaryAngles();

            MTensor out;
            mint dims[1] = {2};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = angles.x;
            data[1] = angles.y;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for get_facetShift
    DLLEXPORT int GetFacetShiftTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec3d& shift = it->second->get_facetShift();

            MTensor out;
            mint dims[1] = {3};  // A rank-1 tensor with 3 elements
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err; // Check for tensor creation errors

            double* data = libData->MTensor_getRealData(out);
            data[0] = shift.x;
            data[1] = shift.y;
            data[2] = shift.z;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR; // Instance not found
        }
    }

    // Wrapper function for get_facetNormal
    DLLEXPORT int GetFacetNormalTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec3d& normal = it->second->get_facetNormal();

            MTensor out;
            mint dims[1] = {3};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = normal.x;
            data[1] = normal.y;
            data[2] = normal.z;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for get_anglesDefault
    DLLEXPORT int GetAnglesDefaultTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            const vec2d& angles = it->second->get_anglesDefault();

            MTensor out;
            mint dims[1] = {2};
            int err = libData->MTensor_new(MType_Real, 1, dims, &out);
            if (err) return err;

            double* data = libData->MTensor_getRealData(out);
            data[0] = angles.x;
            data[1] = angles.y;

            MArgument_setMTensor(Res, out);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_primaryShift
    DLLEXPORT int SetPrimaryShiftTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_primaryShift(vec3d(x, y, z));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_primaryAxis
    DLLEXPORT int SetPrimaryAxisTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_primaryAxis(vec3d(x, y, z));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_primaryAngles
    DLLEXPORT int SetPrimaryAnglesTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_primaryAngles(vec2d(x, y));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }



    // Wrapper function for set_secondaryShift
    DLLEXPORT int SetSecondaryShiftTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_secondaryShift(vec3d(x, y, z));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_secondaryAxis
    DLLEXPORT int SetSecondaryAxisTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_secondaryAxis(vec3d(x, y, z));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    DLLEXPORT int SetSecondaryAnglesTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_secondaryAngles(vec2d(x, y));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_facetShift
    DLLEXPORT int SetFacetShiftTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_facetShift(vec3d(x, y, z));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_facetNormal
    DLLEXPORT int SetFacetNormalTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);
        double z = MArgument_getReal(Args[3]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_facetNormal(vec3d(x, y, z));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for set_anglesDefault
    DLLEXPORT int SetAnglesDefaultTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint id = MArgument_getInteger(Args[0]);
        double x = MArgument_getReal(Args[1]);
        double y = MArgument_getReal(Args[2]);

        auto it = trackerArmature2AInstances.find(id);
        if (it != trackerArmature2AInstances.end()) {
            it->second->set_anglesDefault(vec2d(x, y));
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR;
        }
    }

    // Wrapper function for update
    DLLEXPORT int UpdateTrackerArmature2A(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
        mint armatureId = MArgument_getInteger(Args[0]);
        MTensor transformTensor = MArgument_getMTensor(Args[1]);
        MTensor sunVectorTensor = MArgument_getMTensor(Args[2]);
        mint targetId = MArgument_getInteger(Args[3]);

        // Find instances in their respective maps
        auto armatureIt = trackerArmature2AInstances.find(armatureId);
        auto targetIt = trackerTargetInstances.find(targetId);

        if (armatureIt != trackerArmature2AInstances.end() && targetIt != trackerTargetInstances.end()) {
            double* transformData = libData->MTensor_getRealData(transformTensor);
            double* sunVectorData = libData->MTensor_getRealData(sunVectorTensor);
            
            vec3d sunVec(sunVectorData[0], sunVectorData[1], sunVectorData[2]);
            
            double mat[4][4];
            for (int i = 0; i < 16; ++i) {
                mat[i / 4][i % 4] = transformData[i];
            }
            Transform transform(mat);

            // Call the update method on the armature with the target and other parameters
            armatureIt->second->update(transform, sunVec, targetIt->second);
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_FUNCTION_ERROR; // Either armature or target instance not found
        }
    }

} // extern "C"