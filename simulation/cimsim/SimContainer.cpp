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
  InitialEggs(container->InitEggs_)
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
  UsingRandomFood = bio->Larvae->Food->UseRandomFood;

  // initially all container density is considered untreated
  UntreatedDensity = this->Density;
  TreatedDensity = 0;

  // initially no larvicide treatments in effect
  CurrentLarvicideTreatment = NULL;

  // determine maximum egg band
  MaxEggBand = static_cast<int>( ceil(this->Height / EggBandWidth) );


  if( containerPopData != NULL ) {
    // initialize simulation with existing population
    EggCohorts = containerPopData->EggCohorts;

    LarvaeCohorts = containerPopData->LarvaeCohorts;
    cadavers = containerPopData->cadavers;
    LarvCadWt = containerPopData->LarvCadWt;

    PupaeCohorts = containerPopData->PupaeCohorts;
    PupCadWt = containerPopData->PupCadWt;

    WaterDepthYesterday = containerPopData->Depth;
    FoodRemainingYesterday = containerPopData->Food;

    UntreatedDensity = containerPopData->UntreatedDensity;
    TreatedDensity = containerPopData->TreatedDensity;
    ExcludedDensities = containerPopData->ExcludedDensities;
  }
  else {
    // food calcs for the first day of year require the initial food in container to be at "day zero"
    WaterDepthYesterday = 0;
    FoodRemainingYesterday = InitFood;

    // initialize egg cohort collection with all possible bands
    EggCohorts = EggBandCollection();
    for( int i = 1; i <= MaxEggBand; ++i ) {
      EggCohorts[i] = EggBand();
    }
  
    LarvaeCohorts = LarvaeCohortCollection();
    LarvCadWt = 0;
    cadavers = 0;

    PupaeCohorts = PupaeCohortCollection();
    PupCadWt = 0;
  }


  // read biology values
  EggsP25 = bio->Egg->Development->RO25;
  EggsDHa = bio->Egg->Development->DHA;
  EggsDH = bio->Egg->Development->DHH;
  EggsTh2 = bio->Egg->Development->THALF;

  LarvP25 = bio->Larvae->Development->RO25;
  LarvDHa = bio->Larvae->Development->DHA;
  LarvDH = bio->Larvae->Development->DHH;
  LarvTh2 = bio->Larvae->Development->THALF;
  
  PupaeP25 = bio->Pupae->Development->RO25;
  PupaeDHa = bio->Pupae->Development->DHA;
  PupaeDH = bio->Pupae->Development->DHH;
  PupaeTh2 = bio->Pupae->Development->THALF;

  eggwetsu = bio->Egg->SaturationDeficit->WetSurvival;
  eggdryth = bio->Egg->SaturationDeficit->HighSunExposureThreshold;
  eggdrysu = bio->Egg->SaturationDeficit->HighSunExposureSurvival;
  egghsdth = bio->Egg->SaturationDeficit->HighThreshold;
  egglsdth = bio->Egg->SaturationDeficit->LowThreshold;
  egghsdsu = bio->Egg->SaturationDeficit->HighSurvival;
  egglsdsu = bio->Egg->SaturationDeficit->LowSurvival;

  PropHatchSpont = bio->Egg->SpontaneousHatchRatio;
  EggSurvNom = bio->Egg->NominalSurvival;

  eggtemp1 = bio->Egg->Temperature->LowThreshold;
  eggtemp2 = bio->Egg->Temperature->LowLethalThreshold;
  eggtemp3 = bio->Egg->Temperature->HighThreshold;
  eggtemp4 = bio->Egg->Temperature->HighLethalThreshold;
  
  PredLT = bio->Egg->Predation->LowThreshold;
  PredHT = bio->Egg->Predation->HighThreshold;
  PredSurLT = bio->Egg->Predation->LowSurvival;
  PredSurHT = bio->Egg->Predation->HighSurvival;

  eggdiapausetemp = bio->Egg->MinimumHatchTemperature;
  PropHatchflood = bio->Egg->FloodHatchRatio;

  LarvaeSurvivalNominal = bio->Larvae->NominalSurvival;
  CadFoodEquiv = bio->Larvae->CadaverFoodRatio;

  LarvTemp1 = bio->Larvae->Temperature->LowLethalSurvival;
  LarvTemp2 = bio->Larvae->Temperature->LowThreshold;
  LarvTemp3 = bio->Larvae->Temperature->HighLethalThreshold;
  LarvTemp4 = bio->Larvae->Temperature->HighThreshold;

  a = bio->Larvae->Food->AssimilationRate;
  b = bio->Larvae->Food->ExploitationRate;
  c = bio->Larvae->Food->ExploitationRateIndependence;
  d1 = bio->Larvae->Food->MetabolicWeightLossRate;
  d2 = bio->Larvae->Food->MetabolicWeightLossExponent;
  // TODO - this is bio->Larvae->Chrono...
  fT = .001f;                                           // TODO: larval weight function param, figure out what this is, fix where its loaded from

  larvpwtsu = bio->Larvae->Fasting->NoFastingSurvival;
  larvnwtnfbsu = bio->Larvae->Fasting->NoLipidReserveSurvival;
  larvnwtfbsu = bio->Larvae->Fasting->LipidReserveSurvival;


  LarvaeInitialWeight = bio->Larvae->WeightAtHatch;
  pupgeneticsu = bio->Larvae->PupationSurvival;

  PupTemp1 = bio->Pupae->Temperature->LowLethalThreshold;
  PupTemp2 = bio->Pupae->Temperature->LowThreshold;
  PupTemp3 = bio->Pupae->Temperature->HighThreshold;
  PupTemp4 = bio->Pupae->Temperature->HighLethalThreshold;
  PupSurvNom = bio->Pupae->NominalSurvival;
  
  PupWtSlope = bio->Larvae->PupationWeight->Slope;
  PupWtConst = bio->Larvae->PupationWeight->Intercept;
  PupMinWt = bio->Larvae->PupationWeight->MinimumWeightForPupation;

  LarvaePupWtMaxDev = bio->Larvae->PupationWeight->MaximumDevelopment;

  EmergenceSuccess = bio->Pupae->EmergenceSurvival;
  PercentFemale = bio->Pupae->FemaleEmergence;
}



SimContainer::~SimContainer(void)
{
}



void
SimContainer::Initialize( date startDate )
{
  // set previous food addition date
  PreviousFoodAdditionDate = startDate - days(3);

  // clear total productivity
  CumulativeFemales = 0;
}



void
SimContainer::InitializeYear( int year )
{
  EggSurvivalEggDestruction = 1;
  cadavers = 0;
}



void
SimContainer::InitializeEggs(void)
{
  OvipositionBand = static_cast<int>( ceil(WaterDepth / EggBandWidth) );

  if( OvipositionBand == 0 ) {
    // only true when container is dry, oviposition should still occur in the first band
    OvipositionBand = 1;
  }

  // insert initial eggs
  EggCohorts[OvipositionBand].MatureEggs = this->InitialEggs;
}



void
SimContainer::DoDay( boost::gregorian::date currentDate )
{
  CurrentDate_ = currentDate;
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
    else if( DrawdownFrequency == input::Container::Weekly && CurrentDate_.day_of_week() == boost::date_time::Thursday ) {
      // on thursday for weekly frequencies
      drawdownToday = true;
    }
    else if( DrawdownFrequency == input::Container::Monthly && CurrentDate_.day() == 14 ) {
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


  double yestDepth = WaterDepthYesterday;
  if( (yestDepth - waterLoss) < 0 )
    currentDepth = 0;
  else
    currentDepth = yestDepth - waterLoss;

  currentDepth = currentDepth + waterGain;
  if( currentDepth > Height )
    currentDepth = Height;

  WaterDepth = currentDepth;

  // check for manual fill
  if( FillMethod == input::Container::ManualFill ) {

    // daily fills
    if( ManualFillFrequency == input::Container::Daily ) {
      WaterDepth = Height;
    }

    // weekly fills occur at beginning of week
    if( ManualFillFrequency == input::Container::Weekly ) {
      if( CurrentDate_.day_of_week() == boost::date_time::Sunday ) {
        WaterDepth = Height;
      }
    }

    // monthly fills occur at beginning of month
    if( ManualFillFrequency == input::Container::Monthly ) {
      if( CurrentDate_.day() == 1 ) {
        WaterDepth = Height;
      }
    }
  }
}



void
SimContainer::CalculateWaterTemperature( double minAirTemp, double avgAirTemp, double maxAirTemp )
{
  if( WaterDepth <= 0 ) {
    // container empty, use today's air temps for container enviroment
    MinWaterTemp = minAirTemp;
    AvgWaterTemp = avgAirTemp;
    MaxWaterTemp = maxAirTemp;

    // container loses any thermal inertia
    PreviousMinWaterTemps.clear();
    PreviousMaxWaterTemps.clear();
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
    while( PreviousMinWaterTemps.size() >= (unsigned int) numDaysRequired ) {
      PreviousMinWaterTemps.pop_front();
    }
    while( PreviousMaxWaterTemps.size() >= (unsigned int) numDaysRequired ) {
      PreviousMaxWaterTemps.pop_front();
    }

    // push today's calculated temps
    PreviousMinWaterTemps.push_back( todayMinTemp );
    PreviousMaxWaterTemps.push_back( todayMaxTemp );

    int numDaysAvailable = static_cast<int>(PreviousMinWaterTemps.size());

    // now perform average
    double minSum = std::accumulate( PreviousMinWaterTemps.begin(), PreviousMinWaterTemps.end(), 0.0 );
    double maxSum = std::accumulate( PreviousMaxWaterTemps.begin(), PreviousMaxWaterTemps.end(), 0.0 );

    MinWaterTemp = minSum / numDaysAvailable;
    MaxWaterTemp = maxSum / numDaysAvailable;

    AvgWaterTemp = (MinWaterTemp + MaxWaterTemp) / 2.0;
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
  static double DevRateLarv26 = DevelopmentRate( LarvP25, 26 + 273.15, LarvDHa, LarvDH, LarvTh2 );
  static double DevRateLarv134 = DevelopmentRate( LarvP25, 13.4 + 273.15, LarvDHa, LarvDH, LarvTh2 );

  DevRateEggs = DevelopmentRate( EggsP25, AvgWaterTemp + 273.15f, EggsDHa, EggsDH, EggsTh2 );
  DevRateLarv = DevelopmentRate( LarvP25, AvgWaterTemp + 273.15f, LarvDHa, LarvDH, LarvTh2 );

  // et places food/weight calculations on a chronological basis with temperature
  // food/weight functions shutdown below 13.4 degrees celsius
  if( AvgWaterTemp <= 13.4f ) {
    et = 0;
  }
  else {
    et = (DevRateLarv - DevRateLarv134) / (DevRateLarv26 - DevRateLarv134);
  }

  DevRatePupae = DevelopmentRate(PupaeP25, AvgWaterTemp + 273.15f, PupaeDHa, PupaeDH, PupaeTh2 );
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
  double ContainerLoss = UntreatedDensity * Loss;
  double ContainerGain = Density * Loss;
  UntreatedDensity = UntreatedDensity - ContainerLoss + ContainerGain;
}



void
SimContainer::ApplySourceReduction( double rateOfReduction )
{
  double numContainersRemoved = UntreatedDensity * rateOfReduction;
  UntreatedDensity = UntreatedDensity - numContainersRemoved;
}



void
SimContainer::RecoverExcluded(void)
{
  if( ExcludedDensities.size() == 0 ) {
    // nothing to recover
    return;
  }

  std::vector<ExcludedDensity>::iterator itExcluded;
  for( itExcluded = ExcludedDensities.begin(); itExcluded != ExcludedDensities.end(); ++itExcluded ) {
    // apply recovery and loss to each excluded Density and move recovered back to untreated Density
    double numRecovered = itExcluded->Density * itExcluded->RateOfRecovery;
    double numMonthlyLoss = itExcluded->Density * this->Loss;
    itExcluded->Density = itExcluded->Density - numRecovered - numMonthlyLoss;
    UntreatedDensity = UntreatedDensity + numRecovered;
  }
}



double
SimContainer::GetTotalExcludedDensity(void)
{
  double totalExcluded = 0;
  std::vector<ExcludedDensity>::iterator itExcluded;
  for( itExcluded = ExcludedDensities.begin(); itExcluded != ExcludedDensities.end(); ++itExcluded ) {
    totalExcluded += itExcluded->Density;
  }
  return totalExcluded;
}



void
SimContainer::ApplyOvipositionExclusion( double rateOfExclusion, double rateOfRecovery )
{
  double numExcluded = UntreatedDensity * rateOfExclusion;
  UntreatedDensity = UntreatedDensity - numExcluded;

  ExcludedDensity ed;
  ed.Density = numExcluded;
  ed.RateOfRecovery = rateOfRecovery;

  ExcludedDensities.push_back(ed);
}



void
SimContainer::RecoverTreated(void)
{
  if( TreatedDensity == 0 ) {
    // no treated containers to recover
    return;
  }

  if( CurrentLarvicideTreatment->InEffect ) {
    // treatment(s) in progress, do apply monthly loss however
    double numMonthlyLoss = TreatedDensity * this->Loss;
    TreatedDensity = TreatedDensity - numMonthlyLoss;
    UntreatedDensity = UntreatedDensity + numMonthlyLoss;
  }
  else {
    // if all treatments have expired, add this density back to untreated
    UntreatedDensity = UntreatedDensity + TreatedDensity;

    // clear treated density and current treatment
    TreatedDensity = 0;
    delete CurrentLarvicideTreatment;
    CurrentLarvicideTreatment = NULL;
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
  double currentTreatedDensity = TreatedDensity;
  double nonExcludedDensity = UntreatedDensity + TreatedDensity;
  double treatmentDensity = rateOfTreatment * nonExcludedDensity;
  double additionalDensity = treatmentDensity - currentTreatedDensity;

  // update densities
  TreatedDensity += additionalDensity;
  UntreatedDensity -= additionalDensity;

  // delete previous treatment
  if( CurrentLarvicideTreatment != NULL ) {
    delete CurrentLarvicideTreatment;
  }

  // new treatment
  CurrentLarvicideTreatment = new LarvicideTreatment( li, CurrentDate_ );
}



void
SimContainer::ApplyEggDestruction( double rateOfDestruction )
{
  EggSurvivalEggDestruction = 1 - rateOfDestruction;
}



void
SimContainer::CalculateSaturationDeficitEggSurvival( int day, double satDef )
{
  if( WaterDepth == 0 ) {
    if( Exposure > this->eggdryth ) {
      EggSurvivalSatDef = eggdrysu;
    }
    else {
      if( satDef <= egglsdth ) {
        EggSurvivalSatDef = egglsdsu;
      }
      else if( satDef >= egghsdth ) {
        EggSurvivalSatDef = egghsdsu;
      }
      else {
        double eggsdslope = (egglsdsu - egghsdsu) / (egghsdth - egglsdth);
        EggSurvivalSatDef = egglsdsu - ((satDef - egglsdth) * eggsdslope);
      }
    }
  }
  else {
    EggSurvivalSatDef = eggwetsu;
  }
}



void
SimContainer::CalculateTemperatureEggSurvival( int day )
{
  if( MinWaterTemp <= eggtemp1 ) {
    EggSurvivalTemperature = .05f;
  }
  else if( MinWaterTemp >= eggtemp2 ) {
    EggSurvivalTemperature = 1;
  }
  else {
    double eggltempslope = .95f / (eggtemp1 - eggtemp2);
    EggSurvivalTemperature = 1 + ((eggtemp2 - MinWaterTemp) * eggltempslope);
  }

  if( MaxWaterTemp >= eggtemp4 ) {
    EggSurvivalTemperature = EggSurvivalTemperature * .05f;
  }
  else if( MaxWaterTemp <= eggtemp3 ) {
    EggSurvivalTemperature = EggSurvivalTemperature * 1;
  }
  else {
    double egghtempslope = .95f / (eggtemp3 - eggtemp4);
    EggSurvivalTemperature = EggSurvivalTemperature * (1 + ((MaxWaterTemp - eggtemp3) * egghtempslope));
  }
}



void
SimContainer::CalculatePredationEggSurvival( int day )
{
  if( AvgWaterTemp <= PredLT ) {
    EggSurvivalPredation = PredSurLT;
  }
  else if( AvgWaterTemp >= PredHT ) {
    EggSurvivalPredation = PredSurHT;
  }
  else {
    double Slope = (PredSurLT - PredSurHT) / (PredHT - PredLT);
    EggSurvivalPredation = PredSurLT - ((AvgWaterTemp - PredLT) * Slope);
  }
}



void
SimContainer::CalculateCumulativeEggSurvival(void)
{
  SurvEggs = EggSurvivalSatDef * EggSurvivalTemperature * EggSurvNom * EggSurvivalPredation * EggSurvivalEggDestruction;
}



void
SimContainer::AdvanceEggs( int day )
{
  HatchBand = static_cast<int>(ceil( WaterDepth / EggBandWidth ));

  NewlyHatched = 0;
  for( EggBandIterator itBand = EggCohorts.begin(); itBand != EggCohorts.end(); ++itBand ) {
    // current band iteration
    int currentBand = itBand->first;
    EggBand * eggBand = &(itBand->second);

    // process mature cohorts
    eggBand->MatureEggs = eggBand->MatureEggs * SurvEggs;

    // new develompent threshold target, using a variable CDt calculation based on today's development
    // instead of compensating for simulation's discrete development over the course of a day by making the threshold 0.95
    // (slightly less than 1.0), we subtract half of today's development from 1.0,
    // the new target is always (1 - D(t)/2)
    double targetThreshold = 1.0 - (DevRateEggs / 2.0);

    // process immature cohorts
    for( EggIterator itEgg = eggBand->EggCohorts.begin(); itEgg != eggBand->EggCohorts.end();  ) {
      if( itEgg->Development <= targetThreshold ) {
        itEgg->Age++;
        itEgg->Number = itEgg->Number * SurvEggs;
        itEgg->Development = itEgg->Development + DevRateEggs;

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
        if( AvgWaterTemp < eggdiapausetemp ) {
          eggBand->MatureEggs = eggBand->MatureEggs + (itEgg->Number * SurvEggs);
        }
        else {
          if( currentBand <= HatchBand ) {
            // band flooded, all eggs hatch
            NewlyHatched += (itEgg->Number * SurvEggs);
          }
          else {
            // band not flooded, some proportion hatch spontaneously, rest become mature eggs
            eggBand->MatureEggs += ((1 - PropHatchSpont) * itEgg->Number * SurvEggs);
            NewlyHatched += (PropHatchSpont * itEgg->Number * SurvEggs);
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
  if( WaterDepth == 0 ) {
    NewlyHatched = 0;
  }
}



void
SimContainer::AdjustFood( date currentDate )
{
  // find addition parameter for current month
  double foodAddition = this->MonthlyFoodAdditions[currentDate.month().as_enum()];

  // apply decay to yesterday's food
  double naturalDecay = FoodRemainingYesterday * FoodDecayRate;
  double yesterdayFood = FoodRemainingYesterday - naturalDecay;
  if( yesterdayFood < 0 ) {
    yesterdayFood = 0;
  }

  // calculate actual food addition, if any
  if( UsingRandomFood ) {
    // between 0-2 times the daily amount, every day
    double rndFactor = (double) rand()/RAND_MAX * 2;
    foodAddition = foodAddition * rndFactor;
  }
  else {
    // fixed delivery every 3 days
    if( currentDate == PreviousFoodAdditionDate + days(3) ) {
      // 3 times daily addition
      foodAddition = 3 * foodAddition;

      // update previous day for next 3 day interval
      PreviousFoodAdditionDate = currentDate;
    }
    else {
      // no addition yet, still within 3 day interval
      foodAddition = 0;
    }
  }

  // today's food = yesterday's food + addition (if any) + cadavers
  FoodAvailable = yesterdayFood + foodAddition + cadavers;
}



void
SimContainer::CalculateTemperatureLarvalSurvival( int day )
{
  // survival from minimum temperatures
  if( MinWaterTemp <= LarvTemp1 ) {
    LarvaeSurvivalTemperature = .05f;
  }
  else if( MinWaterTemp >= LarvTemp2 ) {
    LarvaeSurvivalTemperature = 1.0f;
  }
  else {
    double LarSlope = (.05f - 1.0f) / (LarvTemp1 - LarvTemp2);
    LarvaeSurvivalTemperature = 1 - ((LarvTemp2 - MinWaterTemp) * LarSlope);
  }

  // survival from maximum temperatures
  if( MaxWaterTemp >= LarvTemp4 ) {
    LarvaeSurvivalTemperature = LarvaeSurvivalTemperature * .05f;
  }
  else if( MaxWaterTemp <= LarvTemp3 ) {
    LarvaeSurvivalTemperature = LarvaeSurvivalTemperature * 1;
  }
  else {
    double LarSlope = (1 - .05f) / (LarvTemp3 - LarvTemp4);
    LarvaeSurvivalTemperature = LarvaeSurvivalTemperature * (1 + ((MaxWaterTemp - LarvTemp3) * LarSlope));
  }
}



void
SimContainer::CalculateLarvicideLarvalSurvival( date d )
{
  if( CurrentLarvicideTreatment != NULL ) {
    if( CurrentLarvicideTreatment->InEffect ) {
      // first check for effect loss if dry
      if( CurrentLarvicideTreatment->LoseOnDry && this->IsDry() ) {
        CurrentLarvicideTreatment->InEffect = false;
      }

      // find mortality for today, and its inverse survival
      double mortality = CurrentLarvicideTreatment->Mortality[d];
      LarvaeSurvivalLarvicide = 1.0 - mortality;

      // if tomorrow is not in mortality map, treatment period and effect is over
      if( !CurrentLarvicideTreatment->IsDateInTreatmentPeriod(d + days(1)) ) {
        CurrentLarvicideTreatment->InEffect = false;
      }
    }
  }
  else {
    // no treatments in effect, full survival
    LarvaeSurvivalLarvicide = 1.0;
  }
}



void
SimContainer::CalculateWaterDepthLarvalSurvival( int day )
{
  // for empty containers, survival drops to 0.05
  if( WaterDepth == 0 )
    LarvaeSurvivalTemperature = .05f;
}



void
SimContainer::CalculateLarvalFoodConsumptionAndWeight( int day, int eulerSteps )
{
  // clear today's weight changes
  for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ++itLarvae ) {
    itLarvae->WeightChange = 0;
  }


  for( int i = 1; i <= eulerSteps; ++i ) {
    double stepConsumption = 0.0;
    for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ++itLarvae ) {
      // calculate larvae food/weight
      double cohortFoodConsumption = FoodEqn( itLarvae->Number, (itLarvae->Weight + itLarvae->WeightChange), FoodAvailable, et ) * (2880 / (double)eulerSteps);
      double cohortWeightChange = WeightEqn( (itLarvae->Weight + itLarvae->WeightChange), FoodAvailable, et ) * (2880 / (double)eulerSteps);

      // update container food after each cohort feeds, not just after each Euler step
      FoodAvailable += cohortFoodConsumption;
      if( FoodAvailable < 0 ) {
        FoodAvailable = 0;
      }

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
  
  NewPupae = 0;
  MaxLarvWt = 0;    // average wt of larval cohorts that are pupating, end value represents:  sum Wt * N / sum N

  double newPupae = 0.0;
  double totalNewPupaeWeight = 0.0;
  double totalCadaverWeight = 0.0;

  double targetThreshold = 1.0 - (DevRateLarv / 2.0);

  for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ) {

    if( itLarvae->Number == 0 ) {
      // TODO - at some point the smallest possible floating point number becomes 0
      ++itLarvae;
      continue;
    }
    else {
      // calculate pupation weight - temperature and CD dependent
      double WTerm = (PupWtSlope * abs(AvgWaterTemp)) + PupWtConst;
      double Slope = (WTerm - PupMinWt) / (targetThreshold - LarvaePupWtMaxDev);
      double PupationWt = (WTerm + (Slope * itLarvae->Development));

      if( PupationWt < PupMinWt )
        PupationWt = PupMinWt;

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
          itLarvae->SurvivalFood = larvpwtsu;
        }
        else {
          // negative weight gain
          if( itLarvae->PreFastFatBody == 0 ) {
            // no previous fasting, establish reserve and begin fasting
            double maxfb = itLarvae->Weight * (.059f * (log(itLarvae->Weight) + 6.9f) - .15f);
            // don't allow negative fatbody reserve
            if( maxfb < 0 ) {
              maxfb = 0;
            }
            itLarvae->PreFastFatBody = maxfb;
            itLarvae->FatBody = maxfb + itLarvae->WeightChange;
          }
          else {
            // previous fasting
            itLarvae->FatBody = itLarvae->FatBody + itLarvae->WeightChange;
          }

          if( itLarvae->FatBody <= 0 ) {
            itLarvae->SurvivalFood = larvnwtnfbsu;
          }
          else {
            itLarvae->SurvivalFood = larvnwtfbsu;
          }
        }

        // advance cohort
        double number = itLarvae->Number;
        double weight = itLarvae->Weight;
        double survival = LarvaeSurvivalNominal * LarvaeSurvivalTemperature * LarvaeSurvivalLarvicide * itLarvae->SurvivalFood;

        itLarvae->Age++;
        itLarvae->Number = itLarvae->Number * survival;
        itLarvae->Development = itLarvae->Development + DevRateLarv;
        itLarvae->Weight = itLarvae->Weight + itLarvae->WeightChange;

        if( itLarvae->Weight < .003 || itLarvae->Development > LarvaePupWtMaxDev ) {
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
        double survival = LarvaeSurvivalNominal * LarvaeSurvivalTemperature * LarvaeSurvivalLarvicide * itLarvae->SurvivalFood;

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

  NewPupae = newPupae;
  MaxLarvWt = avgNewPupaeWeight;
  LarvCadWt = totalCadaverWeight;
}



void
SimContainer::ApplyGeneticPupationDeath( int day )
{
  PupCadWt = (NewPupae - (NewPupae * pupgeneticsu)) * MaxLarvWt;
  NewPupae = NewPupae * pupgeneticsu;
}



void
SimContainer::HatchEggs( int day )
{
  if( AvgWaterTemp >= eggdiapausetemp ) {
    for( int i = HatchBand; i >= 1; --i ) {
      EggBand * eggBand = &EggCohorts[i];

      double hatchedEggs = eggBand->MatureEggs * PropHatchflood;
      NewlyHatched += hatchedEggs;
      eggBand->MatureEggs = eggBand->MatureEggs - hatchedEggs;
    }

    // establish new larvae cohort from all newly hatched eggs
    if( NewlyHatched > 0 ) {
      LarvaeCohorts.push_back( LarvaeCohort(1, NewlyHatched * LarvaeSurvivalLarvicide, DevRateLarv, LarvaeInitialWeight) );
    }
    NewlyHatched = 0;
  }
}



void
SimContainer::CalculateTemperaturePupalSurvival( int day )
{
  if( MinWaterTemp <= PupTemp1 ) {
    PupSurvTempDlyCt = .05f;
  }
  else if( MinWaterTemp >= PupTemp2 ) {
    PupSurvTempDlyCt = 1;
  }
  else {
    double PupSlope = (.05f - 1) / (PupTemp1 - PupTemp2);
    PupSurvTempDlyCt = 1 - ((PupTemp2 - MinWaterTemp) * PupSlope);
  }

  if( MaxWaterTemp >= PupTemp4 ) {
    PupSurvTempDlyCt = PupSurvTempDlyCt * .05f;
  }
  else if( MaxWaterTemp <= PupTemp3 ) {
    PupSurvTempDlyCt = PupSurvTempDlyCt * 1;
  }
  else {
    double PupSlope = (1 - .05f) / (PupTemp3 - PupTemp4);
    PupSurvTempDlyCt = PupSurvTempDlyCt * (1 + ((MaxWaterTemp - PupTemp3) * PupSlope));
  }
}



void
SimContainer::AdvancePupae(void)
{
  // clear new adult data
  NewAdults = 0;
  PupaeWt = 0;

  double targetThreshold = 1.0 - (DevRatePupae / 2.0);
  for( PupaeIterator itPupae = PupaeCohorts.begin(); itPupae != PupaeCohorts.end(); ) {
    // apply survival
    double survivingPupae = itPupae->Number * PupSurvTempDlyCt * PupSurvNom;
    double deadPupae = itPupae->Number - survivingPupae;

    if( itPupae->Development <= targetThreshold ) {
      // not developed yet, advance cohort
      itPupae->Age++;
      itPupae->Number = survivingPupae;
      itPupae->Development = itPupae->Development + DevRatePupae;

      PupCadWt += deadPupae * itPupae->Weight;

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
      double emergedPupae = survivingPupae * EmergenceSuccess;
      double nonEmergedPupae = survivingPupae - emergedPupae;
      double emergedPupaeWeight = emergedPupae * itPupae->Weight;

      NewAdults += emergedPupae;
      PupaeWt += emergedPupaeWeight;

      // pupae die from both cumulative survival and unsuccessful emergence
      deadPupae += nonEmergedPupae;
      PupCadWt += deadPupae * itPupae->Weight;

      // all members of cohort either emerged or dead
      itPupae = PupaeCohorts.erase( itPupae );
    }
  }

  // establish new pupae cohort
  if( NewPupae > 0 ) {
    PupaeCohorts.push_back( PupaeCohort(1, NewPupae, DevRatePupae, MaxLarvWt) );
  }

  if( NewAdults > 0 ) {
    PupaeWt = PupaeWt / NewAdults;
  }
  else {
    PupaeWt = 0;
  }
}



void
SimContainer::SelectFemales(void)
{
  NewFemales = NewAdults * PercentFemale;
}



double
SimContainer::CalculateDensityAdjustedNewFemaleWeight(void)
{
  return PupaeWt * ((NewFemales * UntreatedDensity) + (NewFemales * TreatedDensity));
}



double
SimContainer::CalculateDensityAdjustedNewFemaleCount(void)
{
  return (NewFemales * UntreatedDensity) + (NewFemales * TreatedDensity);
}



bool
SimContainer::IsDry(void)
{
  if( WaterDepth > 0 )
    return false;
  else
    return true;
}



double
SimContainer::GetWaterVolume(void)
{
  double volume = 0.0;

  if( Shape == input::Container::Rectangle ) {
    volume = (this->Length * this->Wide * this->WaterDepth) / 1000;
  }
  else if( Shape == input::Container::Circle ) {
    volume = (this->WaterDepth * 3.14159f * pow((this->Diameter/2), 2)) / 1000;
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
  ContPref = 0;
}



double
SimContainer::CalculateContPref( int day )
{
  ContPref = log(GetCapacityVolume() + 1) * (UntreatedDensity + TreatedDensity);
  return ContPref;
}



void
SimContainer::NormalizeContPref( double normTotal )
{
  ContPref = ContPref / normTotal;
}



void
SimContainer::CalculateEggInputLevel( int day )
{
  OvipositionBand = static_cast<int>( ceil(WaterDepth / EggBandWidth));

  if( OvipositionBand == 0 ) {
    // only true when container is dry, any oviposition will still occur in the first band
    OvipositionBand = 1;
  }
}



void
SimContainer::DistributeNewEggs( double totalNewEggs )
{
  // no available containers (due to exclusion cover, source control, etc.)
  if( UntreatedDensity + TreatedDensity <= 0 ) {
    NewEggCount = 0;
  }
  else {
    // ContPref is the apportionment ratio of total eggs based on capacity method this is
    // scaled down to a container type value by dividing by density available for oviposition
    NewEggCount = totalNewEggs * ContPref / (UntreatedDensity + TreatedDensity);

    // cohort classes
    if( OvipositionBand == MaxEggBand ) {
      EggCohorts[OvipositionBand].EggCohorts.push_back( EggCohort( 1, NewEggCount, 0 ) );
    }
    else {
      EggCohorts[OvipositionBand].EggCohorts.push_back( EggCohort( 1, .5 * NewEggCount, 0 ) );
      EggCohorts[OvipositionBand + 1].EggCohorts.push_back( EggCohort( 1, .5 * NewEggCount, 0 ) );
    }
  }
}



sim::output::ContainerPopData *
SimContainer::GeneratePopData(void)
{
  sim::output::ContainerPopData * cpd = new output::ContainerPopData();

  cpd->Name = this->Name;

  // eggs
  cpd->EggCohorts = EggCohorts;

  // larvae
  cpd->LarvaeCohorts = LarvaeCohorts;
  cpd->cadavers = cadavers;
  cpd->LarvCadWt = LarvCadWt;

  // pupae
  cpd->PupaeCohorts = PupaeCohorts;
  cpd->PupCadWt = PupCadWt;

  // environment
  cpd->Depth = WaterDepthYesterday;
  cpd->Food = FoodRemainingYesterday;

  // densities
  cpd->UntreatedDensity = UntreatedDensity;
  cpd->TreatedDensity = TreatedDensity;
  cpd->ExcludedDensities = ExcludedDensities;

  return cpd;
}



void
SimContainer::CalcDailyTotals()
{
  // tally eggs
  EmbryonatingEggCount = 0;
  MatureEggCount = 0;
  for( EggBandIterator itBand = EggCohorts.begin(); itBand !=EggCohorts.end(); ++itBand ) {
    MatureEggCount += itBand->second.MatureEggs;
    
    for( EggIterator itEgg = itBand->second.EggCohorts.begin(); itEgg != itBand->second.EggCohorts.end(); ++itEgg ) {
      EmbryonatingEggCount += itEgg->Number;
    }
  }


  // tally larvae
  TotalLarvae = 0;
  for( LarvaeIterator itLarvae = LarvaeCohorts.begin(); itLarvae != LarvaeCohorts.end(); ++itLarvae ) {
    TotalLarvae += itLarvae->Number;
  }


  // tally pupae
  TotalPupae = 0;
  for( PupaeIterator itPupae = PupaeCohorts.begin(); itPupae != PupaeCohorts.end(); ++itPupae ) {
    TotalPupae += itPupae->Number;
  }

  // tally avg pupae weight
  AveragePupaeWeight = 0;
  int Count = 0;
  for( PupaeIterator itPupae = PupaeCohorts.begin(); itPupae != PupaeCohorts.end(); ++itPupae ) {
    if( itPupae->Weight > 0 ) {
      Count++;
      AveragePupaeWeight += itPupae->Weight;
    }
  }
  if( Count > 0 ) {
    AveragePupaeWeight = AveragePupaeWeight / Count;
  }


  // tally cumulative females
  CumulativeFemales = CumulativeFemales + NewFemales;


  // estimate cadaver contribution to available food
  cadavers = (LarvCadWt + PupCadWt) * CadFoodEquiv;
  LarvCadWt = 0;
  PupCadWt = 0;
}



sim::output::DailyContainerOutput
SimContainer::GetOutput( boost::gregorian::date d )
{
  // record container output for this date
  sim::output::DailyContainerOutput dco;
  int day = d.day_of_year();

  dco.DayOfYear = day;
  dco.Depth = WaterDepth;
  dco.Food = FoodAvailable;
  dco.MaxTemp = MaxWaterTemp;
  dco.MinTemp = MinWaterTemp;
  dco.Eggs = EmbryonatingEggCount + MatureEggCount;
  dco.Larvae = TotalLarvae;
  dco.Pupae = TotalPupae;
  dco.AvgDryPupWt = AveragePupaeWeight;
  dco.NewFemales = NewFemales;
  dco.CumulativeFemales = CumulativeFemales;
  dco.Oviposition = NewEggCount;
  dco.TotalDensity = Density;
  dco.UntreatedDensity = UntreatedDensity;
  dco.TreatedDensity = TreatedDensity;
  dco.ExcludedDensity = GetTotalExcludedDensity();

  return dco;
}



void
SimContainer::EndDay(void)
{
  EggSurvivalEggDestruction = 1;

  WaterDepthYesterday = WaterDepth;
  FoodRemainingYesterday = FoodAvailable;
}



void
SimContainer::EndYear(void)
{
  // Set next year's first day's previous depth and food to this year's last day's depth and food
  WaterDepthYesterday = WaterDepth;
  FoodRemainingYesterday = FoodAvailable;
}

