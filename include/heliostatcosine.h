#ifndef HELIOSTATCOSINE_H
#define HELIOSTATCOSINE_H

#include "heliostat.h"


namespace hypl
{
    class HeliostatCosine : public Heliostat
    { 
    public:
        HeliostatCosine(Scenario& scenario, vec3d center) : Heliostat(scenario, center) {} 

        //Public functions
        virtual TrackingInfo Track(vec3d& sun_vector, double sun_subtended_angle) const;
    };
}
#endif // HELIOSTATCOSINE_H