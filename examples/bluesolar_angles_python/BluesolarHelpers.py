import sys

# Ensure Python can find the compiled module
sys.path.append('C:/Users/manue_6t240gh/Dropbox/OpenSource/heliostat_tracking/build/Release')

import heliostat_tracking_module as ht
from math import radians

def convert_and_validate_arguments(args):
    if len(args) != 9:
        print("Usage: python script.py xHeliostat yHeliostat zHeliostat xAimingPoint yAimingPoint zAimingPoint sunAzimuth sunElevation")
        return False

    try:
        xHeliostat = float(args[1])
        yHeliostat = float(args[2])
        zHeliostat = float(args[3])
        xAimingPoint = float(args[4])
        yAimingPoint = float(args[5])
        zAimingPoint = float(args[6])
        sunAzimuth = float(args[7])
        sunElevation = float(args[8])
    except ValueError as e:
        print(f"Invalid argument: {e}")
        return False

    return xHeliostat, yHeliostat, zHeliostat, xAimingPoint, yAimingPoint, zAimingPoint, sunAzimuth, sunElevation

def bluesolar_heliostat_armature(armature_id):
    ht.set_primary_shift(armature_id, 0.0, 0.0, 2.415)
    ht.set_primary_axis(armature_id, -1.0, 0.0, 0.0)
    ht.set_primary_angles(armature_id, 0.0, 90.0)

    ht.set_secondary_shift(armature_id, 0.0, -0.0816, 0.0)
    ht.set_secondary_axis(armature_id, 0.0, 0.0, -1.0)
    ht.set_secondary_angles(armature_id, -70.0, 55.0)

    ht.set_facet_shift(armature_id, 0.0, -0.105, 0.035)
    ht.set_facet_normal(armature_id, 0.0, -1.0, 0.0)

    ht.set_angles_default(armature_id, 0.0, 0.0)

def create_bluesolar_elevation_angle_km():
    gamma = 1.5566945190927768  # Convert to radians
    rab = 0.3679941188052566
    rbc = 0.08587871211683747
    rad = 0.45469491923653677
    alpha2 = 0.08155204289894769
    offset = 0.04037
    return ht.ElevationAngleKM(gamma, rab, rbc, rad, alpha2, offset)

def create_bluesolar_hour_angle_km():
    gamma = 0.543717625543648  # Convert to radians
    rab = 0.3716059721933388
    rbc = 0.05209218963038278
    rad = 0.3390154085801952
    offset = 0.04037    
    return ht.HourAngleKM(gamma, rab, rbc, rad, offset)
