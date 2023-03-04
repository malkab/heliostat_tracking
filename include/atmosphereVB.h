#ifndef ATMOSPHEREVB_H
#define ATMOSPHEREVB_H

#include "atmosphere.h"

namespace hypl
{
    class AtmosphereVB : public Atmosphere
    {
    public:
        AtmosphereVB() : Atmosphere() { }

        //Specific public functions
        virtual double Transmittance(double slant_range ) const 
            { return 0.99326 + slant_range * (-0.0001046 + (1.7000000000000003e-8 - 2.845e-12 * slant_range) * slant_range); }
    };
}
#endif // ATMOSPHEREVB_H