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
#include "atmosphereVB.h"
#include "receiver.h"
#include "vec3d.h"
#include "boundaries.h"
#include "heliostatcosinetransmittance.h"
#include "idealefficiencymap.h"
#include "auxfunction.h"

void benchmark_two_receiver_analysis(int nrows, int ncolumns);
void TwoReceiversAnalysis(double latitude_degree, double tower_height, double receiver_radius, double maximum_heliostat_field_area);
void WriteResults(std::string filename, int maximum_number_of_valid_heliostats, 
                  hypl::IdealEfficiencyMap<hypl::HeliostatCosineAndTransmittance>& ideal_efficiency_map, std::vector< std::pair<double, double> > & average_field_efficiency);

int main(int argc, char *argv[])
{
    int nrows;
    int ncolumns;

    std::cout << "Please, enter number of rows: ";
    std::cin >> nrows;
    std::cout << "Please, enter number of columns: ";
    std::cin >> ncolumns;

    benchmark_two_receiver_analysis(nrows, ncolumns);

    std::cout << "DONE" <<std::endl;
    return 1;
}

//----------------------------------------------------------
void benchmark_two_receiver_analysis(int nrows, int ncolumns)
{
    std::cout << "Executing benchmark_two_receiver_analysis(" << nrows << ", " << ncolumns << ")" << std::endl;
    // Input data
    double latitude_degree = 30.0; // Degrees North
    double tower_height = 50.0; // Meters
    double receiver_radius = 5.0; // Meters 
    double maximum_heliostat_field_area = 2500000.0; // Square meters
    double delta_t = 225.0;

    // Environment
    hypl::Location location(latitude_degree * hypl::mathconstants::degree);
    hypl::AtmosphereVB *ptr_atmosphere = new hypl::AtmosphereVB(); // Using default attenuation model

    // Boundaries
    double characteristic_length = sqrt(maximum_heliostat_field_area);
    double xmin = -(1.5 * characteristic_length);
    double xmax = -xmin;
    double ymin = -(0.5 * characteristic_length);
    double ymax =  (1.5 * characteristic_length);
    hypl::Boundaries boundaries(xmin,xmax,ymin,ymax);

    // Compute heliostat reflective area and number of heliostats in the field
    double heliostat_area = boundaries.area()/(nrows * ncolumns);
    int total_number_of_heliostats = nrows * ncolumns;
    int maximum_number_of_valid_heliostats = maximum_heliostat_field_area / heliostat_area;

    // Distance between receivers
    double factor = 1.0;
    double distance_between_receivers =  factor * characteristic_length;
    std::vector<hypl::Receiver> receivers;
    receivers.push_back(hypl::Receiver(hypl::vec3d(-distance_between_receivers/2.0, 0.0, tower_height), receiver_radius));
    receivers.push_back(hypl::Receiver(hypl::vec3d( distance_between_receivers/2.0, 0.0, tower_height), receiver_radius));   

    // Scenario
    hypl::Scenario scenario(location, ptr_atmosphere, boundaries, receivers);

    // BEGIN COMPUTATIONS
    std::cout << "Start computing --------------------------------------------" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    // Compute annual optical efficiencies of ideal heliostats
    hypl::IdealEfficiencyMap<hypl::HeliostatCosineAndTransmittance> ideal_efficiency_map(scenario, nrows, ncolumns); 
    ideal_efficiency_map.EvaluateAnnualEfficiencies(delta_t);

    // Copy annual heliostats' annual ideal efficiencies (aie) to a vector of doubles
    std::vector<hypl::HeliostatCosineAndTransmittance> const& heliostats = ideal_efficiency_map.heliostats();
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

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time computing = " << duration.count()/1000000. << " seconds" << std::endl;
    // END COMPUTATIONS

    // BEGIN RECORDING RESULTS
    std::cout << "Start saving to disk --------------------------------------------" << std::endl;   
    start = std::chrono::high_resolution_clock::now();

    // Build filename
    std::string filename="Efficiency-Cosine_Attenuation_";
    filename.append("LA-").append(std::to_string((int) latitude_degree)).append("_");    
    filename.append("TH-").append(std::to_string((int) tower_height)).append("_");
    filename.append("RR-").append(std::to_string((int) receiver_radius)).append("_");
    filename.append("RD-").append(std::to_string((int) distance_between_receivers)).append("_");    
    filename.append("DT-").append(std::to_string((int) delta_t)).append(".dat");

    // Write results to finary file
    std::cout << "Writing results to binary file: " << filename << std::endl;
    WriteResults(filename, maximum_number_of_valid_heliostats, ideal_efficiency_map, average_field_efficiency);

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time recording results = " << duration.count()/1000000. << " seconds" << std::endl;
    //  END RECORDING RESULTS 

    // Cleaning 
    delete ptr_atmosphere;
}

void WriteResults(std::string filename, int maximum_number_of_valid_heliostats, 
                  hypl::IdealEfficiencyMap<hypl::HeliostatCosineAndTransmittance>& ideal_efficiency_map, std::vector< std::pair<double, double> > & average_field_efficiency)
{
    std::ofstream outputFile;
    outputFile.open (filename, std::ios::out | std::ios::app | std::ios::binary);

    // Write the text indicating the type of ideal efficiency calcultation
    std::string ideal_efficiency_type_text = "Cosine and Attenuation"; // HACK - NEED TO BE DONE PROPERLY

    outputFile.write( const_cast<char*>(ideal_efficiency_type_text.c_str()), ideal_efficiency_type_text.size() +1 );

    // Write maximum number of valid heliostats
    outputFile.write( (char *) &maximum_number_of_valid_heliostats, sizeof(int));

    // Write nrows, ncolums, xmin, xmax, ymin, ymax
    outputFile.write( (char *) &ideal_efficiency_map.nrows(), sizeof(int));
    outputFile.write( (char *) &ideal_efficiency_map.ncolumns(), sizeof(int));
    outputFile.write( (char *) &ideal_efficiency_map.scenario().boundaries().xmin(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.scenario().boundaries().xmax(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.scenario().boundaries().ymin(), sizeof(double));
    outputFile.write( (char *) &ideal_efficiency_map.scenario().boundaries().ymax(), sizeof(double));

    // Write number of receivers
    int nreceivers = ideal_efficiency_map.scenario().receivers().size();
    outputFile.write( (char *) &nreceivers, sizeof(int));

    // Write the annual ideal efficiency map as a vector of nrows * ncolumns elements
    std::vector<hypl::HeliostatCosineAndTransmittance> const& heliostats = ideal_efficiency_map.heliostats();
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