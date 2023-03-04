#ifndef ATMOSPHERELH_H
#define ATMOSPHERELH_H

#include "atmosphere.h"

namespace hypl
{
    class AtmosphereLH : public Atmosphere
    {
    public:
        AtmosphereLH() : Atmosphere() { }
        AtmosphereLH(double io, double beta) : Atmosphere(io, beta) { }

        //Specific public functions
        virtual double Transmittance(double slant_range ) const 
            {
                if(slant_range <= 1000.0) return 0.99321 + (-0.0001176 + 1.9699999999999998e-8 * slant_range) * slant_range;
                else return exp(-0.0001106 * slant_range);               
            }
    };
}
#endif // ATMOSPHERELH_H