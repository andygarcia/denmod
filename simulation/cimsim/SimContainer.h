#ifndef SIM_CS_CONTAINER_H
#define SIM_CS_CONTAINER_H

#include "SimClasses.h"
#include "Cohorts.h"
#include "../input/Location.h"
#include "../output/CimsimOutput.h"



namespace sim {
namespace cs {

double DevelopmentRate( double p25, double tempt, double dha, double dh, double th2 );



class SimContainer
{
public:
  SimContainer( const input::Container * container, const input::Biology * bio, output::ContainerPopData * containerPopData = NULL );
  ~SimContainer(void);

public:
  output::ContainerPopData * GeneratePopData(void);

  void Initialize( boost::gregorian::date startDate );
  void InitializeYear( int year );
  void InitializeEggs(void);

  void DoDay( boost::gregorian::date currentDate );

public:
  void CalculateWaterDepth( double todaysRain, double relHumid );
  void CalculateWaterTemperature( double minAirTemp, double avgAirTemp, double maxAirTemp );
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
  double CalculateNewFemaleCountMovingAverage(void);

  bool IsDry(void);
  double GetWaterVolume(void);
  double GetCapacityVolume(void);
  double GetSurfaceArea(void);

  void ResetContPref(void);
  double CalculateContPref( int day );
  void NormalizeContPref( double normTotal );

  void CalculateEggInputLevel( int day );
  void DistributeNewEggs( double totalNewEggs );

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

  double InitialEggs;           // initial number of eggs

  double InitFood;                                                          // initial amount of food
  double FoodDecayRate;                                                     // daily rate of decay of food
  std::map<boost::gregorian::months_of_year, double> MonthlyFoodAdditions;  // daily food additions by month

private:
  // current date in simulation
  boost::gregorian::date CurrentDate_;

  // water level
  double WaterDepth;
  double WaterDepthYesterday;

  // food
  double FoodAvailable;
  double FoodRemainingYesterday;

  // current water temperatures
  double MinWaterTemp;
  double AvgWaterTemp;
  double MaxWaterTemp;

  // previous water temperatures
  std::list<double> PreviousMinWaterTemps;
  std::list<double> PreviousMaxWaterTemps;

  double MaxWaterTempRegression( double minAirTemp, double maxAirTemp );
  double MinWaterTempRegression( double minAirTemp, double maxAirTemp );

  // food delivery method
  bool UsingRandomFood;
  boost::gregorian::date PreviousFoodAdditionDate;

  // density types
  double UntreatedDensity;
  double TreatedDensity;
  std::vector<ExcludedDensity> ExcludedDensities;

  // eggs
  EggBandCollection EggCohorts;
  double NewEggCount;
  double EmbryonatingEggCount;
  double MatureEggCount;

  double EggsP25;
  double EggsDHa;
  double EggsDH;
  double EggsTh2;

  double eggwetsu;
  double eggdryth;
  double eggdrysu;
  double egghsdth;
  double egglsdth;
  double egghsdsu;
  double egglsdsu;

  double eggtemp1;
  double eggtemp2;
  double eggtemp3;
  double eggtemp4;

  double PredLT;
  double PredHT;
  double PredSurLT;
  double PredSurHT;

  double EggSurvNom;

  double EggSurvivalTemperature;
  double EggSurvivalSatDef;
  double EggSurvivalPredation;
  double EggSurvivalEggDestruction;

  double SurvEggs;
  double DevRateEggs;

  int MaxEggBand;
  static const int EggBandWidth = 2;

  int HatchBand;
  int OvipositionBand;

  double PropHatchflood;
  double PropHatchSpont;
  double eggdiapausetemp;


  // larvae
  LarvaeCohortCollection LarvaeCohorts;
  double TotalLarvae;

  double LarvP25;
  double LarvDHa;
  double LarvDH;
  double LarvTh2;

  double LarvTemp1;
  double LarvTemp2;
  double LarvTemp3;
  double LarvTemp4;

  double larvpwtsu;
  double larvnwtnfbsu;
  double larvnwtfbsu;

  double LarvaeSurvivalNominal;
  double LarvaeSurvivalTemperature;
  double LarvaeSurvivalLarvicide;
  LarvicideTreatment * CurrentLarvicideTreatment;

  double NewlyHatched;
  double LarvaeInitialWeight;

  double DevRateLarv;
  double MaxLarvWt;
  double LarvaeMaxCD;



  double et;
  double fT;

  double a;
  double b;
  double c;
  double d1;
  double d2;

  double cadavers;
  double LarvCadWt;
  double CadFoodEquiv;

  // Pupae
  PupaeCohortCollection PupaeCohorts;

  double NewPupae;
  double DevRatePupae;
  double PupaeWt;

  double TotalPupae;
  double AveragePupaeWeight;
  double PupCadWt;

  double PupaeP25;
  double PupaeDHa;
  double PupaeDH;
  double PupaeTh2;

  double PupTemp1;
  double PupTemp2;
  double PupTemp3;
  double PupTemp4;

  double pupgeneticsu;
  double PupSurvTempDlyCt;
  double PupSurvNom;

  double PupWtSlope;
  double PupWtConst;
  double PupMinWt;
  double PupMinAge;

  double EmergenceSuccess;
  double PercentFemale;

  // Adults
  double NewAdults;
  double NewFemales;
  double CumulativeFemales;

  // Oviposition
  double ContPref;
};

};
};

#endif
