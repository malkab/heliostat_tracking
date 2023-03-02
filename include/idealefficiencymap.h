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

        IdealEfficiencyMap(Scenario& scenario, int nrows, int ncolumns,  Heliostat::IdealEfficiencyType ideal_efficiency_type);

        //Accessors
        Scenario const& scenario() const {return m_scenario;}
        int const& nrows() const {return m_nrows;}
        int const& ncolumns() const {return m_ncolumns;}
        std::vector<Heliostat> const& heliostats() {return m_heliostat;}

        //Mutators
        void update();
        void regenerate();
        void set_scenario(Scenario const& scenario) {m_scenario = scenario; update();}
        void set_nrows(int nrows) {m_nrows = nrows; regenerate();}
        void set_ncolumns(int ncolumns) {m_ncolumns = ncolumns; regenerate();}
        void set_dimensions(int nrows, int ncolumns) {m_nrows = nrows; m_ncolumns = ncolumns; regenerate();}

        //Public functions
        void EvaluateAnnualEfficiencies(Heliostat::IdealEfficiencyType ideal_efficiency_type, double delta_t);

    private:
        void ProcessDay(int const& day_number, Heliostat::IdealEfficiencyType const& ideal_efficiency_type, 
            double const& delta_hour_angle, double const& weight, double& direct_insolation);
        double StartingHourAngle(double const& wo, double const& delta_hour_angle);

    private:
        Scenario& m_scenario;
        int m_nrows;
        int m_ncolumns;
        Heliostat::IdealEfficiencyType m_ideal_efficiency_type;
        std::vector<Heliostat> m_heliostat;
    };
}
#endif // IDEALEFFICIENCYMAP_H