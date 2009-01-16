#ifndef OUTPUT_DENSIMOUTPUT_H
#define OUTPUT_DENSIMOUTPUT_H

#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../densim/SimClasses.h"



namespace sim {
namespace output {

class DensimOutput
{
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
public:
  typedef std::map<boost::gregorian::date, DailyLocationOutput> LocationOutput;
  typedef std::map<boost::gregorian::date, DailySerotypeOutput> SerotypeOutput;
  typedef std::map<int, SerotypeOutput> SerotypeOutputs;

public:
  DensimOutput(void);
  ~DensimOutput(void);

public:
  boost::gregorian::date_period GetDateRange(void);
  
  void AddDailyLocationOutput( DailyLocationOutput dlo, boost::gregorian::date d );
  void SetInitialData( std::vector<int> & initialAgeDistribution,
                       std::vector<std::vector<int>> & initialSeroprevalence );
  void SetFinalData( std::vector<int> & finalAgeDistribution,
                     std::vector<int> & births,
                     std::vector<int> & deaths,
                     std::vector<std::vector<int>> & finalSeroprevalence );


  std::vector<int> GetInitialAgeDsitribution(void);
  std::vector<int> GetFinalAgeDistribution(void);
  std::vector<int> GetBirths(void);
  std::vector<int> GetDeaths(void);

  std::vector<int> GetNumberOfHumans( boost::gregorian::date startDate, boost::gregorian::date stopDate );
  std::vector<double> GetMosqTotal( boost::gregorian::date startDate, boost::gregorian::date stopDate );
  std::vector<int> GetPotentiallyInfectiveBites( boost::gregorian::date startDate, boost::gregorian::date stopDate );

  // serotype specific
  std::vector<int> GetInitialSeroprevalence( int serotype );
  std::vector<int> GetFinalSeroprevalence( int serotype );

  std::vector<double> GetPersonsWithVirus( boost::gregorian::date startDate, boost::gregorian::date stopDate, int serotype );
  std::vector<double> GetPersonsIncubating( boost::gregorian::date startDate, boost::gregorian::date stopDate, int serotype );
  std::vector<double> GetPersonsViremic( boost::gregorian::date startDate, boost::gregorian::date stopDate, int serotype );
  std::vector<double> GetEipDevelopmentRate( boost::gregorian::date startDate, boost::gregorian::date stopDate, int serotype );
  std::vector<double> GetInfectiveMosquitoes( boost::gregorian::date startDate, boost::gregorian::date stopDate, int serotype );

private:
  LocationOutput _locationOutput;
  SerotypeOutputs _serotypeOutputs;

  std::vector<int> _initialAgeDistribution;
  std::vector<int> _finalAgeDistribution;
  std::vector<int> _births;
  std::vector<int> _deaths;

  std::vector<std::vector<int>> _initialSeroprevalence; 
  std::vector<std::vector<int>> _finalSeroprevalence;
};

};
};

#endif
