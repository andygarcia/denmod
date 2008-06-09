#ifndef OUTPUT_DENSIMOUTPUT_H
#define OUTPUT_DENSIMOUTPUT_H

#include <map>
#include "Output.h"
#include "../densim/SimClasses.h"


namespace sim {
namespace output {

class DensimOutput
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


  class LocationOutput
  {
  public:
    LocationOutput( boost::gregorian::date startDate, boost::gregorian::date stopDate )
    : TotalFemales(startDate, stopDate),
      InfvBites(startDate, stopDate),
      Humans(startDate, stopDate)
    {}

    Output<double> TotalFemales;
    Output<int> InfvBites;
    Output<int> Humans;
    Output<double> SimulationArea;
  };


  class SerotypeOutput
  {
  public:
    SerotypeOutput()
    : Incubating(),
      Viremic(),
      InfectiveMosquitoes(),
      EipDevelopmentRate(),
      NewCases()
    {
      throw "Not supported.  sim::output::SerotypeOutput must be constructed using date range.";
    }

    SerotypeOutput( boost::gregorian::date startDate, boost::gregorian::date stopDate )
    : Incubating(startDate, stopDate),
      Viremic(startDate, stopDate),
      InfectiveMosquitoes(startDate, stopDate),
      EipDevelopmentRate(startDate, stopDate),
      NewCases(startDate, stopDate)
    {}
    
    virtual ~SerotypeOutput(void)
    {}

  public:
    Output<double> Incubating;
    Output<double> Viremic;
    Output<double> InfectiveMosquitoes;
    Output<double> EipDevelopmentRate;
    Output<double> NewCases;
  };

  //class SerotypeOutputs
  //{
  //public:
  //  SerotypeOutputs( boost::gregorian::date startDate, boost::gregorian::date stopDate );
  //  virtual ~SerotypeOutputs(void);

  //public:

  //}

public:
  typedef std::map<int, SerotypeOutput> SerotypeOutputs;
  typedef std::vector<int> ClassData;

public:
  DensimOutput( boost::gregorian::date startDate, boost::gregorian::date stopDate );
  ~DensimOutput(void);

public:
  void AddDailyLocationOutput( DailyLocationOutput dlo, boost::gregorian::date d );
  void SetInitialData( std::vector<int>& initialAgeDistribution );
  void SetFinalData( std::vector<int>& finalAgeDistribution, std::vector<int>& births, std::vector<int>& deaths );

  ClassData GetInitialAgeDsitribution(void);
  ClassData GetBirths(void);
  ClassData GetDeaths(void);
  ClassData GetFinalAgeDsitribution(void);

  std::vector<double> GetPersonsWithVirus( int serotype );
  std::vector<double> & GetPersonsIncubating( int serotype );
  std::vector<double> & GetPersonsViremic( int serotype );
  std::vector<double> & GetInfectiveMosquitoes( int serotype );
  std::vector<double> & GetEipDevelopmentRate( int serotype );

  // Number of Humans
  std::vector<double> & GetFemales(void);
  std::vector<double> GetFemalesPerPerson(void);
  std::vector<int> & GetNumberOfHumans(void);
  std::vector<double> GetSimulationArea( double humanHostDensity );
  std::vector<int> & GetPotentiallyInfectiveBites(void);

private:
  LocationOutput _locationOutput;
  SerotypeOutputs _serotypeOutputs;

  ClassData _initialAgeDistribution;
  ClassData _births;
  ClassData _deaths;
  ClassData _finalAgeDistribution;
};

};
};

#endif
