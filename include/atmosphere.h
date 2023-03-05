#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

namespace hypl
{
    class Atmosphere
    {
    public:
        Atmosphere() : m_io {1110.0}, m_beta {0.11} { }
        Atmosphere(double io, double beta) : m_io {io}, m_beta {beta} { }

        //Accessors
        double const& io() const { return m_io; }
        double const& beta() const {return m_beta; }

        //Mutators
        void set_io(double io) { m_io = io; }
        void set_beta( double beta) { m_beta = beta; }

        //Specific public functions
        virtual double Transmittance(double slant_range) const = 0; // Pure virtual function
        double DniFromSz(double sz) const
            {
                if(sz>0.00001) return m_io * exp(-m_beta/sz);
                else return 0.0;
            }

    protected:
        double m_io;
        double m_beta;
    };
}
#endif // ATMOSPHERE_H