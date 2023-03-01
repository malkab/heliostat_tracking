#include "scenario.h"
#include "auxfunction.h"

hypl::Scenario::Scenario()
{
    update_scenario();
}

hypl::Scenario::Scenario( Location location, Atmosphere atmosphere, Boundaries boundaries, std::vector<Receiver> receivers) :
m_location {location},
m_atmosphere {atmosphere},
m_boundaries {boundaries},
m_receivers {receivers}
{
    update_scenario();
}

void hypl::Scenario::update_scenario()
{

    if( m_sun_subtended_angles.empty() == false ) m_declinations.clear();
    if( m_declinations.empty() == false ) m_declinations.clear();

    // ACTION - Modify to lines below take into account the actual days of the year we are using to estimate things 173 to 355??
    int ndays = 365;  
    m_sun_subtended_angles.reserve(ndays);
    m_declinations.reserve(ndays);
    for (int day_number=1; day_number<=ndays; day_number++)
    {
        m_sun_subtended_angles.emplace_back(auxfunction::ReceiverSubtendedAngle(mathconstants::sun_radius / auxfunction::DistanceSunEarth(day_number)));
        m_declinations.emplace_back(auxfunction::SolarDeclinationByDayNumber(day_number));
    }
}
