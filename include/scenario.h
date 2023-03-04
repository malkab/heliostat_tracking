#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>

#include "location.h"
#include "atmosphere.h"
#include "boundaries.h"
#include "receiver.h"

namespace hypl
{
    class Scenario
    {
    public:

        Scenario();
        Scenario(Location location, Atmosphere* atmosphere, Boundaries boundaries, std::vector<Receiver> receivers);


        //Accessors
        Location const& location() const { return m_location; }
        Atmosphere* const& atmosphere() const { return m_atmosphere; }
        Boundaries  const& boundaries() const { return m_boundaries; }
        std::vector<Receiver> const& receivers() const { return m_receivers; }
        std::vector<double> const& sun_subtended_angles() const { return m_sun_subtended_angles; }
        std::vector<double> const& declinations() const { return m_declinations; }

        //Mutators
        void set_location(Location location) { m_location = location; }
        void set_atmosphere(Atmosphere* atmosphere) { m_atmosphere = atmosphere; }
        void set_boundaries(Boundaries boundaries) { m_boundaries = boundaries; }
        void set_receivers(std::vector<Receiver> receivers) { m_receivers = receivers;}
        void update_scenario();

    private:
        //Private variables
        Location m_location;
        Atmosphere* m_atmosphere;
        Boundaries m_boundaries;
        std::vector<Receiver> m_receivers;
        std::vector<double> m_sun_subtended_angles;
        std::vector<double> m_declinations;
    };
}

#endif // ENVIRONMENT_H