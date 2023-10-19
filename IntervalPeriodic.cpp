#include "IntervalPeriodic.h"

#include "gcf.h"

double IntervalPeriodic::normalizeAngle(double alpha) const
{
    return gcf::normalizeAngle(alpha, m_a);
}
