#ifndef OUTPUT_CIMSIMOUTPUT_H
#define OUTPUT_CIMSIMOUTPUT_H

#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "MosData.h"
#include "PopData.h"



namespace sim {
namespace output {

class DailyLocationOutput;
class DailyDensimOutput;
class DailyContainerOutput;



class CimsimOutput
{
public:
  typedef std::map<boost::gregorian::date, DailyLocationOutput> LocationOutput;
  typedef std::map<boost::gregorian::date, DailyContainerOutput> ContainerOutput;
  typedef std::map<int, ContainerOutput> ContainerOutputs;

public:
  CimsimOutput(void);
  ~CimsimOutput(void);

public:
  MosData * GetMosData(void);

  // initial starting population of CIMSiM
  sim::cs::PreOviAdultCohortCollection InitialPreOviAdultCohorts;
  sim::cs::OviAdultCohortCollection InitialOviAdultCohorts;

  void SetPopData( PopData * popData );
  PopData * GetPopData(void);

public:
  boost::gregorian::date_period GetDateRange(void);
  std::vector<std::string> GetContainerNames(void);
  
  void AddDailyLocationOutput( DailyLocationOutput dlo, boost::gregorian::date d );
  void AddDailyContainerOutput( DailyContainerOutput dco, boost::gregorian::date d, int containerID );

private:
  void CalculateContainerTotals(void);

public:
  // Location outputs
  std::vector<double> GetFemales( boost::gregorian::date startDate, boost::gregorian::date endDate );
  std::vector<double> GetNewFemales( boost::gregorian::date startDate, boost::gregorian::date endDate );
  std::vector<double> GetAverageFemaleWeight( boost::gregorian::date startDate, boost::gregorian::date endDate );
  std::vector<double> GetOviposition( boost::gregorian::date startDate, boost::gregorian::date endDate );
  std::vector<double> GetTotalPupae( boost::gregorian::date startDate, boost::gregorian::date endDate );
  std::vector<double> GetTotalLarvae( boost::gregorian::date startDate, boost::gregorian::date endDate );
  std::vector<double> GetTotalEggs( boost::gregorian::date startDate, boost::gregorian::date endDate );

  // Container outputs
  std::vector<double> GetDepth( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetFood( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetMaxTemp( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetMinTemp( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetEggs( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetLarvae( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetPupae( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetAvgDryPupWt( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetNewFemales( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetCumulativeFemales( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetOviposition( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetTotalDensity( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetUntreatedDensity( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetTreatedDensity( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetExcludedDensity( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );

  std::vector<double> GetEggDevelopment( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetLarvaeDevelopment( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );
  std::vector<double> GetPupaeDevelopment( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID );


private:
  LocationOutput LocationOutput_;
  ContainerOutputs ContainerOutputs_;

  bool AreContainersTotaled_;
  ContainerOutput ContainerTotals_;

  PopData * PopData_;
  bool IsPopDataReleased_;
};



class DailyLocationOutput
{
public:
  double Females;
  double Oviposition;

  double NewFemales;
  double AverageWeight;
  double OverallSurvival;
  double AdultDevelopment;

public:
  DailyMosData GetDailyMosData(void);
};



class DailyDensimOutput
{
public:
  double NewFemales;
  double AverageWeight;
  double OverallSurvival;
  double AdultDevelopment;
};



class DailyContainerOutput
{
public:
  DailyContainerOutput(void) {
    DayOfYear = 0;
    Depth = 0;
    MaxTemp = 0;
    MinTemp = 0;
    Food = 0;
    Eggs = 0;
    Larvae = 0;
    Pupae = 0;
    AvgDryPupWt = 0;
    NewFemales = 0;
    CumulativeFemales = 0;
    Oviposition = 0;
    TotalDensity = 0;
    UntreatedDensity = 0;
    TreatedDensity = 0;
    ExcludedDensity = 0;

    EggDevelopment = 0;
    LarvaeDevelopment = 0;
    PupaeDevelopment = 0;
  }

public:
  int DayOfYear;
  double Depth;
  double MaxTemp;
  double MinTemp;
  double Food;
  double Eggs;
  double Larvae;
  double Pupae;
  double AvgDryPupWt;
  double NewFemales;
  double CumulativeFemales;
  double Oviposition;
  double TotalDensity;
  double UntreatedDensity;
  double TreatedDensity;
  double ExcludedDensity;

  double EggDevelopment;
  double LarvaeDevelopment;
  double PupaeDevelopment;
};

};
};

#endif
