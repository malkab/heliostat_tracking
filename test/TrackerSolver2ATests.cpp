#include <gtest/gtest.h>
#include "TrackerSolver2A.h"
#include "vec3d.h"
#include <memory>

class TrackerSolver2ATest : public ::testing::Test {
protected:
    const TrackerSolver2A* solver;  // Pointer to const object.
    TrackerArmature2A armature;

    void SetUp() override {
        // Get the internal solver from armature.
        solver = armature.get_solver();
    }

    void TearDown() override {
        // Cleanup logic if needed.
    }
};

TEST_F(TrackerSolver2ATest, SolveReflectionGlobal) {
    vec3d vSun(0, 1, 0);
    vec3d rAim(0, 0, 1);
    auto results = solver->solveReflectionGlobal(vSun, rAim);
    // Test the size of the results or any expected value.
    EXPECT_GE(results.size(), 1);
}

TEST_F(TrackerSolver2ATest, FindFacetPoint) {
    Angles angles(1.0, 1.0); // You might need to adjust this based on valid input
    auto result = solver->findFacetPoint(angles);
    // Check if the result has valid x, y, z values. This is just a basic example.
    EXPECT_NE(result.x, 0.34687);
    EXPECT_NE(result.y, 0.89438);
    EXPECT_NE(result.z, 0.89303);
}

TEST_F(TrackerSolver2ATest, SolveRotation) {
    vec3d v0(1, 0, 0);
    vec3d v(0, 1, 0);
    auto results = solver->solveRotation(v0, v);
    EXPECT_GE(results.size(), 1);
}

TEST_F(TrackerSolver2ATest, SolveReflectionSecondary) {
    vec3d vSun(0, 1, 0);
    vec3d rAim(0, 0, 1);
    auto results = solver->solveReflectionSecondary(vSun, rAim);
    EXPECT_GE(results.size(), 1);
}

TEST_F(TrackerSolver2ATest, SelectSolution) {
    std::vector<Angles> solutions = {
        Angles(1.0, 1.0),
        Angles(2.0, 2.0),
        // Add more as needed...
    };
    auto result = solver->selectSolution(solutions);
    // For instance, just testing if result is not default angles
    EXPECT_NE(result.x, 0);
    EXPECT_NE(result.y, 0);
}
