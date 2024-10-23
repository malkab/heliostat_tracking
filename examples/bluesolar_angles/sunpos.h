#ifndef __SUNPOS_H
#define __SUNPOS_H


// Declaration of some constants
#define pi 3.14159265358979323846
#define twopi (2*pi)
#define degree (pi/180) // factor to transform degrees into radians.
#define dEarthMeanRadius 6371.01  // In km
#define dAstronomicalUnit 149597870.7  // In km

struct cTime
{
    int iYear;
    int iMonth;
    int iDay;
    double dHours;
    double dMinutes;
    double dSeconds;
};

struct cLocation
{
    double dLongitude; //radians
    double dLatitude; //radians
};

struct cSunCoordinates
{
    double dAzimuth; //radians
    double dZenithAngle; //radians
    double dBoundedHourAngle; //radians
    double dRightAscension; //radians
    double dDeclination; //radians
};

void sunpos(cTime udtTime, cLocation udtLocation, cSunCoordinates *udtSunCoordinates);

#endif