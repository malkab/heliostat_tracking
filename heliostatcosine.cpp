#include <math.h>

#include "heliostatcosine.h"
#include "auxfunction.h"

hypl::Heliostat::TrackingInfo hypl::HeliostatCosine::Track(vec3d& sun_vector,  double sun_subtended_angle) const
{
    TrackingInfo tracking_info = { -1.0, -1 };

    double ideal_efficiency;
 
    for (int receiver_id = 0; receiver_id < m_scenario.receivers().size(); receiver_id++)
    {
        ideal_efficiency = sqrt( 0.5 + 0.5 * dot(sun_vector, m_reflected_unit_vector[receiver_id]) );

        if (ideal_efficiency > tracking_info.ideal_efficiency)
        {
            tracking_info.ideal_efficiency = ideal_efficiency;
            tracking_info.aiming_at_receiver_id = receiver_id;
        }
    }            
    return tracking_info;
}