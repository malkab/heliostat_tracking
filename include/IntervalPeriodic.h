#pragma once

#include "Interval.h"

class IntervalPeriodic: public Interval
{
public:
    IntervalPeriodic(double a, double b):
        Interval(a, b) {}

    double normalizeAngle(double alpha) const;
};