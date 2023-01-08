#ifndef AUXFUNCTION_H
#define AUXFUNCTION_H

#include <cfloat>
#include <cmath>

namespace hypl
{
    namespace auxfunction
    {
        double SolarDeclinationByDayNumber(int day_number);
        double DistanceSunEarth(int day_number);
        double ReceiverSubtendedAngle(double ratio_of_distances );

        template<class T>
        bool equals(T x, T y)
        {
            return std::abs(x - y) < std::numeric_limits<T>::epsilon();
        }
    }
}
#endif // AUXFUNCTION_H