#ifndef SIM_CS_CONTAINER_H
#define SIM_CS_CONTAINER_H

#include "SimClasses.h"
#include "Cohorts.h"
#include "../input/Location.h"
#include "../output/CimsimOutput.h"



namespace sim {
namespace csstoch {

double DevelopmentRate( double p25, double tempt, double dha, double dh, double th2 );



class SimContainer
{
public:
  SimContainer( const input::Container * container, const input::Biology * bio, output::ContainerPopData * containerPopData = NULL );
  ~SimContainer(void);

public:
  output::ContainerPopData * GeneratePopData(void);
  void MakeClone( int cloneId, int numClones, double newDensity );

  void Initialize( boost::gregorian::date startDate );
  void InitializeYear( int year );
  void InitializeEggs(void);

  void DoDay( boost::gregorian::date currentDate );

public:
  void CalculateWaterDepth( double todaysRain, double relHumid );
  void CalculateWaterTemperature( double minAirTemp, double avgAirTemp, double maxAirTemp );
  double MaxWaterTempRegression( double minAirTemp, double maxAirTemp );
  double MinWaterTempRegression( double minAirTemp, double maxAirTemp );
  void CalculateDevelopmentRates( int day );

  void ApplyMonthlyDensityAdjustment(void);
  void ApplySourceReduction( double rateOfReduction );
  void RecoverExcluded(void);
  double GetTotalExcludedDensity(void);
  void ApplyOvipositionExclusion( double rateOfExclusion, double rateOfRecovery );
  void RecoverTreated(void);
  void BeginNewLarvicideTreatment( input::Larvicide * li );
  void ApplyEggDestruction( double rateOfDestruction );

  void CalculateSaturationDeficitEggSurvival( int day, double satDef );
  void CalculateTemperatureEggSurvival( int day );
  void CalculatePredationEggSurvival( int day );
  void CalculateCumulativeEggSurvival(void);
  void AdvanceEggs( int day );

  void ApplyDryContainerToNewLarvae( int day );
  void AdjustFood( boost::gregorian::date curentDate );
  void CalculateTemperatureLarvalSurvival( int day );
  void CalculateLarvicideLarvalSurvival( boost::gregorian::date d );
  void CalculateWaterDepthLarvalSurvival( int day );
  void CalculateLarvalFoodConsumptionAndWeight( int day, int eulerSteps );
  double FoodEqn( double nt, double WT, double FT, double et );
  double WeightEqn( double WT, double FT, double et );
  void AdvanceLarvae( int day );
  void ApplyGeneticPupationDeath( int day );

  void HatchEggs( int day );

  void CalculateTemperaturePupalSurvival( int day );
  void AdvancePupae();
  
  void SelectFemales(void);
  double CalculateDensityAdjustedNewFemaleWeight(void);
  double CalculateDensityAdjustedNewFemaleCount(void);

  double GetNewFemaleCount(void);
  double GetEmergedPupaeAverageWeight(void);
  double GetUntreatedDensity(void);
  double GetTreatedDensity(void);

  bool IsDry(void);
  double GetWaterVolume(void);
  double GetCapacityVolume(void);
  double GetSurfaceArea(void);

  void ResetContPref(void);
  double CalculateContPref( int day );
  void NormalizeContPref( double normTotal );
  double GetOvipositionPreference(void);

  void CalculateEggInputLevel( int day );
  double DistributeNewEggs( double totalNewEggs );

  void CalcDailyTotals();

  void EndDay(void);
  void EndYear(void);

  output::DailyContainerOutput GetOutput( boost::gregorian::date d );

public:
  std::string Name;                   // name
  int Id;                             // type id
  input::Container::ShapeType Shape;  // shape

  double Height;                      // container height (cm)
  double Diameter;                    // container diameter (cm) - 0 if rectangular
  double Length;                      // container length (cm) - 0 if circular
  double Wide;                        // container width (cm) - 0 if circular
  double WatershedRatio;              // watershed ratio

  double Density;                     // density in # / ha
  double Loss;                        // rate at which containers are lost/recovered each month

  double Exposure;                    // exposure to sun
  double CoolingEffect;               // evaporative cooling effect on water temperature

  input::Container::Fill FillMethod;  // manual or rain fill
  double Drawdown;                    // drawdown in liters

  input::Container::Frequency DrawdownFrequency;      // daily, weekly, or monthly drawdown
  input::Container::Frequency ManualFillFrequency;    // daily, weekly, or monthly manual fill

  bool IsCovered;               // if container is covered
  double CoverRed;              // reduction in evaporative loss from cover

  double InitialEggs;                                                       // initial number of eggs
  double InitFood;                                                          // initial amount of food
  double FoodDecayRate;                                                     // daily rate of decay of food
  std::map<boost::gregorian::months_of_year, double> MonthlyFoodAdditions;  // daily food additions by month
  double _foodAddition;
  double _foodConsumption;

  bool IsCloned;                // container clone status
  int CloneId;                  // clone id within type id
  int NumberOfClones;           // number of clones within type

  // used for cloned hydrology
  boost::gregorian::date_period _nextDrawdownPeriod;      // period in which next drawdown should take place
  boost::gregorian::date _nextDrawdown;                   // date for next drawdown

  boost::gregorian::date_period _nextManualFillPeriod;    // period in which next manual fill should take place
  boost::gregorian::date _nextManualFill;                 // date for next manual fill

private:
  // current date in simulation
  boost::gregorian::date _currentDate;

  // water level
  double _waterDepth;
  double _waterDepthYesterday;

  // food
  double _foodAvailable;
  double _foodRemainingYesterday;

  // current water temperatures
  double _minimumWaterTemperature;
  double _averageWaterTemperature;
  double _maximumWaterTemp;

  // previous water temperatures
  std::list<double> _previousMinWaterTemperatures;
  std::list<double> _previousMaxWaterTemperatures;

  // food delivery method
  bool _usingRandomFood;
  boost::gregorian::date _previousFoodAdditionDate;

  // density types
  double _untreatedDensity;
  double _treatedDensity;
  std::vector<ExcludedDensity> _excludedDensities;

  // eggs
  EggBandCollection EggCohorts;

  double _newEggCount;
  double _embryonatingEggCount;
  double _matureEggCount;

  double _eggDevRate;
  double _eggDevRO25;
  double _eggDevDHA;
  double _eggDevDHH;
  double _eggDevTHALF;

  double _eggSurvival;
  double _eggNominalSurvival;
  double _eggTemperatureSurvival;
  double _eggSatDefSurvival;
  double _eggPredationSurvival;
  double _eggDestructionSurvival;

  double _eggSatDefWetSurvival;
  double _eggSatDefHighSunExposureThreshold;
  double _eggSatDefHighSunExposureSurvival;
  double _eggSatDefHighThreshold;
  double _eggSatDefLowThreshold;
  double _eggSatDefHighSurvival;
  double _eggSatDefLowSurvival;

  double _eggTemperatureLowLethalSurvival;
  double _eggTemperatureLowLethalThreshold;
  double _eggTemperatureLowThreshold;
  double _eggTemperatureHighThreshold;
  double _eggTemperatureHighLethalThreshold;
  double _eggTemperatureHighLethalSurvival;

  double _eggPredationLowThreshold;
  double _eggPredationHighThreshold;
  double _eggPredationLowSurvival;
  double _eggPredationHighSurvival;

  static const int _eggBandWidth = 2;
  int _maxEggBand;
  int _hatchBand;
  int _ovipositionBand;

  double _eggFloodHatchRatio;
  double _eggSpontaneousHatchRatio;
  double _eggMinimumHatchTemperature;

  
  // cadavers
  double _cadavers;
  double _cadaverFoodRatio;


  // larvae
  LarvaeCohortCollection LarvaeCohorts;

  double _totalLarvae;
  double _totalLarvaeFasting;
  double _totalLarvaeDeathFromFasting;

  double _newlyHatched;
  double _larvaeInitialWeight;
  double _larvaeMaxWeight;
  double _larvaeCadaverWeight;

  double _larvaeDevRate;
  double _larvaeDevRO25;
  double _larvaeDevDHA;
  double _larvaeDevDH;
  double _larvaeDevTHALF;
  double _larvaeMaximumDevelopment;

  double _larvaeTemperatureLowLethalSurvival;
  double _larvaeTemperatureLowLethalThreshold;
  double _larvaeTemperatureLowThreshold;
  double _larvaeTemperatureHighThreshold;
  double _larvaeTemperatureHighLethalThreshold;
  double _larvaeTemperatureHighLethalSurvival;

  double _larvaeNoFastingSurvival;
  double _larvaeNoLipidReserveSurvival;
  double _larvaeLipidReserveSurvival;

  double _larvaeNominalSurvival;
  double _larvaeTemperatureSurvival;
  double _larvaePupationSurvival;
  double _larvaeLarvicideSurvival;

  double _larvaeDryContainerSurvival;

  LarvicideTreatment * _currentLarvicideTreatment;

  double et;
  double fT;

  double a;
  double b;
  double c;
  double d1;
  double d2;

  double _larvaeNonDeptableLipidReserve;
  double _larvaeWeightToLipidSlope;
  double _larvaeWeightToLipidConstant;

  double _larvaePupationWeightSlope;
  double _larvaePupationWeightIntercept;
  double _larvaeMinimumWeightForSurvival;
  double _larvaeMinimumWeightForPupation;


  // pupae
  PupaeCohortCollection PupaeCohorts;

  double _newPupae;
  double _totalPupae;
  double _pupaeWeight;
  double _averagePupaeWeight;
  double _pupaeCadaverWeight;

  double _pupaeDevRate;
  double _pupaeDevRO25;
  double _pupaeDevDHA;
  double _pupaeDevDHH;
  double _pupaeDevTHALF;

  double _pupaeTemperatureLowLethalSurvival;
  double _pupaeTemperatureLowLethalThreshold;
  double _pupaeTemperatureLowThreshold;
  double _pupaeTemperatureHighThreshold;
  double _pupaeTemperatureHighLethalThreshold;
  double _pupaeTemperatureHighLethalSurvival;

  double _pupaeTemperatureSurvival;
  double _pupaeNominalSurvival;

  double _pupaeEmergenceSuccess;
  double _pupaeFemaleEmergenceRatio;


  // adults
  double _newAdults;
  double _newFemales;
  double _cumulativeFemales;


  // oviposition
  double _ovipositionPreference;
};

};
};

#endif
