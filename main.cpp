#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
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

void WriteResults(std::string filename, hypl::Heliostat::IdealEfficiencyType ideal_efficiency_type, hypl::IdealEfficiencyMap& ideal_efficiency_map);

int main(int argc, char *argv[])
{
    // Scenario
    double latitude_degree = 30.0; // Degrees North
    double tower_height = 50.0; // Meters
    double receiver_radius = 5.0; // Meters 
    double heliostat_field_area = 300000; // Square meters
    double characteristic_length = sqrt(heliostat_field_area);
    
    // Environment
    hypl::Location location(latitude_degree * hypl::mathconstants::degree);
    hypl::Atmosphere atmosphere; // Using default attenuation model
    hypl::Environment environment(location, atmosphere);

    // Boundaries
    double xmin = -(3 * characteristic_length);
    double xmax = -xmin;
    double ymin = xmin;
    double ymax = -ymin;
    hypl::Boundaries boundaries(xmin,xmax,ymin,ymax);

    std::cout << std::endl << "Boundaries: " << "( (" << xmin << ", " << xmax << "), (" << ymin << ", " << ymax << ") )" << std::endl;

    // Grid
    int nrows = 600;
    int ncolumns = 600;

    // Analysis parameters       
    double delta_t=225.;
    hypl::Heliostat::IdealEfficiencyType ideal_efficiency_type = hypl::Heliostat::IdealEfficiencyType::CosineAndTransmittance;

    for( double factor = 0.5; factor < 3.6; factor += 0.025  )
    {
        double distance_between_receivers =  factor * characteristic_length;
        // Receivers
        std::vector<hypl::Receiver> receivers;
        receivers.push_back(hypl::Receiver(hypl::vec3d(-distance_between_receivers/2.0, 0.0, tower_height), receiver_radius));
        receivers.push_back(hypl::Receiver(hypl::vec3d( distance_between_receivers/2.0, 0.0, tower_height), receiver_radius));   

        // Compute Efficiency Matrix
 //       std::cout << "Computing annual heliostat efficiencies... \n";
        auto start = std::chrono::high_resolution_clock::now();

        hypl::IdealEfficiencyMap ideal_efficiency_map(environment, boundaries, receivers, nrows, ncolumns); 
        ideal_efficiency_map.EvaluateAnnualEfficiencies(ideal_efficiency_type, delta_t);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//        std::cout << duration.count()/60000000. << " minutes" << std::endl;

        // MODIFICATION
 //       std::cout << "MODIFICATION ... \n";

        std::vector<hypl::Heliostat> const& heliostats = ideal_efficiency_map.heliostats();
        std::vector<double> aoe;
        for (auto& element : heliostats) aoe.push_back(element.m_annual_ideal_efficiency);

        double heliostat_size = ((xmax-xmin) * (ymax-ymin))/(nrows * ncolumns);
        int number_of_heliostats = std::round(heliostat_field_area / heliostat_size);

        std::sort(aoe.begin(), aoe.end(), std::greater<double>());
        double threshold_efficiency = aoe[number_of_heliostats];

        double average_field_efficiency = std::accumulate(aoe.begin(), std::next(aoe.begin(), number_of_heliostats), 0.0)/number_of_heliostats;

/*
        std::cout << "Heliostat surface (m2): " << heliostat_size << std::endl;
        std::cout << "Heliostats in the  field: " <<  number_of_heliostats << std::endl;
        std::cout << "Threshold efficiency: " <<  threshold_efficiency << std::endl;
        std::cout << "Threshold efficiency 2: " <<  *(aoe.begin()+number_of_heliostats) << std::endl;
        std::cout << "Average annual optical field efficiency: " << average_field_efficiency << std::endl;
*/

        std::cout << factor << ", " << distance_between_receivers << ", " << average_field_efficiency << std::endl;

        // Write results to binary output file
//        std::cout << "Writing binary output file... \n";  
        start = std::chrono::high_resolution_clock::now();

        std::string filename="Efficiency-Cosine_Attenuation_";
        filename.append("Lat-").append(std::to_string((int) latitude_degree)).append("_");
        filename.append("TH-").append(std::to_string((int) tower_height)).append("_");
        filename.append("RecRadius-").append(std::to_string((int) receiver_radius)).append("_");
        filename.append("RecDistance-").append(std::to_string((int) distance_between_receivers)).append("_");    
        filename.append("Resolution-225sec").append(".dat");

        WriteResults(filename, ideal_efficiency_type, ideal_efficiency_map);

        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
 //       std::cout << duration.count()/60000000. << " minutes" << std::endl;
    }   
 
    std::cout << "DONE" <<std::endl;

    return 1;
}

void WriteResults(std::string filename, hypl::Heliostat::IdealEfficiencyType ideal_efficiency_type, hypl::IdealEfficiencyMap& ideal_efficiency_map)
{
    std::ofstream outputFile;
    outputFile.open (filename, std::ios::out | std::ios::app | std::ios::binary);

    outputFile.write( (char *) &ideal_efficiency_map.nrows(), sizeof(int));
    outputFile.write( (char *) &ideal_efficiency_map.ncolumns(), sizeof(int));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().xmin(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().xmax(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().ymin(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.boundaries().ymax(), sizeof(double));

    std::string ideal_efficiency_name;
    switch ( ideal_efficiency_type )
    {
        case hypl::Heliostat::IdealEfficiencyType::CosineOnly:
            ideal_efficiency_name = "Cosine Only";
            break;
        case hypl::Heliostat::IdealEfficiencyType::CosineAndTransmittance:
            ideal_efficiency_name = "Cosine and Attenuation";
            break;
        case hypl::Heliostat::IdealEfficiencyType::AllFactors:
            ideal_efficiency_name = "All Factors";
            break;
        default:
            ideal_efficiency_name = "Not Defined";
            break;
    }
    outputFile.write( const_cast<char*>(ideal_efficiency_name.c_str()), ideal_efficiency_name.size() +1 );

    std::vector<hypl::Heliostat> const& heliostats = ideal_efficiency_map.heliostats();

    for (auto& element : heliostats)
    {
        double annual_ideal_efficiency = element.m_annual_ideal_efficiency;
        outputFile.write((char *) &annual_ideal_efficiency, sizeof(double));
    }
    outputFile.close();
}