#include <math.h>

#include "heliostatcosinetransmittance.h"
#include "auxfunction.h"

hypl::Heliostat::TrackingInfo hypl::HeliostatCosineAndTransmittance::Track(vec3d& sun_vector,  double sun_subtended_angle) const
{
    TrackingInfo tracking_info = { -1.0, -1 };

    double cosine;
    double ideal_efficiency;
 
    for (int receiver_id = 0; receiver_id < m_scenario.receivers().size(); receiver_id++)
    {            
        cosine = sqrt( 0.5 + 0.5 * dot(sun_vector, m_reflected_unit_vector[receiver_id]) );
        ideal_efficiency = cosine * m_transmittance[receiver_id];

        if (ideal_efficiency > tracking_info.ideal_efficiency)
        {
            tracking_info.ideal_efficiency = ideal_efficiency;
            tracking_info.aiming_at_receiver_id = receiver_id;
        }
    }           
    return tracking_info;
}