#ifndef HELIOSTATALLFACTORS_H
#define HELIOSTATALLFACTORS_H

#include "heliostat.h"


namespace hypl
{
    class HeliostatAllFactors : public Heliostat
    { 
    public:
        HeliostatAllFactors(Scenario& scenario, vec3d center) : Heliostat(scenario, center) {} 

        //Public functions
        virtual TrackingInfo Track(vec3d& sun_vector, double sun_subtended_angle) const;
    };
}
#endif // HELIOSTATALLFACTORS_H