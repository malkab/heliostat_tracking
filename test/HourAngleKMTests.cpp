#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "gcf.h"
#include "HourAngleKM.h"

class HourAngleKMTests : public ::testing::Test {  
protected:
    void SetUp() override {
        double gamma = 0.543717625543648; // radians
        double rab = 0.3716059721933388; // meters
        double rbc = 0.05209218963038278; // meters    
        double rad = 0.3390154085801952; // meters    
        double offset = 0.04037; // meters

        m_pHourAngleKM = new HourAngleKM(gamma, rab, rbc, rad, offset);
    }

    void TearDown() override {
        delete m_pHourAngleKM;
    }

    HourAngleKM* m_pHourAngleKM;
};

TEST_F(HourAngleKMTests, ConstructorInitialization) {
    EXPECT_EQ(m_pHourAngleKM->get_gamma(), 0.543717625543648);
    EXPECT_EQ(m_pHourAngleKM->get_rab(), 0.3716059721933388);
    EXPECT_EQ(m_pHourAngleKM->get_rbc(),  0.05209218963038278);
    EXPECT_EQ(m_pHourAngleKM->get_rad(), 0.3390154085801952);
    EXPECT_EQ(m_pHourAngleKM->get_offset(), 0.04037);
}

// Tests for calculation functions
TEST_F(HourAngleKMTests, GetActuatorLengthFromHourAngle) {
    double hour_angle = 30.2 * gcf::degree; // radians
    double expected_actuator_length = m_pHourAngleKM->getActuatorLengthFromHourAngle(hour_angle);
    EXPECT_NEAR(expected_actuator_length, 0.455544478465155, 0.001);
}

TEST_F(HourAngleKMTests, GetHourAngleFromActuatorLength) {
    double actuator_length = 0.455544478465155;
    double expected_hour_angle = m_pHourAngleKM->getHourAngleFromActuatorLength(actuator_length);
    EXPECT_NEAR(expected_hour_angle, 30.2 * gcf::degree, 0.001);
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
