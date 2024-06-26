// examples/BluesolarHelpers.h
#pragma once

#include "TrackerArmature2A.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"

bool ConvertAndValidateArguments(int argc, char* argv[], 
                                 double& xHeliostat, double& yHeliostat, double& zHeliostat, 
                                 double& xAimingPoint, double& yAimingPoint, double& zAimingPoint, 
                                 double& sunAzimuth, double& sunElevation);
void BluesolarHeliostatArmature(TrackerArmature2A& armature);
ElevationAngleKM CreateBluesolarElevationAngleKM();
HourAngleKM CreateBluesolarHourAngleKM();
