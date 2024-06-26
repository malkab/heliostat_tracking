#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "gcf.h"
#include "HourAngleKM.h"

class HourAngleKMTests : public ::testing::Test {  
protected:
    void SetUp() override {
        double gamma = 22.0 * gcf::degree; // radians
        double rab = 0.35033; // meters
        double rbc = 0.0465; // meters
        double rad = 0.36527; // meters

        m_pHourAngleKM = new HourAngleKM(gamma, rab, rbc, rad);
    }

    void TearDown() override {
        delete m_pHourAngleKM;
    }

    HourAngleKM* m_pHourAngleKM;
};

TEST_F(HourAngleKMTests, ConstructorInitialization) {
    EXPECT_EQ(m_pHourAngleKM->get_gamma(), 22.0 * gcf::degree);
    EXPECT_EQ(m_pHourAngleKM->get_rab(), 0.35033);
    EXPECT_EQ(m_pHourAngleKM->get_rbc(),  0.0465);
    EXPECT_EQ(m_pHourAngleKM->get_rad(), 0.36527);
}

// Tests for setter functions
TEST_F(HourAngleKMTests, SetGamma) {
    double gamma = 30.0 * gcf::degree; // radians
    m_pHourAngleKM->set_gamma(gamma);
    EXPECT_EQ(m_pHourAngleKM->get_gamma(), gamma);
}

TEST_F(HourAngleKMTests, SetRab) {
    double rab = 0.56; // meters
    m_pHourAngleKM->set_rab(rab);
    EXPECT_EQ(m_pHourAngleKM->get_rab(), rab);
}

TEST_F(HourAngleKMTests, SetRbc) {
    double rbc = 0.08; // meters
    m_pHourAngleKM->set_rbc(rbc);
    EXPECT_EQ(m_pHourAngleKM->get_rbc(), rbc);
}

TEST_F(HourAngleKMTests, SetRad) {
    double rad = 0.630; // meters
    m_pHourAngleKM->set_rad(rad);
    EXPECT_EQ(m_pHourAngleKM->get_rad(), rad);
}

// Tests for calculation functions
TEST_F(HourAngleKMTests, GetActuatorLengthFromHourAngle) {
    double hour_angle = 0.0 * gcf::degree; // radians
    double expected_actuator_length = m_pHourAngleKM->getActuatorLengthFromHourAngle(hour_angle);
    EXPECT_NEAR(expected_actuator_length, 0.3976404620418174, 0.001);
}

TEST_F(HourAngleKMTests, GetHourAngleFromActuatorLength) {
    double actuator_length = 0.3976404620418174;
    double expected_hour_angle = m_pHourAngleKM->getHourAngleFromActuatorLength(actuator_length);
    EXPECT_NEAR(expected_hour_angle, 0.0 * gcf::degree, 0.001);
}
