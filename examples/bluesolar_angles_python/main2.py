# main2.py
import sys
import os
from math import cos, sin, radians

# Ensure Python can find the compiled module
sys.path.append('C:/Users/manue_6t240gh/Dropbox/OpenSource/heliostat_tracking/build/Release')

import numpy as np
import heliostat_tracking_module as ht
from BluesolarHelpers import create_bluesolar_elevation_angle_km, create_bluesolar_hour_angle_km

def main():
    if len(sys.argv) != 9:
        print("Usage: main2.py xHeliostat yHeliostat zHeliostat xAimingPoint yAimingPoint zAimingPoint sunAzimuth sunElevation")
        return

    xHeliostat, yHeliostat, zHeliostat = map(float, sys.argv[1:4])
    xAimingPoint, yAimingPoint, zAimingPoint = map(float, sys.argv[4:7])
    sunAzimuth, sunElevation = map(float, sys.argv[7:9])

    # Create TrackerTarget instance
    target = ht.TrackerTarget()
    target.aiming_point = ht.vec3d(xAimingPoint, yAimingPoint, zAimingPoint)

    # Create and configure TrackerArmature2A instance
    armature = ht.TrackerArmature2A()
    armature.set_primary_shift(ht.vec3d(0.0, 0.0, 2.415))
    armature.set_primary_axis(ht.vec3d(-1.0, 0.0, 0.0))
    armature.set_primary_angles(ht.vec2d(0.0, 90.0))
    armature.set_secondary_shift(ht.vec3d(0.0, -0.0816, 0.0))
    armature.set_secondary_axis(ht.vec3d(0.0, 0.0, -1.0))
    armature.set_secondary_angles(ht.vec2d(-70.0, 55.0))
    armature.set_facet_shift(ht.vec3d(0.0, -0.105, 0.035))
    armature.set_facet_normal(ht.vec3d(0.0, -1.0, 0.0))
    armature.set_default_angles(ht.vec2d(0.0, 0.0))

    # Define the heliostat location transform
    heliostat_location = ht.Transform([
        [1.0, 0.0, 0.0, xHeliostat],
        [0.0, 1.0, 0.0, yHeliostat],
        [0.0, 0.0, 1.0, zHeliostat],
        [0.0, 0.0, 0.0, 1.0]
    ])

    # Define the sun vector from sun angles
    sun_azimuth = radians(sunAzimuth)  # Convert to radians
    sun_elevation = radians(sunElevation)  # Convert to radians
    sun_vector = ht.vec3d(cos(sun_elevation) * sin(sun_azimuth), cos(sun_elevation) * cos(sun_azimuth), sin(sun_elevation))

    # Update the armature to compute the angles
    armature.update(heliostat_location, sun_vector, target)

    # Get the resulting angles
    elevation_angle = target.angles.x
    hour_angle = target.angles.y

    # Initialize kinematic models using BlueSolarHelpers
    elevation_angle_km = create_bluesolar_elevation_angle_km()
    hour_angle_km = create_bluesolar_hour_angle_km()

    # Compute actuator lengths
    length_elevation_angle_actuator = elevation_angle_km.get_actuator_length_from_elevation_angle(radians(elevation_angle))
    length_hour_angle_actuator = hour_angle_km.get_actuator_length_from_hour_angle(radians(hour_angle))

    # Print the results
    print(f"Angles: ({target.angles.x}, {target.angles.y}), Elevation Actuator Length: {length_elevation_angle_actuator}, Hour Actuator Length: {length_hour_angle_actuator}")

if __name__ == "__main__":
    main()