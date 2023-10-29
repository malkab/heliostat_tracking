#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TrackerArmature2A.h"
#include "TrackerSolver2A.h"
#include "TrackerTarget.h"

class TrackerArmature2ATest : public ::testing::Test {  
 
protected:

    void SetUp() override {
        m_pArmature = new TrackerArmature2A();
    }

    void TearDown() override {
        delete m_pArmature;
    }

    TrackerArmature2A* m_pArmature;
};

TEST_F(TrackerArmature2ATest, DefaultConstructorPrimaryAxisInitialization) {
    EXPECT_EQ(m_pArmature->get_primaryAxis(), vec3d(0.f, 0.f, -1.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorPrimaryAnglesInitialization) {
    EXPECT_EQ(m_pArmature->get_primaryAngles(), vec2d(-90.f, 90.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorSecondaryShiftInitialization) {
    EXPECT_EQ(m_pArmature->get_secondaryShift(), vec3d(0.f, 0.f, 0.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorSecondaryAxisInitialization) {
    EXPECT_EQ(m_pArmature->get_secondaryAxis(), vec3d(1.f, 0.f, 0.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorSecondaryAnglesInitialization) {
    EXPECT_EQ(m_pArmature->get_secondaryAngles(), vec2d(-90.f, 90.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorFacetShiftInitialization) {
    EXPECT_EQ(m_pArmature->get_facetShift(), vec3d(0.f, 0.f, 0.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorFacetNormalInitialization) {
    EXPECT_EQ(m_pArmature->get_facetNormal(), vec3d(0.f, 0.f, 1.f));
}

TEST_F(TrackerArmature2ATest, DefaultConstructorAnglesDefaultInitialization) {
    EXPECT_EQ(m_pArmature->get_anglesDefault(), vec2d(0.f, 0.f));
}

// Tests for setters and the onModified() function
TEST_F(TrackerArmature2ATest, SetPrimaryShift) {
    vec3d newValue(1.f, 2.f, 3.f);
    m_pArmature->set_primaryShift(newValue);
    EXPECT_EQ(m_pArmature->get_primaryShift(), newValue);
}

TEST_F(TrackerArmature2ATest, SetPrimaryAxis) {
    vec3d newValue(0.f, 1.f, 0.f);
    m_pArmature->set_primaryAxis(newValue);
    EXPECT_EQ(m_pArmature->get_primaryAxis(), newValue);
}

TEST_F(TrackerArmature2ATest, SetPrimaryAngles) {
    vec2d newValue(45.f, 135.f);
    m_pArmature->set_primaryAngles(newValue);
    EXPECT_EQ(m_pArmature->get_primaryAngles(), newValue);
}

TEST_F(TrackerArmature2ATest, SetSecondaryShift) {
    vec3d newValue(1.f, 2.f, 3.f);
    m_pArmature->set_secondaryShift(newValue);
    EXPECT_EQ(m_pArmature->get_secondaryShift(), newValue);
}

TEST_F(TrackerArmature2ATest, SetSecondaryAxis) {
    vec3d newValue(0.f, 1.f, 0.f);
    m_pArmature->set_secondaryAxis(newValue);
    EXPECT_EQ(m_pArmature->get_secondaryAxis(), newValue);
}

TEST_F(TrackerArmature2ATest, SetSecondaryAngles) {
    vec2d newValue(45.f, 135.f);
    m_pArmature->set_secondaryAngles(newValue);
    EXPECT_EQ(m_pArmature->get_secondaryAngles(), newValue);
}

TEST_F(TrackerArmature2ATest, SetFacetShift) {
    vec3d newValue(1.f, 2.f, 3.f);
    m_pArmature->set_facetShift(newValue);
    EXPECT_EQ(m_pArmature->get_facetShift(), newValue);
}

TEST_F(TrackerArmature2ATest, SetFacetNormal) {
    vec3d newValue(0.f, 1.f, 0.f);
    m_pArmature->set_facetNormal(newValue);
    EXPECT_EQ(m_pArmature->get_facetNormal(), newValue);
}

TEST_F(TrackerArmature2ATest, SetAnglesDefault) {
    vec2d newValue(45.f, 135.f);
    m_pArmature->set_anglesDefault(newValue);
    EXPECT_EQ(m_pArmature->get_anglesDefault(), newValue);
}
