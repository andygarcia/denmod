#ifndef OUTPUT_DENSIMOUTPUT_H
#define OUTPUT_DENSIMOUTPUT_H

#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../densim/Classes.h"



namespace sim {
namespace output {

class DensimOutput
{
// Classes
public:
  class DailyLocationOutput
  {
  public:
    double Incubate1;                                   // number of humans incubating
    double Incubate2;                                   // number of humans incubating
    double Incubate3;                                   // number of humans incubating
    double Incubate4;                                   // number of humans incubating
    double Viremic1;                                    // number of humans infective
    double Viremic2;                                    // number of humans infective
    double Viremic3;                                    // number of humans infective
    double Viremic4;                                    // number of humans infective
    double MosqTotal;                                   // total daily mosquitoes
    double MosqInfvTotal[4+1];                          // total infective mosquitoes
    int InfvBites;                                      // new potential inoculations
    double EIPDevRate[4+1];                             // extrinsic incubation period rate - daily
    int NumHumans;                                      // number of humans
    double SerPos[23+1][4+1];                           // percent of indiv. in age class that are seropositive
    double NewHumCases[4+1];                            // number of new human cases/day/serotype
    sim::ds::SequentialInfectionValues SeqInfVals;      // daily sequential value statistics
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

// Typedefs
public:
  typedef std::vector<DailyLocationOutput> LocationOutput;
  typedef std::vector<DailySerotypeOutput> SerotypeOutput;
  typedef std::vector<SerotypeOutput> SerotypeOutputs;

// Constructors
public:
  DensimOutput( boost::gregorian::date startDate, boost::gregorian::date stopDate );
  ~DensimOutput(void);

// Methods
public:
  boost::gregorian::date_period GetDateRange(void);
  void AddDailyLocationOutput( DailyLocationOutput dlo, boost::gregorian::date d );
  void SetInitialData( std::vector<int> & initialAgeDistribution,
                       std::vector<std::vector<int>> & initialSeroDistribution );
  void SetFinalData( std::vector<int> & finalAgeDistribution,
                     std::vector<int> & births,
                     std::vector<int> & deaths,
                     std::vector<std::vector<int>> & finalSeroDistribution );

  std::vector<int> GetInitialAgeDistribution(void);
  std::vector<int> GetFinalAgeDistribution(void);
  std::vector<int> GetBirths(void);
  std::vector<int> GetDeaths(void);
  std::vector<double> GetArea(void);
  std::vector<int> GetPopulation(void);
  std::vector<double> GetMosqTotal(void);
  std::vector<int> GetPotentiallyInfectiveBites(void);

  std::vector<int> GetInitialSeroDistribution( int serotype );
  std::vector<int> GetFinalSeroDistribution( int serotype );
  std::vector<double> GetDetailedSeroprevalence( int seroClass, int serotype );
  std::vector<double> GetPersonsWithVirus( int serotype );
  std::vector<double> GetPersonsIncubating( int serotype );
  std::vector<double> GetPersonsViremic( int serotype );
  std::vector<double> GetEipDevelopmentRate( int serotype );
  std::vector<double> GetInfectiveMosquitoes( int serotype );

// Members
private:
  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;

  LocationOutput _locationOutput;
  SerotypeOutputs _serotypeOutputs;

  std::vector<int> _initialAgeDistribution;
  std::vector<int> _finalAgeDistribution;

  std::vector<int> _births;
  std::vector<int> _deaths;

  std::vector<std::vector<int>> _initialSeroDistribution;
  std::vector<std::vector<int>> _finalSeroDistribution;
};

};
};

#endif
