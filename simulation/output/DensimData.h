#ifndef OUTPUT_DENSIMDATA_H
#define OUTPUT_DENSIMDATA_H

#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../densim/SimClasses.h"


namespace sim {
namespace output {

class DensimData
{
public:
  class DailyLocationOutput
  {
  public:
    double Incubate1;                        // Number of humans incubating
    double Incubate2;                        // Number of humans incubating
    double Incubate3;                        // Number of humans incubating
    double Incubate4;                        // Number of humans incubating
    double Viremic1;                         // Number of humans infective
    double Viremic2;                         // Number of humans infective
    double Viremic3;                         // Number of humans infective
    double Viremic4;                         // Number of humans infective
    double MosqTotal;                        // Total daily mosquitoes
    double MosqInfvTotal[4+1];               // Total infective mosquitoes
    int InfvBites;                           // New potential inoculations
    double EIPDevRate[4+1];                  // Extrinsic incubation period rate - daily
    int NumHumans;                           // Number of humans
    double SerPos[23+1][4+1];                // Percent of indiv. in age class that are seropositive
    double NewHumCases[4+1];                 // Number of new human cases/day/serotype
    sim::ds::SequentialInfectionValues SeqInfVals;    // Daily sequential value statistics
  };


  class DailySerotypeOutput
  {
  public:
    double Incubating;
    double Viremic;
    double InfectiveMosquitoes;
    double EipDevelopmentRate;
    double NewCases;
  };
public:
  typedef std::map<boost::gregorian::date, DailyLocationOutput> LocationOutput;
  typedef std::map<boost::gregorian::date, DailySerotypeOutput> SerotypeOutput;

public:
  DensimData(void);
  ~DensimData(void);

public:
  boost::gregorian::date_period GetDateRange(void);
  
  void AddDailyLocationOutput( DailyLocationOutput dlo, boost::gregorian::date d );
  void SetInitialData( std::vector<int>& initialAgeDistribution );
  void SetFinalData( std::vector<int>& finalAgeDistribution, std::vector<int>& births, std::vector<int>& deaths );

  std::vector<int> GetInitialAgeDsitribution(void);
  std::vector<int> GetFinalAgeDsitribution(void);
  std::vector<int> GetBirths(void);
  std::vector<int> GetDeaths(void);

  // Virus (Incubating + Viremic)
  double GetDengue1Virus( boost::gregorian::date d );
  double GetDengue2Virus( boost::gregorian::date d );
  double GetDengue3Virus( boost::gregorian::date d );
  double GetDengue4Virus( boost::gregorian::date d );

  // Incubating
  double GetDengue1Incubating( boost::gregorian::date d );
  double GetDengue2Incubating( boost::gregorian::date d );
  double GetDengue3Incubating( boost::gregorian::date d );
  double GetDengue4Incubating( boost::gregorian::date d );

  // Viremic
  double GetDengue1Viremic( boost::gregorian::date d );
  double GetDengue2Viremic( boost::gregorian::date d );
  double GetDengue3Viremic( boost::gregorian::date d );
  double GetDengue4Viremic( boost::gregorian::date d );

  // Mosquitoes with Virus
  double GetDengue1InfectiveMosquitoes( boost::gregorian::date d );
  double GetDengue2InfectiveMosquitoes( boost::gregorian::date d );
  double GetDengue3InfectiveMosquitoes( boost::gregorian::date d );
  double GetDengue4InfectiveMosquitoes( boost::gregorian::date d );

  // EIP Development Rate
  double GetDengue1EipDevelopmentRate( boost::gregorian::date d );
  double GetDengue2EipDevelopmentRate( boost::gregorian::date d );
  double GetDengue3EipDevelopmentRate( boost::gregorian::date d );
  double GetDengue4EipDevelopmentRate( boost::gregorian::date d );

  // Number of Humans
  int GetNumberOfHumans( boost::gregorian::date d );

  // Female mosquitoes
  double GetMosqTotal( boost::gregorian::date d );

  // Potentially Infective Bites
  double GetPotentiallyInfectiveBites( boost::gregorian::date d );

private:
  LocationOutput LocationOutput_;
  SerotypeOutput Dengue1Output_;
  SerotypeOutput Dengue2Output_;
  SerotypeOutput Dengue3Output_;
  SerotypeOutput Dengue4Output_;

  std::vector<int> InitialAgeDistribution_;
  std::vector<int> FinalAgeDistribution_;
  std::vector<int> Births_;
  std::vector<int> Deaths_;
};

};
};

#endif
