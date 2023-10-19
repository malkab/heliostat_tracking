#include <iostream>


int main(int argc, char *argv[])
{
    double sun_azimuth;
    double sun_elevation;

    std::cout << "Please, enter sun position: " <<std::endl;
    std::cout << "   - Azimuth (North towards East) in degrees: ";
    std::cin >> sun_azimuth;
    std::cout << "   - Elevation in degrees: ";
    std::cin >> sun_elevation;

    std::cout << "DONE" <<std::endl;
    return 1;
}