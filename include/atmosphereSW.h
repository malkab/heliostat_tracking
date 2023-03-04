#ifndef ATMOSPHERESW_H
#define ATMOSPHERESW_H

#include "atmosphere.h"

namespace hypl
{
    class AtmosphereSW : public Atmosphere
    {
    public:
        AtmosphereSW() : Atmosphere() { }
        AtmosphereSW(double io, double beta) : AtmosphereSW(io, beta) { }

        //Specific public functions
        virtual double Transmittance(double slant_range ) const 
            { return exp(-(0.000010696 + 0.0009196 * m_beta) * slant_range); }
}
#endif // ATMOSPHERESW_H