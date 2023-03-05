#ifndef PROCESSHELISTATFUNCTOR_H
#define PROCESSHELISTATFUNCTOR_H

#include "heliostat.h"

namespace hypl
{
    class ProcessHeliostatFunctor
    {
    public:
        ProcessHeliostatFunctor(vec3d& sun_vector, double sun_subtended_angle, double dni);
        void operator()(Heliostat* heliostat) const;

    private:
        vec3d& m_sun_vector;
        double m_sun_subtended_angle;
        double m_dni;
    };
}
#endif // PROCESSHELISTATFUNCTOR_H