#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <utility>
#include <vector>
#include <chrono>
#include <numeric>
#include <functional>
#include <algorithm>
#include <execution>

#include "location.h"
#include "atmosphere.h"
#include "receiver.h"
#include "vec3d.h"
#include "boundaries.h"
#include "heliostat.h"
#include "idealefficiencymap.h"
#include "auxfunction.h"

void TwoReceiversAnalysis();
void WriteResults(std::string filename, hypl::Heliostat::IdealEfficiencyType ideal_efficiency_type, 
                  hypl::IdealEfficiencyMap& ideal_efficiency_map, std::vector< std::pair<double, double> > & average_field_efficiency);

int main(int argc, char *argv[])
{
    TwoReceiversAnalysis();

    std::cout << "DONE" <<std::endl;

    return 1;
}

//----------------------------------------------------------
void TwoReceiversAnalysis()
{
    // Scenario
    double latitude_degree = 30.0; // Degrees North
    double tower_height = 50.0; // Meters
    double receiver_radius = 5.0; // Meters 
    double maximum_heliostat_field_area = 2500000.0; // Square meters
    double characteristic_length = sqrt(maximum_heliostat_field_area);
    
    // Environment
    hypl::Location location(latitude_degree * hypl::mathconstants::degree);
    hypl::Atmosphere atmosphere; // Using default attenuation model
    hypl::Environment environment(location, atmosphere);

    // Boundaries
    double xmin = -(3.0 * characteristic_length);
    double xmax = -xmin;
    double ymin = xmin;
    double ymax = -ymin;
    hypl::Boundaries boundaries(xmin,xmax,ymin,ymax);

    std::cout << std::endl << "Boundaries: " << "( (" << xmin << ", " << xmax << "), (" << ymin << ", " << ymax << ") )" << std::endl;

    // Grid
    int nrows = 1000;
    int ncolumns = 1000;

    // Analysis parameters       
    double delta_t = 225.;
    hypl::Heliostat::IdealEfficiencyType ideal_efficiency_type = hypl::Heliostat::IdealEfficiencyType::CosineAndTransmittance;

    auto start = std::chrono::high_resolution_clock::now();

    // Compute heliosta reflective area and number of heliostats in the field
    double heliostat_area = ((xmax-xmin) * (ymax-ymin))/(nrows * ncolumns);
    int total_number_of_heliostats = nrows * ncolumns;
    int maximum_number_of_valid_heliostats = maximum_heliostat_field_area / heliostat_area;

    for( double factor = 0.1; factor < 3.0; factor += 0.01  )
    {
        // Modify distance between receivers
        double distance_between_receivers =  factor * characteristic_length;
        std::vector<hypl::Receiver> receivers;
        receivers.push_back(hypl::Receiver(hypl::vec3d(-distance_between_receivers/2.0, 0.0, tower_height), receiver_radius));
        receivers.push_back(hypl::Receiver(hypl::vec3d( distance_between_receivers/2.0, 0.0, tower_height), receiver_radius));   

        // Compute annual optical efficiencies of ideal heliostats
        hypl::IdealEfficiencyMap ideal_efficiency_map(environment, boundaries, receivers, nrows, ncolumns); 
        ideal_efficiency_map.EvaluateAnnualEfficiencies(ideal_efficiency_type, delta_t);

        // Copy annual heliostats' annual ideal efficiencies (aie) to a vector of doubles
        std::vector<hypl::Heliostat> const& heliostats = ideal_efficiency_map.heliostats();
        std::vector<double> haie;
        for (auto& element : heliostats) haie.push_back(element.m_annual_ideal_efficiency);

        // Sort the annual efficiency vector from greater to lower
        std::sort(haie.begin(), haie.end(), std::greater<double>());

        // Compute the average annual efficiency as a function of the heliostat field's area
        std::vector< std::pair<double, double> >  average_field_efficiency;
        for (int number_of_heliostats = 1; number_of_heliostats <= maximum_number_of_valid_heliostats; number_of_heliostats++)
        {
            std::pair<double, double> value_point;
            value_point.first = number_of_heliostats * heliostat_area;
            value_point.second = std::accumulate(haie.begin(), std::next(haie.begin(), number_of_heliostats), 0.0)/number_of_heliostats;
            average_field_efficiency.push_back(value_point);
        }

        // Build filename
        std::string filename="Efficiency-Cosine_Attenuation_";
        filename.append("LA-").append(std::to_string((int) latitude_degree)).append("_");    
        filename.append("TH-").append(std::to_string((int) tower_height)).append("_");
        filename.append("RR-").append(std::to_string((int) receiver_radius)).append("_");
        filename.append("RD-").append(std::to_string((int) distance_between_receivers)).append("_");    
        filename.append("DT-").append(std::to_string((int) delta_t)).append(".dat");

        // Write results to finary file
        std::cout << "Writing results to binary file: " << filename << std::endl;
        WriteResults(filename, ideal_efficiency_type, ideal_efficiency_map, average_field_efficiency);

    } 
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count()/60000000. << " minutes" << std::endl;
}

void WriteResults(std::string filename, hypl::Heliostat::IdealEfficiencyType ideal_efficiency_type, 
                  hypl::IdealEfficiencyMap& ideal_efficiency_map, std::vector< std::pair<double, double> > & average_field_efficiency)
{
    std::ofstream outputFile;
    outputFile.open (filename, std::ios::out | std::ios::app | std::ios::binary);

    // Write nrows, ncolums, xmin, xmax, ymin, ymax
    outputFile.write( (char *) &ideal_efficiency_map.nrows(), sizeof(int));
    outputFile.write( (char *) &ideal_efficiency_map.ncolumns(), sizeof(int));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().xmin(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().xmax(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().ymin(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().ymax(), sizeof(double));

    // Write the text indicating the type of ideal efficiency calcultation
    std::string ideal_efficiency_type_text;
    switch ( ideal_efficiency_type )
    {
        case hypl::Heliostat::IdealEfficiencyType::CosineOnly:
            ideal_efficiency_type_text = "Cosine Only";
            break;
        case hypl::Heliostat::IdealEfficiencyType::CosineAndTransmittance:
            ideal_efficiency_type_text = "Cosine and Attenuation";
            break;
        case hypl::Heliostat::IdealEfficiencyType::AllFactors:
            ideal_efficiency_type_text = "All Factors";
            break;
        default:
            ideal_efficiency_type_text = "Not Defined";
            break;
    }
    outputFile.write( const_cast<char*>(ideal_efficiency_type_text.c_str()), ideal_efficiency_type_text.size() +1 );

    // Write the annual ideal efficiency map as a vector of nrows * ncolumns elements
    std::vector<hypl::Heliostat> const& heliostats = ideal_efficiency_map.heliostats();
    for (auto& element : heliostats)
    {
        double annual_ideal_efficiency = element.m_annual_ideal_efficiency;
        outputFile.write((char *) &annual_ideal_efficiency, sizeof(double));
    }

    // Write the average annual field efficiency vector
    for (auto& element : average_field_efficiency)
    {        
        outputFile.write((char *) &element.first, sizeof(double));
        outputFile.write((char *) &element.second, sizeof(double));     
    }

    outputFile.close();
}