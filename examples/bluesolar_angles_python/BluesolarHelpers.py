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
    gamma = radians(90.75)  # Convert to radians
    rab = 0.39254
    rbc = 0.0465
    rad = 0.43061
    ra = 0.082
    rd = 0.045
    return ht.ElevationAngleKM(gamma, rab, rbc, rad, ra, rd)

def create_bluesolar_hour_angle_km():
    gamma = radians(22.0)  # Convert to radians
    rab = 0.35033
    rbc = 0.0465
    rad = 0.36527
    return ht.HourAngleKM(gamma, rab, rbc, rad)
