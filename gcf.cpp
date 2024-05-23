#include <cmath>
#include <iostream>
#include <stdlib.h>

#include "gcf.h"

void gcf::SevereError(std::string errorMessage)
{
    std::cerr << errorMessage << std::endl;
    exit(-1);
}

// normalize angle phi to the range [phi0, phi0 + 2pi)
double gcf::normalizeAngle(double phi, double phi0)
{
    return phi - TwoPi*floor((phi - phi0)/TwoPi);
}