#include "gtest/gtest.h"
#include "pybind11/embed.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "gcf.h"
#include "vec3d.h"
#include "vec2d.h"

namespace py = pybind11;
using namespace py::literals;

// Test fixture for embedding the Python interpreter in tests
class PythonWrapperTest : public ::testing::Test {
protected:
    py::scoped_interpreter guard{}; // Start the interpreter and keep it alive
    py::module heliostat_tracking_module;

    void SetUp() override {
        py::module sys = py::module::import("sys");
        sys.attr("path").attr("append")("${CMAKE_CURRENT_BINARY_DIR}");
        heliostat_tracking_module = py::module::import("heliostat_tracking_module");
    }

};

// Helper functions
py::tuple vec3d_to_tuple(const vec3d& v) {
    return py::make_tuple(v.x, v.y, v.z);
}

vec3d tuple_to_vec3d(const py::tuple& t) {
    if (t.size() != 3)
        throw std::runtime_error("Expected a tuple of size 3.");
    return vec3d(t[0].cast<double>(), t[1].cast<double>(), t[2].cast<double>());
}

// Test the creation and basic operations of vec3d
TEST_F(PythonWrapperTest, Vec3dCreationAndOperations) {
    auto vec3d_class = heliostat_tracking_module.attr("vec3d");
    auto v = vec3d_class(1.0, 2.0, 3.0);
    
    EXPECT_EQ(v.attr("x").cast<double>(), 1.0);
    EXPECT_EQ(v.attr("y").cast<double>(), 2.0);
    EXPECT_EQ(v.attr("z").cast<double>(), 3.0);

    v.attr("x") = 4.0;
    v.attr("y") = 5.0;
    v.attr("z") = 6.0;

    EXPECT_EQ(v.attr("x").cast<double>(), 4.0);
    EXPECT_EQ(v.attr("y").cast<double>(), 5.0);
    EXPECT_EQ(v.attr("z").cast<double>(), 6.0);
}

// Test the creation and basic operations of vec2d
TEST_F(PythonWrapperTest, Vec2dCreationAndOperations) {
    auto vec2d_class = heliostat_tracking_module.attr("vec2d");
    auto v = vec2d_class(1.0, 2.0);

    EXPECT_EQ(v.attr("x").cast<double>(), 1.0);
    EXPECT_EQ(v.attr("y").cast<double>(), 2.0);

    v.attr("x") = 3.0;
    v.attr("y") = 4.0;

    EXPECT_EQ(v.attr("x").cast<double>(), 3.0);
    EXPECT_EQ(v.attr("y").cast<double>(), 4.0);
}

// Test TrackerTarget and its properties
TEST_F(PythonWrapperTest, TrackerTargetTest) {
    auto vec3d_class = heliostat_tracking_module.attr("vec3d");
    auto vec2d_class = heliostat_tracking_module.attr("vec2d");
    auto target_class = heliostat_tracking_module.attr("TrackerTarget");

    auto target = target_class();
    auto aiming_point = vec3d_class(1.0, 2.0, 3.0);
    auto angles = vec2d_class(45.0, 30.0);

    target.attr("aiming_point") = aiming_point;
    target.attr("angles") = angles;

    EXPECT_EQ(target.attr("aiming_point").attr("x").cast<double>(), 1.0);
    EXPECT_EQ(target.attr("aiming_point").attr("y").cast<double>(), 2.0);
    EXPECT_EQ(target.attr("aiming_point").attr("z").cast<double>(), 3.0);

    EXPECT_EQ(target.attr("angles").attr("x").cast<double>(), 45.0);
    EXPECT_EQ(target.attr("angles").attr("y").cast<double>(), 30.0);
}

// Test TrackerArmature2A and its methods
TEST_F(PythonWrapperTest, TrackerArmature2ATest) {
    auto vec3d_class = heliostat_tracking_module.attr("vec3d");
    auto vec2d_class = heliostat_tracking_module.attr("vec2d");
    auto transform_class = heliostat_tracking_module.attr("Transform");
    auto armature_class = heliostat_tracking_module.attr("TrackerArmature2A");
    auto target_class = heliostat_tracking_module.attr("TrackerTarget");

    auto armature = armature_class();
    auto target = target_class();

    double xHeliostat = 0.0;
    double yHeliostat = 100.0;
    double zHeliostat = 0.0;

    auto heliostat_location = transform_class(
        1.0, 0.0, 0.0, xHeliostat,
        0.0, 1.0, 0.0, yHeliostat,
        0.0, 0.0, 1.0, zHeliostat,
        0.0, 0.0, 0.0, 1.0
    );

    //Define the sun vector from sun angles
    double sun_azimuth = 180.0 * gcf::degree;
    double sun_elevation = 70.0 * gcf::degree;
    vec3d sun_vector = vec3d(cos(sun_elevation) * sin(sun_azimuth), cos(sun_elevation) * cos(sun_azimuth), sin(sun_elevation));

    target.attr("aiming_point") = vec3d_class(0.0, 0.0, 20.0);

    armature.attr("set_primary_shift")(vec3d_class(0.0, 0.0, 2.415));
    armature.attr("set_primary_axis")(vec3d_class(-1.0, 0.0, 0.0));
    armature.attr("set_primary_angles")(vec2d_class(0.0, 90.0));
    armature.attr("set_secondary_shift")(vec3d_class(0.0, -0.0816, 0.0));
    armature.attr("set_secondary_axis")(vec3d_class(0.0, 0.0, -1.0));
    armature.attr("set_secondary_angles")(vec2d_class(-70.0, 55.0));
    armature.attr("set_facet_shift")(vec3d_class(0.0, -0.105, 0.035));
    armature.attr("set_facet_normal")(vec3d_class(0.0, -1.0, 0.0));
    armature.attr("set_default_angles")(vec2d_class(0.0, 0.0));

    armature.attr("update")(heliostat_location, sun_vector, target);

    auto angles = target.attr("angles");

    EXPECT_NEAR(angles.attr("x").cast<double>(), 39.95181117155712, 0.01);
    EXPECT_NEAR(angles.attr("y").cast<double>(), 0.0, 0.01);
}

// Test ElevationAngleKM
TEST_F(PythonWrapperTest, ElevationAngleKMTest) {
    auto elevation_angle_km_class = heliostat_tracking_module.attr("ElevationAngleKM");
    double gamma = 90.75 * gcf::degree;
    double rab = 0.39254;
    double rbc = 0.0465;
    double rad = 0.43061;
    double ra = 0.082;
    double rd = 0.045;
    auto elevation_angle_km = elevation_angle_km_class(gamma, rab, rbc, rad, ra, rd);

    auto length = elevation_angle_km.attr("get_actuator_length_from_elevation_angle")(39.95181117155712 * gcf::degree);
    EXPECT_NEAR(length.cast<double>(),  0.3738030587687042, 0.0001);
}

// Test HourAngleKM
TEST_F(PythonWrapperTest, HourAngleKMTest) {
    auto hour_angle_km_class = heliostat_tracking_module.attr("HourAngleKM");
    double gamma = 22.0 * gcf::degree;
    double rab = 0.35033;
    double rbc = 0.0465;
    double rad = 0.36527;  
    auto hour_angle_km = hour_angle_km_class(gamma, rab, rbc, rad);

    auto length = hour_angle_km.attr("get_actuator_length_from_hour_angle")(-1.3854021315850383e-15 * gcf::degree);
    EXPECT_NEAR(length.cast<double>(), 0.3976404620418174, 0.0001);
}


