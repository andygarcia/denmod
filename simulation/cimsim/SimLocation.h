#ifndef SIM_CS_LOCATION_H
#define SIM_CS_LOCATION_H

#include <string>
#include <vector>
#include "../input/Location.h"
#include "../output/Log.h"
#include "SimContainer.h"
#include "Cohorts.h"



namespace sim {
namespace cs {


class SimLocation
{
// Constructors
public:
  SimLocation( const input::Location * location, boost::gregorian::date startDate, boost::gregorian::date stopDate, const output::PopData * popData = NULL );
  ~SimLocation(void);

// Methods
public:
  void Start(void);
  output::CimsimOutput * GetSimOutput(void);

private:
  void StartSimulation(void);
  void DoYear(void);
  void ReadWeather(int year);
  static bool IsEndOfMonth( boost::gregorian::date d );

  void CalculateAdultTemperatureSurvival(void);
  void CalculateAdultSatDefSurvival(void);
  double CalculateAdultAgeDependentSurvival( int age );

  double GetNulliparousCount(void);
  double GetParousCount(void);
  double GetOvipositingCount(void);

  double GetFemaleAverageWeight(void);
  double GetOvipositingFemaleAverageWeight(void);
  std::pair<double,double> GetOvipositingTotals(void);

  double CalculateDoubleBloodMealProportion(void);
  double GetPreOviBiters( double doubleProp );
  double GetOviBiters( double doubleProp );

  double GetNulliparousBiters( double doubleProp );
  double GetParousBiters( double doubleProp );

  void CalculateDailyTotals(void);
  void UpdateOutput( boost::gregorian::date d, double adultWeight, double adultDev, double newEggs );
  output::PopData * GeneratePopData(void);

private:
  const input::Location * _location;

  output::CimsimOutput * Output_;
  bool _outputReleased;

#ifdef _DEBUG
  output::LocationLog _locationLog;
  output::AdultSurvivalLog _adultSurvivalLog;
#endif

  // time
  int Year;
  int Day;
  boost::gregorian::date BeginDate_;
  boost::gregorian::date CurrentDate_;
  boost::gregorian::date EndDate_;

  // pop data
  bool UsingPop_;

  // containers
  typedef std::vector<SimContainer*> ContainerCollection;
  ContainerCollection Containers_;

  // controls
  std::vector<input::Control*> Controls_;
  std::vector<input::SourceReduction*> SourceReductions_;
  std::vector<input::OvipositionExclusion*> OvipositionExclusions_;
  std::vector<input::EggDestruction*> EggDestructions_;
  std::vector<input::Larvicide*> Larvicides_;
  std::vector<input::SterileMaleRelease*> SterileMaleReleases_;
  std::vector<input::SpaceSpray*> SpaceSprays_;
  std::vector<input::ResidualSpray*> ResidualSprays_;

  // adult biology
  double _adultNominalSurvival;
  const input::Biology::AdultParameters::AgeDependentSurvivalParameters * _adultAgeDependentSurvival;
  const input::Biology::AdultParameters::TemperatureParameters * _adultTemperatureSurvival;
  const input::Biology::AdultParameters::SaturationDeficitParameters * _adultSatDefSurvival;
  double _adultP25;
  double _adultDHA;
  double _adultDHH;
  double _adultTH2;
  double _adultFirstDevelopmentThreshold;
  double _adultSecondDevelopmentThreshold;
  double _minimumOvipositionTemperature;
  double _fecundityCoefficient;
  double _proportionAdultsOutdoor;
  double _interruptedFeedsPerMeal;
  const input::Biology::AdultParameters::DoubleBloodMealParameters * _adultDoubleBloodMeals;

  // initial adult population
  PreOviAdultCohortCollection InitialPreOviAdultCohorts;
  OviAdultCohortCollection InitialOviAdultCohorts;

  // adult population
  PreOviAdultCohortCollection PreOviAdultCohorts;
  OviAdultCohortCollection OviAdultCohorts;

  // all cohorts currently ovipositing
  AdultCohortCollection OvipositingCohorts;

  // TODO new adult cohort system for age dependent survival
  PreOviAdultCohortCollection NulliparousCohorts;
  OviAdultCohortCollection ParousCohorts;
  AdultCohortCollection NewOvipositingCohorts;

  // blood seeking females
  double _preOviBiters;
  double _oviBiters;
  double _totalBiters;

  // adult daily survival
  double AdultSurvival;
  double AdultSurvivalTemperature;
  double AdultSurvivalSatDef;

  // new female cohort
  double NewFemales;
  double NewFemaleWeight;

  std::vector<double> MosqAgeDistr;

  double TotalMales;
  double TotalSterileMales;
  double TotalSterileMalesYesterday;

  std::vector<double> TemperatureMax;
  std::vector<double> TemperatureMin;
  std::vector<double> TemperatureAvg;
  std::vector<double> Rain;
  std::vector<double> RelHumid;
  std::vector<double> SD;
};

};
};

#endif
