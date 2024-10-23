// PythonWrapper.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "TrackerTarget.h"
#include "TrackerArmature2A.h"
#include "ElevationAngleKM.h"
#include "HourAngleKM.h"
#include "Transform.h"
#include "vec3d.h"
#include "vec2d.h"

namespace py = pybind11;

// Helper function to convert a Python list of lists to 16 double arguments
std::tuple<double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>
convertMatrix(const std::vector<std::vector<double>>& matrix) {
    if (matrix.size() != 4 || matrix[0].size() != 4 || matrix[1].size() != 4 || matrix[2].size() != 4 || matrix[3].size() != 4) {
        throw std::invalid_argument("Matrix must be 4x4.");
    }
    return std::make_tuple(
        matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
        matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
        matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
        matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]
    );
}

PYBIND11_MODULE(heliostat_tracking_module, m) {
    py::class_<vec3d>(m, "vec3d")
        .def(py::init<double, double, double>())
        .def_readwrite("x", &vec3d::x)
        .def_readwrite("y", &vec3d::y)
        .def_readwrite("z", &vec3d::z);

    py::class_<vec2d>(m, "vec2d")
        .def(py::init<double, double>())
        .def_readwrite("x", &vec2d::x)
        .def_readwrite("y", &vec2d::y);

    py::class_<Transform>(m, "Transform")
        .def(py::init<
            double, double, double, double,
            double, double, double, double,
            double, double, double, double,
            double, double, double, double>())
        .def(py::init([](const std::vector<std::vector<double>>& matrix) {
            auto args = convertMatrix(matrix);
            return new Transform(
                std::get<0>(args), std::get<1>(args), std::get<2>(args), std::get<3>(args),
                std::get<4>(args), std::get<5>(args), std::get<6>(args), std::get<7>(args),
                std::get<8>(args), std::get<9>(args), std::get<10>(args), std::get<11>(args),
                std::get<12>(args), std::get<13>(args), std::get<14>(args), std::get<15>(args)
            );
        }));

    py::class_<TrackerTarget>(m, "TrackerTarget")
        .def(py::init<>())
        .def_property("aiming_point", 
                      [](const TrackerTarget &t) { return t.aimingPoint; },
                      [](TrackerTarget &t, const vec3d &p) { t.aimingPoint = p; })
        .def_property("angles", 
                      [](const TrackerTarget &t) { return t.angles; },
                      [](TrackerTarget &t, const vec2d &a) { t.angles = a; });

    py::class_<TrackerArmature2A>(m, "TrackerArmature2A")
        .def(py::init<>())
        .def("update", &TrackerArmature2A::update)
        .def("set_primary_shift", &TrackerArmature2A::set_primaryShift)
        .def("set_primary_axis", &TrackerArmature2A::set_primaryAxis)
        .def("set_primary_angles", &TrackerArmature2A::set_primaryAngles)
        .def("set_secondary_shift", &TrackerArmature2A::set_secondaryShift)
        .def("set_secondary_axis", &TrackerArmature2A::set_secondaryAxis)
        .def("set_secondary_angles", &TrackerArmature2A::set_secondaryAngles)
        .def("set_facet_shift", &TrackerArmature2A::set_facetShift)
        .def("set_facet_normal", &TrackerArmature2A::set_facetNormal)
        .def("set_default_angles", &TrackerArmature2A::set_anglesDefault);

    py::class_<ElevationAngleKM>(m, "ElevationAngleKM")
        .def(py::init<double, double, double, double, double>())
        .def("get_actuator_length_from_elevation_angle", &ElevationAngleKM::getActuatorLengthFromElevationAngle)
        .def("get_elevation_angle_from_actuator_length", &ElevationAngleKM::getElevationAngleFromActuatorLength);

    py::class_<HourAngleKM>(m, "HourAngleKM")
        .def(py::init<double, double, double, double>())
        .def("get_actuator_length_from_hour_angle", &HourAngleKM::getActuatorLengthFromHourAngle)
        .def("get_hour_angle_from_actuator_length", &HourAngleKM::getHourAngleFromActuatorLength);
}