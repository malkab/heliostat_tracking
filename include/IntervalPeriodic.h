#pragma once

#include "Interval.h"

class HELIOSTAT_TRACKING_EXPORT IntervalPeriodic: public Interval
{
public:
    IntervalPeriodic() : Interval() {}
    IntervalPeriodic(double a, double b): Interval(a, b) {}

    double normalizeAngle(double alpha) const;
};