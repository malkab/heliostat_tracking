#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "gcf.h"
#include "ElevationAngleKM.h"

class ElevationAngleKMTest : public ::testing::Test {  
protected:
    void SetUp() override {
        double gamma = 90.75 * gcf::degree; // radians
        double rab = 0.39254; // meters
        double rbc = 0.0465; // meters
        double rad = 0.43061; // meters
        double ra = 0.082; // meters
        double rd = 0.045; // meters

        m_pElevationAngleKM = new ElevationAngleKM(gamma, rab, rbc, rad, ra, rd);
    }

    void TearDown() override {
        delete m_pElevationAngleKM;
    }

    ElevationAngleKM* m_pElevationAngleKM;
};

TEST_F(ElevationAngleKMTest, ConstructorInitialization) {
    EXPECT_EQ(m_pElevationAngleKM->get_gamma(), 90.75 * gcf::degree);
    EXPECT_EQ(m_pElevationAngleKM->get_rab(), 0.39254);
    EXPECT_EQ(m_pElevationAngleKM->get_rbc(),  0.0465);
    EXPECT_EQ(m_pElevationAngleKM->get_rad(), 0.43061);
    EXPECT_EQ(m_pElevationAngleKM->get_ra(), 0.082);
    EXPECT_EQ(m_pElevationAngleKM->get_rd(), 0.045);
}

// Tests for setter functions
TEST_F(ElevationAngleKMTest, SetGamma) {
    double gamma = 82.0 * gcf::degree; // radians
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

TEST_F(ElevationAngleKMTest, SetRa) {
    double ra = 0.51; // meters
    m_pElevationAngleKM->set_ra(ra);
    EXPECT_EQ(m_pElevationAngleKM->get_ra(), ra);
}

TEST_F(ElevationAngleKMTest, SetRd) {
    double rd = 0.038; // meters
    m_pElevationAngleKM->set_rd(rd);
    EXPECT_EQ(m_pElevationAngleKM->get_rd(), rd);
}

// Tests for calculation functions
TEST_F(ElevationAngleKMTest, GetActuatorLengthFromElevationAngle) {
    double elevation_angle = 40.0 * gcf::degree; // radians
    double expected_actuator_length = m_pElevationAngleKM->getActuatorLengthFromElevationAngle(elevation_angle);
    EXPECT_NEAR(expected_actuator_length, 0.3734944549994152, 0.001);
}

TEST_F(ElevationAngleKMTest, GetElevationAngleFromActuatorLength) {
    double actuator_length = 0.3734944549994152;
    double expected_elevation_angle = m_pElevationAngleKM->getElevationAngleFromActuatorLength(actuator_length);
    EXPECT_NEAR(expected_elevation_angle, 40.0 * gcf::degree, 0.001);
}
