#ifndef HELIOSTATCOSINETRANSMITTANCE_H
#define HELIOSTATCOSINETRANSMITTANCE_H

#include "heliostat.h"


namespace hypl
{
    class HeliostatCosineAndTransmittance : public Heliostat
    { 
    public:
        HeliostatCosineAndTransmittance(Scenario& scenario, vec3d center) : Heliostat(scenario, center) {} 

        //Public functions
        virtual TrackingInfo Track(vec3d& sun_vector, double sun_subtended_angle) const;
    };
}
#endif // HELIOSTATCOSINETRANSMITTANCE_H