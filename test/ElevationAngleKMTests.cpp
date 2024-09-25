#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "gcf.h"
#include "ElevationAngleKM.h"

class ElevationAngleKMTest : public ::testing::Test {  
protected:
    void SetUp() override {
        double gamma = 1.499539835163685; // radians
        double rab = 0.38228347073744173; // meters
        double rbc = 0.0396; // meters
        double rad = 0.4146341554709371; // meters
        double alpha2 = 0.0848055; // meters

        m_pElevationAngleKM = new ElevationAngleKM(gamma, rab, rbc, rad, alpha2);
    }

    void TearDown() override {
        delete m_pElevationAngleKM;
    }

    ElevationAngleKM* m_pElevationAngleKM;
};

TEST_F(ElevationAngleKMTest, ConstructorInitialization) {
    EXPECT_EQ(m_pElevationAngleKM->get_gamma(), 1.499539835163685);
    EXPECT_EQ(m_pElevationAngleKM->get_rab(), 0.38228347073744173);
    EXPECT_EQ(m_pElevationAngleKM->get_rbc(),  0.0396);
    EXPECT_EQ(m_pElevationAngleKM->get_rad(), 0.4146341554709371);
    EXPECT_EQ(m_pElevationAngleKM->get_alpha2(), 0.0848055);
}

// Tests for setter functions
TEST_F(ElevationAngleKMTest, SetGamma) {
    double gamma = 1.499539835163685; // radians
    m_pElevationAngleKM->set_gamma(gamma);
    EXPECT_EQ(m_pElevationAngleKM->get_gamma(), gamma);
}

TEST_F(ElevationAngleKMTest, SetRab) {
    double rab = 0.56; // meters
    m_pElevationAngleKM->set_rab(rab);
    EXPECT_EQ(m_pElevationAngleKM->get_rab(), rab);
}

TEST_F(ElevationAngleKMTest, SetRbc) {
    double rbc = 0.08; // meters
    m_pElevationAngleKM->set_rbc(rbc);
    EXPECT_EQ(m_pElevationAngleKM->get_rbc(), rbc);
}

TEST_F(ElevationAngleKMTest, SetRad) {
    double rad = 0.630; // meters
    m_pElevationAngleKM->set_rad(rad);
    EXPECT_EQ(m_pElevationAngleKM->get_rad(), rad);
}

TEST_F(ElevationAngleKMTest, SetAlpha2) {
    double alpha2 = 0.08480554835440447; // meters
    m_pElevationAngleKM->set_alpha2(alpha2);
    EXPECT_EQ(m_pElevationAngleKM->get_alpha2(), alpha2);
}


// Tests for calculation functions
TEST_F(ElevationAngleKMTest, GetActuatorLengthFromElevationAngle) {
    double elevation_angle = 40.1 * gcf::degree; // radians
    double expected_actuator_length = m_pElevationAngleKM->getActuatorLengthFromElevationAngle(elevation_angle);
    EXPECT_NEAR(expected_actuator_length, 0.3734944549994152, 0.001);
}

TEST_F(ElevationAngleKMTest, GetElevationAngleFromActuatorLength) {
    double actuator_length = 0.3403445;
    double expected_elevation_angle = m_pElevationAngleKM->getElevationAngleFromActuatorLength(actuator_length);
    EXPECT_NEAR(expected_elevation_angle, 40.1 * gcf::degree, 0.001);
}
