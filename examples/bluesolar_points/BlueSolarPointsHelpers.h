// examples/BluesolarAimingPointHelpers.h
#pragma once

#include "TrackerArmature2A.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"

bool ConvertAndValidateArguments(int argc, char* argv[], 
                                 double& xHeliostat, double& yHeliostat, double& zHeliostat, 
                                 double& sunAzimuth, double& sunElevation, double& yTarget,
                                 double& lengthElevationActuator, double& lengthHourAngleActuator);
void BluesolarHeliostatArmature(TrackerArmature2A& armature);
ElevationAngleKM CreateBluesolarElevationAngleKM();
HourAngleKM CreateBluesolarHourAngleKM();