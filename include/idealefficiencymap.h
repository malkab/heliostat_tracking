#ifndef IDEALEFFICIENCYMAP_H
#define IDEALEFFICIENCYMAP_H

#include <vector>

#include "scenario.h"
#include "heliostat.h"

namespace hypl
{
    class IdealEfficiencyMap
    {
    public:
        IdealEfficiencyMap(Scenario& scenario, int nrows, int ncolumns, Heliostat* heliostat_factory);
        ~IdealEfficiencyMap();
        //Accessors
        Heliostat const* heliostat_factory() {return m_heliostat_factory;} 
        Scenario const& scenario() const {return m_scenario;}
        int const& nrows() const {return m_nrows;}
        int const& ncolumns() const {return m_ncolumns;}
        std::vector<Heliostat*> const& heliostats() {return m_heliostat;}

        //Mutators
        void update();
        void regenerate();
        void set_heliostat_factory(Heliostat* heliostat_factory) {delete m_heliostat_factory; m_heliostat_factory = heliostat_factory;}
        void set_scenario(Scenario const& scenario) {m_scenario = scenario; update();}
        void set_nrows(int nrows) {m_nrows = nrows; regenerate();}
        void set_ncolumns(int ncolumns) {m_ncolumns = ncolumns; regenerate();}
        void set_dimensions(int nrows, int ncolumns) {m_nrows = nrows; m_ncolumns = ncolumns; regenerate();}

        //Public functions
        void EvaluateAnnualEfficiencies(double delta_t);

    private:
        void ProcessDay(int const& day_number, 
            double const& delta_hour_angle, double const& weight, double& direct_insolation);
        double StartingHourAngle(double const& wo, double const& delta_hour_angle);

    private:
        Heliostat* m_heliostat_factory;
        Scenario& m_scenario;
        int m_nrows;
        int m_ncolumns;
        std::vector<Heliostat*> m_heliostat;
    };
}
#endif // IDEALEFFICIENCYMAP_H