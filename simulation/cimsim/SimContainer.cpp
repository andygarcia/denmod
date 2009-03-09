#include "StdAfx.h"
#include "SimContainer.h"
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace boost::gregorian;
using namespace sim::cs;



SimContainer::SimContainer( const input::Container * container, const input::Biology * bio, sim::output::ContainerPopData * containerPopData )
: Name(container->Name_),
  Id(container->Id_),
  Shape(container->Shape_),
  Length(container->Length_),
  Wide(container->Width_),
  Height(container->Height_),
  Diameter(container->Diameter_),
  WatershedRatio(container->WatershedRatio_),
  Density(container->Density_),
  Loss(container->MonthlyTurnoverRate_),
  IsCovered(container->IsCovered_),
  CoverRed(container->CoverReduction_),
  Exposure(container->SunExposure_),
  CoolingEffect(container->Cooling_),
  FillMethod(container->FillMethod_),
  Drawdown(container->Drawdown_),
  DrawdownFrequency(container->DrawdownFrequency_),
  ManualFillFrequency(container->ManualFillFrequency_),
  InitFood(container->InitFood_),
  MonthlyFoodAdditions(std::map<boost::date_time::months_of_year,double>()),
  FoodDecayRate(container->FoodDecayRate_),
  InitialEggs(container->InitEggs_),
  IsCloned(false),
  CloneId(0),
  NumberOfClones(0)
{
  // copy daily food additions by month
  MonthlyFoodAdditions[boost::date_time::Jan] = container->FoodGainJan_;
  MonthlyFoodAdditions[boost::date_time::Feb] = container->FoodGainFeb_;
  MonthlyFoodAdditions[boost::date_time::Mar] = container->FoodGainMar_;
  MonthlyFoodAdditions[boost::date_time::Apr] = container->FoodGainApr_;
  MonthlyFoodAdditions[boost::date_time::May] = container->FoodGainMay_;
  MonthlyFoodAdditions[boost::date_time::Jun] = container->FoodGainJun_;
  MonthlyFoodAdditions[boost::date_time::Jul] = container->FoodGainJul_;
  MonthlyFoodAdditions[boost::date_time::Aug] = container->FoodGainAug_;
  MonthlyFoodAdditions[boost::date_time::Sep] = container->FoodGainSep_;
  MonthlyFoodAdditions[boost::date_time::Oct] = container->FoodGainOct_;
  MonthlyFoodAdditions[boost::date_time::Nov] = container->FoodGainNov_;
  MonthlyFoodAdditions[boost::date_time::Dec] = container->FoodGainDec_;
  _usingRandomFood = bio->Larvae->Food->UseRandomFood;

  // initially all container density is considered untreated
  _untreatedDensity = this->Density;
  _treatedDensity = 0;

  // initially no larvicide treatments in effect
  _currentLarvicideTreatment = NULL;

  // determine maximum egg band
  _maxEggBand = static_cast<int>( ceil(this->Height / _eggBandWidth) );


  if( containerPopData != NULL ) {
    // initialize simulation with existing population
    EggCohorts = containerPopData->EggCohorts;

    LarvaeCohorts = containerPopData->LarvaeCohorts;
    _cadavers = containerPopData->Cadavers;
    _larvaeCadaverWeight = containerPopData->LarvaeCadaverWeight;

    PupaeCohorts = containerPopData->PupaeCohorts;
    _pupaeCadaverWeight = containerPopData->PupaeCadaverWeight;

    _waterDepthYesterday = containerPopData->Depth;
    _foodRemainingYesterday = containerPopData->Food;

    _untreatedDensity = containerPopData->UntreatedDensity;
    _treatedDensity = containerPopData->TreatedDensity;
    _excludedDensities = containerPopData->ExcludedDensities;
  }
  else {
    // food calcs for the first day of year require the initial food in container to be at "day zero"
    _waterDepthYesterday = 0;
    _foodRemainingYesterday = InitFood;

    // initialize egg cohort collection with all possible bands
    EggCohorts = EggBandCollection();
    for( int i = 1; i <= _maxEggBand; ++i ) {
      EggCohorts[i] = EggBand();
    }
  
    LarvaeCohorts = LarvaeCohortCollection();
    _larvaeCadaverWeight = 0;
    _cadavers = 0;

    PupaeCohorts = PupaeCohortCollection();
    _pupaeCadaverWeight = 0;
  }


  // read biology values
  _eggDevRO25 = bio->Egg->Development->RO25;
  _eggDevDHA = bio->Egg->Development->DHA;
  _eggDevDHH = bio->Egg->Development->DHH;
  _eggDevTHALF = bio->Egg->Development->THALF;

  _larvaeDevRO25 = bio->Larvae->Development->RO25;
  _larvaeDevDHA = bio->Larvae->Development->DHA;
  _larvaeDevDH = bio->Larvae->Development->DHH;
  _larvaeDevTHALF = bio->Larvae->Development->THALF;
  
  _pupaeDevRO25 = bio->Pupae->Development->RO25;
  _pupaeDevDHA = bio->Pupae->Development->DHA;
  _pupaeDevDHH = bio->Pupae->Development->DHH;
  _pupaeDevTHALF = bio->Pupae->Development->THALF;

  _eggSatDefWetSurvival = bio->Egg->SaturationDeficit->WetSurvival;
  _eggSatDefHighSunExposureThreshold = bio->Egg->SaturationDeficit->HighSunExposureThreshold;
  _eggSatDefHighSunExposureSurvival = bio->Egg->SaturationDeficit->HighSunExposureSurvival;
  _eggSatDefHighThreshold = bio->Egg->SaturationDeficit->HighThreshold;
  _eggSatDefLowThreshold = bio->Egg->SaturationDeficit->LowThreshold;
  _eggSatDefHighSurvival = bio->Egg->SaturationDeficit->HighSurvival;
  _eggSatDefLowSurvival = bio->Egg->SaturationDeficit->LowSurvival;

  _eggSpontaneousHatchRatio = bio->Egg->SpontaneousHatchRatio;
  _eggNominalSurvival = bio->Egg->NominalSurvival;

  _eggTemperatureLowLethalSurvival = bio->Egg->Temperature->LowLethalSurvival;
  _eggTemperatureLowLethalThreshold = bio->Egg->Temperature->LowLethalThreshold;
  _eggTemperatureLowThreshold = bio->Egg->Temperature->LowThreshold;
  _eggTemperatureHighThreshold = bio->Egg->Temperature->HighThreshold;
  _eggTemperatureHighLethalThreshold = bio->Egg->Temperature->HighLethalThreshold;
  _eggTemperatureHighLethalSurvival = bio->Egg->Temperature->HighLethalSurvival;
  
  _eggPredationLowThreshold = bio->Egg->Predation->LowThreshold;
  _eggPredationHighThreshold = bio->Egg->Predation->HighThreshold;
  _eggPredationLowSurvival = bio->Egg->Predation->LowSurvival;
  _eggPredationHighSurvival = bio->Egg->Predation->HighSurvival;

  _eggMinimumHatchTemperature = bio->Egg->MinimumHatchTemperature;
  _eggFloodHatchRatio = bio->Egg->FloodHatchRatio;

  _cadaverFoodRatio = bio->Larvae->CadaverFoodRatio;

  _larvaeNominalSurvival = bio->Larvae->NominalSurvival;
  _larvaeInitialWeight = bio->Larvae->WeightAtHatch;
  _larvaeMaximumDevelopment = bio->Larvae->PupationWeight->MaximumDevelopment;

  _larvaeDryContainerSurvival = bio->Larvae->DryContainerSurvival;

  _larvaeTemperatureLowLethalSurvival = bio->Larvae->Temperature->LowLethalSurvival;
  _larvaeTemperatureLowLethalThreshold = bio->Larvae->Temperature->LowLethalThreshold;
  _larvaeTemperatureLowThreshold = bio->Larvae->Temperature->LowThreshold;
  _larvaeTemperatureHighThreshold = bio->Larvae->Temperature->HighThreshold;
  _larvaeTemperatureHighLethalThreshold = bio->Larvae->Temperature->HighLethalThreshold;
  _larvaeTemperatureHighLethalSurvival = bio->Larvae->Temperature->HighLethalSurvival;

  a = bio->Larvae->Food->AssimilationRate;
  b = bio->Larvae->Food->ExploitationRate;
  c = bio->Larvae->Food->ExploitationRateIndependence;
  d1 = bio->Larvae->Food->MetabolicWeightLossRate;
  d2 = bio->Larvae->Food->MetabolicWeightLossExponent;
  // chronological basis from 1993 Focks, et. al.
  fT = .001f;

  _larvaeNonDeptableLipidReserve = bio->Larvae->Fasting->NonDepletableLipidReserve;
  _larvaeWeightToLipidSlope = bio->Larvae->Fasting->WeightToLipidSlope;
  _larvaeWeightToLipidConstant = bio->Larvae->Fasting->WeightToLipidConstant;

  _larvaeNoFastingSurvival = bio->Larvae->Fasting->NoFastingSurvival;
  _larvaeNoLipidReserveSurvival = bio->Larvae->Fasting->NoLipidReserveSurvival;
  _larvaeLipidReserveSurvival = bio->Larvae->Fasting->LipidReserveSurvival;

  _larvaePupationSurvival = bio->Larvae->PupationSurvival;
  _larvaePupationWeightSlope = bio->Larvae->PupationWeight->Slope;
  _larvaePupationWeightIntercept = bio->Larvae->PupationWeight->Intercept;
  _larvaeMinimumWeightForPupation = bio->Larvae->PupationWeight->MinimumWeightForPupation;
  _larvaeMinimumWeightForSurvival = bio->Larvae->MinimumWeightForSurvival;

  _pupaeNominalSurvival = bio->Pupae->NominalSurvival;

  _pupaeTemperatureLowLethalSurvival = bio->Pupae->Temperature->LowLethalSurvival;
  _pupaeTemperatureLowLethalThreshold = bio->Pupae->Temperature->LowLethalThreshold;
  _pupaeTemperatureLowThreshold = bio->Pupae->Temperature->LowThreshold;
  _pupaeTemperatureHighThreshold = bio->Pupae->Temperature->HighThreshold;
  _pupaeTemperatureHighLethalThreshold = bio->Pupae->Temperature->HighLethalThreshold;
  _pupaeTemperatureHighLethalSurvival = bio->Pupae->Temperature->HighLethalSurvival;
  
  _pupaeEmergenceSuccess = bio->Pupae->EmergenceSurvival;
  _pupaeFemaleEmergenceRatio = bio->Pupae->FemaleEmergence;
}



SimContainer::~SimContainer(void)
{
}



void
SimContainer::MakeClone( int cloneId, int numOfClones, double newDensity )
{
  this->IsCloned = true;
  this->CloneId = cloneId;
  this->NumberOfClones = numOfClones;

  this->Density = newDensity;
  this->_untreatedDensity = newDensity;
}



void
SimContainer::Initialize( date startDate )
{
  // set previous food addition date
  _previousFoodAdditionDate = startDate - days(3);

  // clear total productivity
  _cumulativeFemales = 0;
}



void
SimContainer::InitializeYear( int year )
{
  _eggDestructionSurvival = 1;
  _cadavers = 0;
}



void
SimContainer::InitializeEggs(void)
{
  _ovipositionBand = static_cast<int>( ceil(_waterDepth / _eggBandWidth) );

  if( _ovipositionBand == 0 ) {
    // only true when container is dry, oviposition should still occur in the first band
    _ovipositionBand = 1;
  }

  // insert initial eggs
  EggCohorts[_ovipositionBand].MatureEggs = this->InitialEggs;
}



void
SimContainer::DoDay( boost::gregorian::date currentDate )
{
  _currentDate = currentDate;
}



void
SimContainer::CalculateWaterDepth( double todaysRain, double relHumid )
{
  double currentDepth;

  // rain adjusted for watershed ratio
  double waterGain = todaysRain * WatershedRatio;

  double coverEffect;
  if( !IsCovered ) {
    coverEffect = 1;
  }
  else {
    coverEffect = 1 - CoverRed;
  }

  
  // possible drawdown
  double heightDrawdown = 0.0;
  if( Drawdown != 0 ) {
    bool drawdownToday = false;

    // depending on specified frequency, drawdown occurs:
    if( DrawdownFrequency == input::Container::Daily ) {
      // every day for daily frequency
      drawdownToday = true;
    }
    else if( DrawdownFrequency == input::Container::Weekly && _currentDate.day_of_week() == boost::date_time::Thursday ) {
      // on thursday for weekly frequencies
      drawdownToday = true;
    }
    else if( DrawdownFrequency == input::Container::Monthly && _currentDate.day() == 14 ) {
      // on the 14th for monthly frequencies
      drawdownToday = true;
    }

    // calculate drawdown if scheduled to occur, converting from liters to cm
    if( drawdownToday ) {
      if( Shape == input::Container::Rectangle ) {
        heightDrawdown = (Drawdown * 1000) / (Length * Wide);
      }
      else if( Shape == input::Container::Circle ) {
        heightDrawdown = (Drawdown * 1000) / (3.141593f * pow(Diameter/2, 2));
      }
    }
  }

  // evaporative loss
  double evaporation = .925636f + (.275191f * Exposure) - (.009041f * relHumid);

  // total water loss is evaporation (adjusted for cover) and draw down
  double waterLoss = (evaporation * coverEffect) + heightDrawdown;


  double yestDepth = _waterDepthYesterday;
  if( (yestDepth - waterLoss) < 0 )
    currentDepth = 0;
  else
    currentDepth = yestDepth - waterLoss;

  currentDepth = currentDepth + waterGain;
  if( currentDepth > Height )
    currentDepth = Height;

  _waterDepth = currentDepth;

  // check for manual fill
  if( FillMethod == input::Container::ManualFill ) {

    // daily fills
    if( ManualFillFrequency == input::Container::Daily ) {
      _waterDepth = Height;
    }

    // weekly fills occur at beginning of week
    if( ManualFillFrequency == input::Container::Weekly ) {
      if( _currentDate.day_of_week() == boost::date_time::Sunday ) {
        _waterDepth = Height;
      }
    }

    // monthly fills occur at beginning of month
    if( ManualFillFrequency == input::Container::Monthly ) {
      if( _currentDate.day() == 1 ) {
        _waterDepth = Height;
      }
    }
  }
}



void
SimContainer::CalculateWaterTemperature( double minAirTemp, double avgAirTemp, double maxAirTemp )
{
  if( _waterDepth <= 0 ) {
    // container empty, use today's air temps for container enviroment
    _minimumWaterTemperature = minAirTemp;
    _averageWaterTemperature = avgAirTemp;
    _maximumWaterTemp = maxAirTemp;

    // container loses any thermal inertia
    _previousMinWaterTemperatures.clear();
    _previousMaxWaterTemperatures.clear();
  }
  else {
    // first calculate today's water temperatures
    double todayMinTemp = MinWaterTempRegression( minAirTemp, maxAirTemp );
    double todayMaxTemp = MaxWaterTempRegression( minAirTemp, maxAirTemp );


    // determine how many days average are required according to current volume
    double waterVolume = GetWaterVolume();

    int numDaysRequired;
    if( waterVolume > 500 )
      numDaysRequired = 4;
    if( 100 <= waterVolume && waterVolume <= 500 )
      numDaysRequired = 3;
    if( 5 <= waterVolume && waterVolume < 100 )
      numDaysRequired = 2;
    if( waterVolume < 5 ) {
      numDaysRequired = 1;
    }


    // update history, if stacks are full, pop
    while( _previousMinWaterTemperatures.size() >= (unsigned int) numDaysRequired ) {
      _previousMinWaterTemperatures.pop_front();
    }
    while( _previousMaxWaterTemperatures.size() >= (unsigned int) numDaysRequired ) {
      _previousMaxWaterTemperatures.pop_front();
    }

    // push today's calculated temps
    _previousMinWaterTemperatures.push_back( todayMinTemp );
    _previousMaxWaterTemperatures.push_back( todayMaxTemp );

    int numDaysAvailable = static_cast<int>(_previousMinWaterTemperatures.size());

    // now perform average
    double minSum = std::accumulate( _previousMinWaterTemperatures.begin(), _previousMinWaterTemperatures.end(), 0.0 );
    double maxSum = std::accumulate( _previousMaxWaterTemperatures.begin(), _previousMaxWaterTemperatures.end(), 0.0 );

    _minimumWaterTemperature = minSum / numDaysAvailable;
    _maximumWaterTemp = maxSum / numDaysAvailable;

    _averageWaterTemperature = (_minimumWaterTemperature + _maximumWaterTemp) / 2.0;
  }
}



double
SimContainer::MinWaterTempRegression( double minAirTemp, double maxAirTemp )
{
  double minTemp;
  
  minTemp = (5.019385f - (1.363636f * Exposure) + (.807682f * minAirTemp) + (.000982f * pow(maxAirTemp,2)));

  return minTemp;
}



double
SimContainer::MaxWaterTempRegression( double minAirTemp, double maxAirTemp )
{
  double maxTemp;

  maxTemp = (15.033426 + (.266995 * minAirTemp) + (.007053 * pow(maxAirTemp,2)) + (7.685039 * pow(Exposure,2)));

  // evaporative cooling
  maxTemp = maxTemp * (1 - CoolingEffect);

  return maxTemp;
}



void
SimContainer::CalculateDevelopmentRates( int day )
{
  static double DevRateLarv26 = DevelopmentRate( _larvaeDevRO25, 26 + 273.15, _larvaeDevDHA, _larvaeDevDH, _larvaeDevTHALF );
  static double DevRateLarv134 = DevelopmentRate( _larvaeDevRO25, 13.4 + 273.15, _larvaeDevDHA, _larvaeDevDH, _larvaeDevTHALF );

  _eggDevRate = DevelopmentRate( _eggDevRO25, _averageWaterTemperature + 273.15f, _eggDevDHA, _eggDevDHH, _eggDevTHALF );
  _larvaeDevRate = DevelopmentRate( _larvaeDevRO25, _averageWaterTemperature + 273.15f, _larvaeDevDHA, _larvaeDevDH, _larvaeDevTHALF );

  // et places food/weight calculations on a chronological basis with temperature
  // food/weight functions shutdown below 13.4 degrees celsius
  if( _averageWaterTemperature <= 13.4f ) {
    et = 0;
  }
  else {
    et = (_larvaeDevRate - DevRateLarv134) / (DevRateLarv26 - DevRateLarv134);
  }

  _pupaeDevRate = DevelopmentRate(_pupaeDevRO25, _averageWaterTemperature + 273.15f, _pupaeDevDHA, _pupaeDevDHH, _pupaeDevTHALF );
}



double
sim::cs::DevelopmentRate( double p25, double tempt, double dha, double dh, double th2 )
{
  static double r = 1.987;

  double tempexpr1 = (dha / r) * (((double)1 / 298) - (1 / tempt));
  double tempexpr2 = (dh / r) * ((1 / th2) - (1 / tempt));

  if( tempexpr1 < -100 ) {
    tempexpr1 = -100;
  }
  else {
    if (tempexpr1 > 150) {
      tempexpr1 = 150;
    }
  }
  if( tempexpr2 < -100 ) {
    tempexpr2 = -100;
  }
  else {
    if (tempexpr2 > 150) {
      tempexpr2 = 150;
    }
  }

  double numerator = p25 * (tempt / 298) * exp(tempexpr1);
  double denominator = 1 + exp(tempexpr2);
  double DevelopmentRate = numerator / denominator * 24;

  return DevelopmentRate;
}



void
SimContainer::ApplyMonthlyDensityAdjustment(void)
{
  double ContainerLoss = _untreatedDensity * Loss;
  double ContainerGain = Density * Loss;
  _untreatedDensity = _untreatedDensity - ContainerLoss + ContainerGain;
}



void
SimContainer::ApplySourceReduction( double rateOfReduction )
{
  double numContainersRemoved = _untreatedDensity * rateOfReduction;
  _untreatedDensity = _untreatedDensity - numContainersRemoved;
}



void
SimContainer::RecoverExcluded(void)
{
  if( _excludedDensities.size() == 0 ) {
    // nothing to recover
    return;
  }

  std::vector<ExcludedDensity>::iterator itExcluded;
  for( itExcluded = _excludedDensities.begin(); itExcluded != _excludedDensities.end(); ++itExcluded ) {
    // apply recovery and loss to each excluded Density and move recovered back to untreated Density
    double numRecovered = itExcluded->Density * itExcluded->RateOfRecovery;
    double numMonthlyLoss = itExcluded->Density * this->Loss;
    itExcluded->Density = itExcluded->Density - numRecovered - numMonthlyLoss;
    _untreatedDensity = _untreatedDensity + numRecovered;
  }
}



double
SimContainer::GetTotalExcludedDensity(void)
{
  double totalExcluded = 0;
  std::vector<ExcludedDensity>::iterator itExcluded;
  for( itExcluded = _excludedDensities.begin(); itExcluded != _excludedDensities.end(); ++itExcluded ) {
    totalExcluded += itExcluded->Density;
  }
  return totalExcluded;
}



void
SimContainer::ApplyOvipositionExclusion( double rateOfExclusion, double rateOfRecovery )
{
  double numExcluded = _untreatedDensity * rateOfExclusion;
  _untreatedDensity = _untreatedDensity - numExcluded;

  ExcludedDensity ed;
  ed.Density = numExcluded;
  ed.RateOfRecovery = rateOfRecovery;

  _excludedDensities.push_back(ed);
}



void
SimContainer::RecoverTreated(void)
{
  if( _treatedDensity == 0 ) {
    // no treated containers to recover
    return;
  }

  if( _currentLarvicideTreatment->InEffect ) {
    // treatment(s) in progress, do apply monthly loss however
    double numMonthlyLoss = _treatedDensity * this->Loss;
    _treatedDensity = _treatedDensity - numMonthlyLoss;
    _untreatedDensity = _untreatedDensity + numMonthlyLoss;
  }
  else {
    // if all treatments have expired, add this density back to untreated
    _untreatedDensity = _untreatedDensity + _treatedDensity;

    // clear treated density and current treatment
    _treatedDensity = 0;
    delete _currentLarvicideTreatment;
    _currentLarvicideTreatment = NULL;
  }
}



void
SimContainer::BeginNewLarvicideTreatment( input::Larvicide * li )
{
  // find treatment rate
  double rateOfTreatment = li->GetTargetParams(this->Name)->RateOfTreatment;

  // determine new densities, since a treatment was previously in effect,
  // or treated containers from an expired treatment have not been recovered,
  // the rate of treatment is considered to be applied to both untreated and
  // currently treated containers, or all non excluded containers
  double currentTreatedDensity = _treatedDensity;
  double nonExcludedDensity = _untreatedDensity + _treatedDensity;
  double treatmentDensity = rateOfTreatment * nonExcludedDensity;
  double additionalDensity = treatmentDensity - currentTreatedDensity;

  // update densities
  _treatedDensity += additionalDensity;
  _untreatedDensity -= additionalDensity;

  // delete previous treatment
  if( _currentLarvicideTreatment != NULL ) {
    delete _currentLarvicideTreatment;
  }

  // new treatment
  _currentLarvicideTreatment = new LarvicideTreatment( li, _currentDate );
}



void
SimContainer::ApplyEggDestruction( double rateOfDestruction )
{
  _eggDestructionSurvival = 1 - rateOfDestruction;
}



void
SimContainer::CalculateSaturationDeficitEggSurvival( int day, double satDef )
{
  if( _waterDepth == 0 ) {
    if( Exposure > this->_eggSatDefHighSunExposureThreshold ) {
      _eggSatDefSurvival = _eggSatDefHighSunExposureSurvival;
    }
    else {
      if( satDef <= _eggSatDefLowThreshold ) {
        _eggSatDefSurvival = _eggSatDefLowSurvival;
      }
      else if( satDef >= _eggSatDefHighThreshold ) {
        _eggSatDefSurvival = _eggSatDefHighSurvival;
      }
      else {
        double eggsdslope = (_eggSatDefLowSurvival - _eggSatDefHighSurvival) / (_eggSatDefHighThreshold - _eggSatDefLowThreshold);
        _eggSatDefSurvival = _eggSatDefLowSurvival - ((satDef - _eggSatDefLowThreshold) * eggsdslope);
      }
    }
  }
  else {
    _eggSatDefSurvival = _eggSatDefWetSurvival;
  }
}



void
SimContainer::CalculateTemperatureEggSurvival( int day )
{
  if( _minimumWaterTemperature <= _eggTemperatureLowLethalThreshold ) {
    _eggTemperatureSurvival = _eggTemperatureLowLethalSurvival;
  }
  else if( _minimumWaterTemperature >= _eggTemperatureLowThreshold ) {
    _eggTemperatureSurvival = 1;
  }
  else {
    double slope = (1 - _eggTemperatureLowLethalSurvival) / (_eggTemperatureLowLethalThreshold - _eggTemperatureLowThreshold);
    _eggTemperatureSurvival = 1 + ((_eggTemperatureLowThreshold - _minimumWaterTemperature) * slope);
  }

  if( _maximumWaterTemp >= _eggTemperatureHighLethalThreshold ) {
    _eggTemperatureSurvival = _eggTemperatureSurvival * _eggTemperatureHighLethalSurvival;
  }
  else if( _maximumWaterTemp <= _eggTemperatureHighThreshold ) {
    _eggTemperatureSurvival = _eggTemperatureSurvival * 1;
  }
  else {
    double egghtempslope = (1 - _eggTemperatureHighLethalSurvival) / (_eggTemperatureHighThreshold - _eggTemperatureHighLethalThreshold);
    _eggTemperatureSurvival = _eggTemperatureSurvival * (1 + ((_maximumWaterTemp - _eggTemperatureHighThreshold) * egghtempslope));
  }
}



void
SimContainer::CalculatePredationEggSurvival( int day )
{
  if( _averageWaterTemperature <= _eggPredationLowThreshold ) {
    _eggPredationSurvival = _eggPredationLowSurvival;
  }
  else if( _averageWaterTemperature >= _eggPredationHighThreshold ) {
    _eggPredationSurvival = _eggPredationHighSurvival;
  }
  else {
    double Slope = (_eggPredationLowSurvival - _eggPredationHighSurvival) / (_eggPredationHighThreshold - _eggPredationLowThreshold);
    _eggPredationSurvival = _eggPredationLowSurvival - ((_averageWaterTemperature - _eggPredationLowThreshold) * Slope);
  }
}



void
SimContainer::CalculateCumulativeEggSurvival(void)
{
  _eggSurvival = _eggSatDefSurvival * _eggTemperatureSurvival * _eggNominalSurvival * _eggPredationSurvival * _eggDestructionSurvival;
}



void
SimContainer::AdvanceEggs( int day )
{
  _hatchBand = static_cast<int>(ceil( _waterDepth / _eggBandWidth ));

  _newlyHatched = 0;
  for( EggBandIterator itBand = EggCohorts.begin(); itBand != EggCohorts.end(); ++itBand ) {
    // current band iteration
    int currentBand = itBand->first;
    EggBand * eggBand = &(itBand->second);

    // process mature cohorts
    eggBand->MatureEggs = eggBand->MatureEggs * _eggSurvival;

    // new develompent threshold target, using a variable CDt calculation based on today's development
    // instead of compensating for simulation's discrete development over the course of a day by making the threshold 0.95
    // (slightly less than 1.0), we subtract half of today's development from 1.0,
    // the new target is always (1 - D(t)/2)
    double targetThreshold = 1.0 - (_eggDevRate / 2.0);

    // process immature cohorts
    for( EggIterator itEgg = eggBand->EggCohorts.begin(); itEgg != eggBand->EggCohorts.end();  ) {
      if( itEgg->Development <= targetThreshold ) {
        itEgg->Age++;
        itEgg->Number = itEgg->Number * _eggSurvival;
        itEgg->Development = itEgg->Development + _eggDevRate;

        if( itEgg->Number <= 0  || itEgg->Age == MaxAgeEggs ) {
          // all dead or max age, remove from band
          itEgg = eggBand->EggCohorts.erase( itEgg );
        }
        else {
          ++itEgg;
        }
        continue;
      }
      else {
        if( _averageWaterTemperature < _eggMinimumHatchTemperature ) {
          eggBand->MatureEggs = eggBand->MatureEggs + (itEgg->Number * _eggSurvival);
        }
        else {
          if( currentBand <= _hatchBand ) {
            // band flooded, all eggs hatch
            _newlyHatched += (itEgg->Number * _eggSurvival);
          }
          else {
            // band not flooded, some proportion hatch spontaneously, rest become mature eggs
            eggBand->MatureEggs += ((1 - _eggSpontaneousHatchRatio) * itEgg->Number * _eggSurvival);
            _newlyHatched += (_eggSpontaneousHatchRatio * itEgg->Number * _eggSurvival);
          }
        }

        // whether flooded or not, remove this immature cohort (now mature)
        itEgg = eggBand->EggCohorts.erase( itEgg );
        continue;
      }
    } // age
  } // band
}



void
SimContainer::ApplyDryContainerToNewLarvae( int day )
{
  if( _waterDepth == 0 ) {
    _newlyHatched = 0;
  }
}



void
SimContainer::AdjustFood( date currentDate )
{
  // find addition parameter for current month
  double foodAddition = this->MonthlyFoodAdditions[currentDate.month().as_enum()];

  // apply decay to yesterday's food
  double naturalDecay = _foodRemainingYesterday * FoodDecayRate;
  double yesterdayFood = _foodRemainingYesterday - naturalDecay;
  if( yesterdayFood < 0 ) {
    yesterdayFood = 0;
  }

  // calculate actual food addition, if any
  if( _usingRandomFood ) {
    // between 0-2 times the daily amount, every day
    double rndFactor = (double) rand()/RAND_MAX * 2;
    foodAddition = foodAddition * rndFactor;
  }
  else {
    // fixed delivery every 3 days
    if( currentDate == _previousFoodAdditionDate + days(3) ) {
      // 3 times daily addition
      foodAddition = 3 * foodAddition;

      // update previous day for next 3 day interval
      _previousFoodAdditionDate = currentDate;
    }
    else {
      // no addition yet, still within 3 day interval
      foodAddition = 0;
    }
  }

  // save food addition for output
  _foodAddition = foodAddition;

  // today's food = yesterday's food + addition (if any) + _cadavers
  _foodAvailable = yesterdayFood + foodAddition + _cadavers;
}



void
SimContainer::CalculateTemperatureLarvalSurvival( int day )
{
  // survival from minimum temperatures
  if( _minimumWaterTemperature <= _larvaeTemperatureLowLethalThreshold ) {
    _larvaeTemperatureSurvival = _larvaeTemperatureLowLethalSurvival;
  }
  else if( _minimumWaterTemperature >= _larvaeTemperatureLowThreshold ) {
    _larvaeTemperatureSurvival = 1.0;
  }
  else {
    double slope = (_larvaeTemperatureLowLethalSurvival - 1.0f) / (_larvaeTemperatureLowLethalThreshold - _larvaeTemperatureLowThreshold);
    _larvaeTemperatureSurvival = 1 - ((_larvaeTemperatureLowThreshold - _minimumWaterTemperature) * slope);
  }

  // survival from maximum temperatures
  if( _maximumWaterTemp >= _larvaeTemperatureHighLethalThreshold ) {
    _larvaeTemperatureSurvival = _larvaeTemperatureSurvival * _larvaeTemperatureHighLethalSurvival;
  }
  else if( _maximumWaterTemp <= _larvaeTemperatureHighThreshold ) {
    _larvaeTemperatureSurvival = _larvaeTemperatureSurvival * 1;
  }
  else {
    double LarSlope = (1 - _larvaeTemperatureHighLethalSurvival) / (_larvaeTemperatureHighThreshold - _larvaeTemperatureHighLethalThreshold);
    _larvaeTemperatureSurvival = _larvaeTemperatureSurvival * (1 + ((_maximumWaterTemp - _larvaeTemperatureHighThreshold) * LarSlope));
  }
}



void
SimContainer::CalculateLarvicideLarvalSurvival( date d )
{
  if( _currentLarvicideTreatment != NULL ) {
    if( _currentLarvicideTreatment->InEffect ) {
      // first check for effect loss if dry
      if( _currentLarvicideTreatment->LoseOnDry && this->IsDry() ) {
        _currentLarvicideTreatment->InEffect = false;
      }

      // find mortality for today, and its inverse survival
      double mortality = _currentLarvicideTreatment->Mortality[d];
      _larvaeLarvicideSurvival = 1.0 - mortality;

      // if tomorrow is not in mortality map, treatment period and effect is over
      if( !_currentLarvicideTreatment->IsDateInTreatmentPeriod(d + days(1)) ) {
        _currentLarvicideTreatment->InEffect = false;
      }
    }
  }
  else {
    // no treatments in effect, full survival
    _larvaeLarvicideSurvival = 1.0;
  }
}



void
SimContainer::CalculateWaterDepthLarvalSurvival( int day )
{
  // not 0.0 because of non-uniformity of surface of container bottom
  if( _waterDepth == 0 )
    _larvaeTemperatureSurvival = _larvaeDryContainerSurvival;
}



void
SimContainer::CalculateLarvalFoodConsumptionAndWeight( int day, int eulerSteps )
{
  // clear today's weight changes
  for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ++itLarvae ) {
    itLarvae->WeightChange = 0;
  }

  
  // track total consumption for output
  _foodConsumption = 0.0;

  for( int i = 1; i <= eulerSteps; ++i ) {
    for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ++itLarvae ) {
      // calculate larvae food/weight
      double cohortFoodConsumption = FoodEqn( itLarvae->Number, (itLarvae->Weight + itLarvae->WeightChange), _foodAvailable, et ) * (2880 / (double)eulerSteps);
      double cohortWeightChange = WeightEqn( (itLarvae->Weight + itLarvae->WeightChange), _foodAvailable, et ) * (2880 / (double)eulerSteps);

      // update container food after each cohort feeds, not just after each Euler step
      _foodAvailable += cohortFoodConsumption;
      if( _foodAvailable < 0 ) {
        _foodAvailable = 0;
      }

      // note that FoodEqn returns food consumption as a negative value (i.e. the decrease in available food)
      // we can subtract this directory from our food value for this container, but to track total consumption
      // requires inverting the sign
      _foodConsumption += (0 - cohortFoodConsumption);

      // update cohort weight with step change in weight
      itLarvae->WeightChange += cohortWeightChange;
    }
  }
}



double SimContainer::FoodEqn( double nt, double WT, double FT, double et )
{
// Larval consumption of food
//
// FT     :weight of food within the container in terms of food
//         equivalents of liver powder in mg, time t
// WT     :weight/larvae at time t in mg
// nt     :number of larvae/container
// f.T    :coefficient to relate rates of changes to physiologic time
// b      :changes in w(t), and hence f(t) are, to a slight degree,
//         nonlinearly related to larvae size
// c      :the rate of exploitation of food
// et     :variable to put equations on a chronological basis

  double foodConsumed = -nt * fT * pow(WT,b) * (1 - exp(-c * FT)) * et;

  return foodConsumed;
}



double SimContainer::WeightEqn( double WT, double FT, double et )
{
// Larval weight gain
//
// FT     :weight of food within the container in terms of food
//         equivalents of liver powder in mg, time t
// WT     :weight/larvae at time t in mg
// f.T    :coefficient to relate rates of changes to physiologic time
// b      :changes in w(t), and hence f(t) are, to a slight degree,
//         nonlinearly related to larvae size
// c      :the rate of exploitation of food
// et     :variable to put equations on a chronological basis
// d1     :fitted term from laboratory experiment, used to reduce larval
//         weight when f(t) is zero
// d2     :exponent for metabolic activity

  double weightChange = a * fT * ( pow(WT,b) * (1 - exp(-c * FT)) - d1 * pow(WT,d2)) * et;

  return weightChange;
}



void
SimContainer::AdvanceLarvae( int day )
{
  // Larval survival vs food availability
  // Weight gain or loss adjustments must consider the previous fasting
  // status of the larvae and the condition of the fatbody
  // max.fb.wt() holds the weight of the fatbody prior to fasting
  // fatbody() holds the current weight of the fatbody
  
  _newPupae = 0;
  _larvaeMaxWeight = 0;    // average wt of larval cohorts that are pupating, end value represents:  sum Wt * N / sum N

  double newPupae = 0.0;
  double totalNewPupaeWeight = 0.0;
  double totalCadaverWeight = 0.0;

  double targetThreshold = 1.0 - (_larvaeDevRate / 2.0);

  for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ) {

    if( itLarvae->Number == 0 ) {
      // TODO - at some point the smallest possible floating point number becomes 0
      ++itLarvae;
      continue;
    }
    else {
      // calculate pupation weight - temperature and CD dependent
      double WTerm = (_larvaePupationWeightSlope * abs(_averageWaterTemperature)) + _larvaePupationWeightIntercept;
      double Slope = (WTerm - _larvaeMinimumWeightForPupation) / (targetThreshold - _larvaeMaximumDevelopment);
      double PupationWt = (WTerm + (Slope * itLarvae->Development));

      if( PupationWt < _larvaeMinimumWeightForPupation )
        PupationWt = _larvaeMinimumWeightForPupation;

      if( itLarvae->Development <= targetThreshold || itLarvae->Weight < PupationWt ) {
        // not sufficiently developed and/or below pupation weight
        if( itLarvae->WeightChange >= 0 ) {
          // positive weight gain
          if( itLarvae->PreFastFatBody == 0 ) {
            // no previous fasting
          }
          else {
            // previous fasting, add weight gain to fatbody
            itLarvae->FatBody = itLarvae->FatBody + itLarvae->WeightChange;
            if( itLarvae->FatBody >= itLarvae->PreFastFatBody ) {
              // fatbody has been replenished, finish fasting
              itLarvae->FatBody = 0;
              itLarvae->PreFastFatBody = 0;
            }
          }
          itLarvae->SurvivalFood = _larvaeNoFastingSurvival;
        }
        else {
          // negative weight gain
          if( itLarvae->PreFastFatBody == 0 ) {
            // no previous fasting, establish reserve and begin fasting
            double maxFatBody = itLarvae->Weight * (_larvaeWeightToLipidSlope * (log(itLarvae->Weight) + _larvaeWeightToLipidConstant) - _larvaeNonDeptableLipidReserve);
            // don't allow negative fatbody reserve
            if( maxFatBody < 0 ) {
              maxFatBody = 0;
            }
            itLarvae->PreFastFatBody = maxFatBody;
            itLarvae->FatBody = maxFatBody + itLarvae->WeightChange;
          }
          else {
            // previous fasting
            itLarvae->FatBody = itLarvae->FatBody + itLarvae->WeightChange;
          }

          if( itLarvae->FatBody <= 0 ) {
            itLarvae->SurvivalFood = _larvaeNoLipidReserveSurvival;
          }
          else {
            itLarvae->SurvivalFood = _larvaeLipidReserveSurvival;
          }
        }

        // advance cohort
        double number = itLarvae->Number;
        double weight = itLarvae->Weight;
        double survival = _larvaeNominalSurvival * _larvaeTemperatureSurvival * _larvaeLarvicideSurvival * itLarvae->SurvivalFood;

        itLarvae->Age++;
        itLarvae->Number = itLarvae->Number * survival;
        itLarvae->Development = itLarvae->Development + _larvaeDevRate;
        itLarvae->Weight = itLarvae->Weight + itLarvae->WeightChange;

        if( itLarvae->Weight < _larvaeMinimumWeightForSurvival  || itLarvae->Development > _larvaeMaximumDevelopment ) {
          // all die and add to cadaver weight
          totalCadaverWeight += number * weight;
          itLarvae = LarvaeCohorts.erase( itLarvae );
          continue;
        }

        // otherwise only a proportion to cadaver weight
        totalCadaverWeight += (number * (1 - survival)) * weight;

        if( itLarvae->Age > MaxAgeLarv ) {
          itLarvae = LarvaeCohorts.erase( itLarvae );
        }
        else {
          ++itLarvae;
        }
      }
      else {
        double number = itLarvae->Number;
        double weight = itLarvae->Weight;
        double survival = _larvaeNominalSurvival * _larvaeTemperatureSurvival * _larvaeLarvicideSurvival * itLarvae->SurvivalFood;

        newPupae += itLarvae->Number * survival;
        totalNewPupaeWeight += itLarvae->Weight * (itLarvae->Number * survival);

        totalCadaverWeight += number * weight * (1 - survival);

        itLarvae = LarvaeCohorts.erase( itLarvae );
      }
    }
  }

  double avgNewPupaeWeight = 0.0;
  if( newPupae > 0 ) {
    avgNewPupaeWeight = totalNewPupaeWeight / newPupae;
  }

  _newPupae = newPupae;
  _larvaeMaxWeight = avgNewPupaeWeight;
  _larvaeCadaverWeight = totalCadaverWeight;
}



void
SimContainer::ApplyGeneticPupationDeath( int day )
{
  _pupaeCadaverWeight = (_newPupae - (_newPupae * _larvaePupationSurvival)) * _larvaeMaxWeight;
  _newPupae = _newPupae * _larvaePupationSurvival;
}



void
SimContainer::HatchEggs( int day )
{
  if( _averageWaterTemperature >= _eggMinimumHatchTemperature ) {
    for( int i = _hatchBand; i >= 1; --i ) {
      EggBand * eggBand = &EggCohorts[i];

      double hatchedEggs = eggBand->MatureEggs * _eggFloodHatchRatio;
      _newlyHatched += hatchedEggs;
      eggBand->MatureEggs = eggBand->MatureEggs - hatchedEggs;
    }

    // establish new larvae cohort from all newly hatched eggs
    if( _newlyHatched > 0 ) {
      LarvaeCohorts.push_back( LarvaeCohort(1, _newlyHatched * _larvaeLarvicideSurvival, _larvaeDevRate, _larvaeInitialWeight) );
    }
    _newlyHatched = 0;
  }
}



void
SimContainer::CalculateTemperaturePupalSurvival( int day )
{
  if( _minimumWaterTemperature <= _pupaeTemperatureLowLethalThreshold ) {
    _pupaeTemperatureSurvival = _pupaeTemperatureLowLethalSurvival;
  }
  else if( _minimumWaterTemperature >= _pupaeTemperatureLowThreshold ) {
    _pupaeTemperatureSurvival = 1;
  }
  else {
    double slope = (_pupaeTemperatureLowLethalSurvival - 1) / (_pupaeTemperatureLowLethalThreshold - _pupaeTemperatureLowThreshold);
    _pupaeTemperatureSurvival = 1 - ((_pupaeTemperatureLowThreshold - _minimumWaterTemperature) * slope);
  }

  if( _maximumWaterTemp >= _pupaeTemperatureHighLethalThreshold ) {
    _pupaeTemperatureSurvival = _pupaeTemperatureSurvival * _pupaeTemperatureHighLethalSurvival;
  }
  else if( _maximumWaterTemp <= _pupaeTemperatureHighThreshold ) {
    _pupaeTemperatureSurvival = _pupaeTemperatureSurvival * 1;
  }
  else {
    double slope = (1 - _pupaeTemperatureHighLethalSurvival) / (_pupaeTemperatureHighThreshold - _pupaeTemperatureHighLethalThreshold);
    _pupaeTemperatureSurvival = _pupaeTemperatureSurvival * (1 + ((_maximumWaterTemp - _pupaeTemperatureHighThreshold) * slope));
  }
}



void
SimContainer::AdvancePupae(void)
{
  // clear new adult data
  _newAdults = 0;
  _pupaeWeight = 0;

  double targetThreshold = 1.0 - (_pupaeDevRate / 2.0);
  for( PupaeIterator itPupae = PupaeCohorts.begin(); itPupae != PupaeCohorts.end(); ) {
    // apply survival
    double survivingPupae = itPupae->Number * _pupaeTemperatureSurvival * _pupaeNominalSurvival;
    double deadPupae = itPupae->Number - survivingPupae;

    if( itPupae->Development <= targetThreshold ) {
      // not developed yet, advance cohort
      itPupae->Age++;
      itPupae->Number = survivingPupae;
      itPupae->Development = itPupae->Development + _pupaeDevRate;

      _pupaeCadaverWeight += deadPupae * itPupae->Weight;

      // remove max age cohort
      if( itPupae->Age > MaxAgePupae ) {
        itPupae = PupaeCohorts.erase( itPupae );
      }
      else {
        ++itPupae;
      }
    }
    else {
      // developed, emerge as adults
      double emergedPupae = survivingPupae * _pupaeEmergenceSuccess;
      double nonEmergedPupae = survivingPupae - emergedPupae;
      double emergedPupaeWeight = emergedPupae * itPupae->Weight;

      _newAdults += emergedPupae;
      _pupaeWeight += emergedPupaeWeight;

      // pupae die from both cumulative survival and unsuccessful emergence
      deadPupae += nonEmergedPupae;
      _pupaeCadaverWeight += deadPupae * itPupae->Weight;

      // all members of cohort either emerged or dead
      itPupae = PupaeCohorts.erase( itPupae );
    }
  }

  // establish new pupae cohort
  if( _newPupae > 0 ) {
    PupaeCohorts.push_back( PupaeCohort(1, _newPupae, _pupaeDevRate, _larvaeMaxWeight) );
  }

  if( _newAdults > 0 ) {
    _pupaeWeight = _pupaeWeight / _newAdults;
  }
  else {
    _pupaeWeight = 0;
  }
}



void
SimContainer::SelectFemales(void)
{
  _newFemales = _newAdults * _pupaeFemaleEmergenceRatio;
}



double
SimContainer::CalculateDensityAdjustedNewFemaleWeight(void)
{
  return _pupaeWeight * ((_newFemales * _untreatedDensity) + (_newFemales * _treatedDensity));
}



double
SimContainer::CalculateDensityAdjustedNewFemaleCount(void)
{
  return (_newFemales * _untreatedDensity) + (_newFemales * _treatedDensity);
}



bool
SimContainer::IsDry(void)
{
  if( _waterDepth > 0 )
    return false;
  else
    return true;
}



double
SimContainer::GetWaterVolume(void)
{
  double volume = 0.0;

  if( Shape == input::Container::Rectangle ) {
    volume = (this->Length * this->Wide * this->_waterDepth) / 1000;
  }
  else if( Shape == input::Container::Circle ) {
    volume = (this->_waterDepth * 3.14159f * pow((this->Diameter/2), 2)) / 1000;
  }

  return volume;
}



double
SimContainer::GetCapacityVolume(void)
{
  double volume = 0.0;

  if( Shape == input::Container::Rectangle ) {
    volume = (this->Length * this->Wide * this->Height) / 1000;
  }
  else if( Shape == input::Container::Circle ) {
    volume = (this->Height * 3.14159f * pow((this->Diameter/2), 2)) / 1000;
  }

  return volume;
}



double
SimContainer::GetSurfaceArea(void)
{
  double surfaceArea;

  if( Shape == input::Container::Rectangle ) {
    surfaceArea = this->Length * this->Wide;
  }
  else if( Shape == input::Container::Circle ) {
    surfaceArea = 3.14159f * pow((this->Diameter/2), 2);
  }

  return surfaceArea;
}



void
SimContainer::ResetContPref(void)
{
  _ovipositionPreference = 0;
}



double
SimContainer::CalculateContPref( int day )
{
  _ovipositionPreference = log(GetCapacityVolume() + 1) * (_untreatedDensity + _treatedDensity);
  return _ovipositionPreference;
}



void
SimContainer::NormalizeContPref( double normTotal )
{
  _ovipositionPreference = _ovipositionPreference / normTotal;
}



void
SimContainer::CalculateEggInputLevel( int day )
{
  _ovipositionBand = static_cast<int>( ceil(_waterDepth / _eggBandWidth));

  if( _ovipositionBand == 0 ) {
    // only true when container is dry, any oviposition will still occur in the first band
    _ovipositionBand = 1;
  }
}



void
SimContainer::DistributeNewEggs( double totalNewEggs )
{
  // no available containers (due to exclusion cover, source control, etc.)
  if( _untreatedDensity + _treatedDensity <= 0 ) {
    _newEggCount = 0;
  }
  else {
    // _ovipositionPreference is the apportionment ratio of total eggs based on capacity method this is
    // scaled down to a container type value by dividing by density available for oviposition
    _newEggCount = totalNewEggs * _ovipositionPreference / (_untreatedDensity + _treatedDensity);

    // cohort classes
    if( _ovipositionBand == _maxEggBand ) {
      EggCohorts[_ovipositionBand].EggCohorts.push_back( EggCohort( 1, _newEggCount, 0 ) );
    }
    else {
      EggCohorts[_ovipositionBand].EggCohorts.push_back( EggCohort( 1, .5 * _newEggCount, 0 ) );
      EggCohorts[_ovipositionBand + 1].EggCohorts.push_back( EggCohort( 1, .5 * _newEggCount, 0 ) );
    }
  }
}



sim::output::ContainerPopData *
SimContainer::GeneratePopData(void)
{
  sim::output::ContainerPopData * cpd = new output::ContainerPopData();

  cpd->Name = this->Name;
  cpd->Id = this->Id;
  cpd->CloneId = this->CloneId;

  // eggs
  cpd->EggCohorts = EggCohorts;

  // larvae
  cpd->LarvaeCohorts = LarvaeCohorts;
  cpd->Cadavers = _cadavers;
  cpd->LarvaeCadaverWeight = _larvaeCadaverWeight;

  // pupae
  cpd->PupaeCohorts = PupaeCohorts;
  cpd->PupaeCadaverWeight = _pupaeCadaverWeight;

  // environment
  cpd->Depth = _waterDepthYesterday;
  cpd->Food = _foodRemainingYesterday;

  // densities
  cpd->UntreatedDensity = _untreatedDensity;
  cpd->TreatedDensity = _treatedDensity;
  cpd->ExcludedDensities = _excludedDensities;

  return cpd;
}



void
SimContainer::CalcDailyTotals()
{
  // tally eggs
  _embryonatingEggCount = 0;
  _matureEggCount = 0;

  for( EggBandIterator itBand = EggCohorts.begin(); itBand !=EggCohorts.end(); ++itBand ) {
    _matureEggCount += itBand->second.MatureEggs;
    
    for( EggIterator itEgg = itBand->second.EggCohorts.begin(); itEgg != itBand->second.EggCohorts.end(); ++itEgg ) {
      _embryonatingEggCount += itEgg->Number;
    }
  }


  // tally larvae
  _totalLarvae = 0;
  for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ++itLarvae ) {
    _totalLarvae += itLarvae->Number;
  }


  // tally pupae
  _totalPupae = 0;
  for( PupaeIterator itPupae = PupaeCohorts.begin(); itPupae != PupaeCohorts.end(); ++itPupae ) {
    _totalPupae += itPupae->Number;
  }

  // tally avg pupae weight
  _averagePupaeWeight = 0;
  int Count = 0;
  for( PupaeIterator itPupae = PupaeCohorts.begin(); itPupae != PupaeCohorts.end(); ++itPupae ) {
    if( itPupae->Weight > 0 ) {
      Count++;
      _averagePupaeWeight += itPupae->Weight;
    }
  }
  if( Count > 0 ) {
    _averagePupaeWeight = _averagePupaeWeight / Count;
  }


  // tally cumulative females
  _cumulativeFemales = _cumulativeFemales + _newFemales;


  // estimate cadaver contribution to available food
  _cadavers = (_larvaeCadaverWeight + _pupaeCadaverWeight) * _cadaverFoodRatio;
  _larvaeCadaverWeight = 0;
  _pupaeCadaverWeight = 0;
}



sim::output::DailyContainerOutput
SimContainer::GetOutput( boost::gregorian::date d )
{
  // record container output for this date
  sim::output::DailyContainerOutput dco;
  int day = d.day_of_year();

  dco.DayOfYear = day;
  dco.Depth = _waterDepth;
  dco.Food = _foodAvailable;
  dco.FoodAddition = _foodAddition;
  dco.FoodConsumption = _foodConsumption;
  dco.CadaverFoodContribution = _cadavers;
  dco.MaxTemp = _maximumWaterTemp;
  dco.MinTemp = _minimumWaterTemperature;

  dco.Eggs = _embryonatingEggCount + _matureEggCount;
  dco.Larvae = _totalLarvae;
  dco.Pupae = _totalPupae;
  dco.AvgDryPupWt = _averagePupaeWeight;
  dco.NewFemales = _newFemales;
  dco.CumulativeFemales = _cumulativeFemales;
  dco.Oviposition = _newEggCount;

  dco.TotalDensity = Density;
  dco.UntreatedDensity = _untreatedDensity;
  dco.TreatedDensity = _treatedDensity;
  dco.ExcludedDensity = GetTotalExcludedDensity();

  dco.EggDevelopment = _eggDevRate;
  dco.LarvaeDevelopment = _larvaeDevRate;
  dco.PupaeDevelopment = _pupaeDevRate;

  if( IsCloned ) {
    // the way output is currently handled we need to downscale this container with respect to its
    // cloned density to be able to accumulate with other cloned containers within this container type
    double scale = 1.0 / NumberOfClones;
    dco.Eggs *= scale;
    dco.Larvae *= scale;
    dco.Pupae *= scale;
    dco.NewFemales *= scale;
    dco.CumulativeFemales *= scale;
    dco.Oviposition *= scale;

    dco.TotalDensity *= NumberOfClones;
    dco.UntreatedDensity *= NumberOfClones;
    dco.TreatedDensity *= NumberOfClones;
    dco.ExcludedDensity *= NumberOfClones;
  }

  return dco;
}



void
SimContainer::EndDay(void)
{
  _eggDestructionSurvival = 1;

  _waterDepthYesterday = _waterDepth;
  _foodRemainingYesterday = _foodAvailable;
}



void
SimContainer::EndYear(void)
{
  // set next year's first day's previous depth and food to this year's last day's depth and food
  _waterDepthYesterday = _waterDepth;
  _foodRemainingYesterday = _foodAvailable;
}
