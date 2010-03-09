#ifndef SIM_CS_DISCRETE_LOCATION_H
#define SIM_CS_DISCRETE_LOCATION_H

#include <string>
#include <vector>
#include "../input/Location.h"
#include "DiscreteSimContainer.h"
#include "Cohorts.h"



namespace sim {
namespace cs {


class DiscreteSimLocation
{
// Constructors and Initializers
public:
  DiscreteSimLocation( const input::Location * location, boost::gregorian::date startDate, boost::gregorian::date stopDate, const output::PopData * popData = NULL );
  ~DiscreteSimLocation(void);

// Initializers
private:
  void InitializeControls( input::ControlCollection controls );
  void InitializeBiology( input::Biology * biology );
  void InitializePopulation( const output::PopData * population );

  void AddContainer( input::Container * container );
  void AddPopContainer( input::Container * container, const sim::output::PopData * population );

// Methods
public:
  void RunSimulation(void);
  output::CimsimOutput * GetSimOutput(void);

private:
  void DoYear(void);

  void ReadWeather(int year);

  void CalculateAdultTemperatureSurvival(void);
  void CalculateAdultSatDefSurvival(void);
  double CalculateAdultAgeDependentSurvival( int age );

  double GetNulliparousCount(void);
  double GetParousCount(void);
  double GetFemaleAverageWeight(void);

  std::pair<double,double> GetOvipositingTotals(void);
  // deprecated - removed once new adult aging system in place in DENSiM
  double GetOvipositingFemaleAverageWeight(void);

  double GetNulliparousBiters(void);
  double GetParousBiters(void);
  double CalculateDoubleBloodMealProportion( double weight );

  void CalculateDailyTotals(void);
  void UpdateOutput( boost::gregorian::date d, double adultDev, double newEggs );

  output::PopData * GeneratePopData(void);

// Helpers
private:
  static bool IsEndOfMonth( boost::gregorian::date d );

private:
  const input::Location * _location;

  output::CimsimOutput * _output;
  bool _outputReleased;

  // time
  int Year;
  int Day;
  boost::gregorian::date _startDate;
  boost::gregorian::date _currentDate;
  boost::gregorian::date _stopDate;

  // pop data
  bool _usingPop;

  // containers
  typedef std::vector<DiscreteSimContainer*> ContainerCollection;
  ContainerCollection _containers;

  // controls
  input::ControlCollection _controls;
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
  PreOviAdultCohortCollection _initialPreOviAdults;
  OviAdultCohortCollection _initialOviAdults;

  // TODO deprecated - remove once changes replicated to DENSiM
  PreOviAdultCohortCollection _preOviAdults;
  OviAdultCohortCollection _oviAdults;
  AdultCohortCollection _ovipositingAdults;

  // adult population
  PreOviAdultCohortCollection _nulliparousAdults;
  OviAdultCohortCollection _parousAdults;

  PreOviAdultCohortCollection _ovipositingNulliparousAdults;
  OviAdultCohortCollection _ovipositingParousAdults;

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

  std::vector<double> _adultAgeDistribution;

  double _totalHostSeekingFemales;
  double _totalOvipositingFemales;

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
