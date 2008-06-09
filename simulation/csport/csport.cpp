#include "stdafx.h"
#include "csport.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <sstream>

using namespace sim::csp;

//==========
// CIMMAIN.h
//==========


void csport::cimmain()
{
  ReadDefaultParms();
  StartProgram();
}


void csport::StartProgram(void)
{
  ControlFileRead();
  InitializeVariables();

  // read location data
  LocAssign();

  // simulation "menu"
  MenuPreSimulation();

  if( !PopFile ) {
    ClearEggArrays();

    for( int i = 1; i <= NumberOfContainers; i++ ) {
      // init "day before" day 1 with its food, the container's init food param
      ContEnv[0][i].Food = ContEnv[0][i].Food + ContDesc[i].InitFood;
    }
  }

  WaterDepthTemp();

lblNextYear:

  MainLoop();

  if( CurSimYear < EndSimYear ) {     // more years left to simulate

    //do treatment transfers to allow for continuous applications
    if( SMPop[YrLen] > 0 ) {
      SMPop[0] = SMPop[YrLen];    // transfer sterile male population of last day of previous year
    }                             // to first day of next year

    if( LI ) {
      for( int i = 1; i <= NumberOfContainers; ++i ) {
        //remove previous years treatment
        for( int j = 1; j <= YrLen; ++j ) {
          LISurv[j][i] = 1;
        }
        //transfer next years residual to current year
        //remove following year
        for( int j = 366; j <= 480; ++j ) {
          LISurv[j - YrLen][i] = LISurv[j][i];    // transfer residuals from previous year(from 366 to 480) to beginning of next year
          LISurv[j][i] = 1;                       // reset next year's residuals (from 366 to 480)
        }
      }
    }

    if( RS ) {
      // reset first part of year
      for( int i = 1; i <= YrLen; ++i ) {
        RSSurv[i] = 1;
      }
      // last year's residuals to beginning of this year, then remove last year's
      for( int i = 366; i <= 480; ++i ) {
        RSSurv[i - YrLen] = RSSurv[i];
        RSSurv[i] = 1;
      }

      //-------------------------------------//
      // 11/15/94 reset control strategy for //
      // successive years on continuous runs //
      //-------------------------------------//

      float RSMinSurv = 1 - RSMaxMort;
      int NextTrt = RSStartDay;
      for( int i = 1; i <= RSNumTrts; ++i ) {
        RSSchedule[NextTrt] = true;
        for( int j = NextTrt; j <= NextTrt% + RSDaysMax% - 1; NextTrt = NextTrt + RSInterval ) {
          RSSurv[j] = RSSurv[j] * RSMinSurv;
          if( RSSurv[j] < RSMinSurv ) {
            RSSurv[j] = RSMinSurv;
          }
        }
        for( int j = NextTrt + RSDaysMax; j <= RSDaysMax + RSDaysRes - 1; ++j ) {
          float slope = (1 - RSMinSurv) / ((NextTrt + RSDaysMax + RSDaysRes) - (NextTrt + RSDaysMax));
          RSSurv[j] = RSSurv[j] * (RSMinSurv + (j - (NextTrt + RSDaysMax - 1)) * slope);
          if( RSSurv[j] < RSMinSurv ) {
            RSSurv[j] = RSMinSurv;
          }
        }
      }
      //-------------------------------------//
    }
  }
  else {
    // last year complete, simulation finished
    return;
  }

  Year = Year + 1;

  HumanDensity = HumanDensity + (HumanDensity * HumanGrowthRate / 100);
  MammalDensity = MammalDensity + (MammalDensity * MammalGrowthRate / 100);

  for( int i = 1; i <= MaxNumCt; ++i ) {
    AdultsNewDlyCt[i] = 0;
  }
  for( int i = 1; i <= YrLen; ++i ) {
    TotPreOviAdults[i] = 0;
    TotOviAdults[i] = 0;
  }


//=============================
//Find next yearly weather file
//=============================

  // read next year of weather from Location_
  input::WeatherYear * wy = Location_.Weather_->GetWeatherForYear( StartDate + CurSimYear );

  for( int i = 1; i <= YrLen; i++ ) {
    input::WeatherDay * wd = wy->GetDay(i);
    TemperatureMax[i] = (float) wd->MaxTemp_;
    TemperatureMin[i] = (float) wd->MinTemp_;
    TemperatureAvg[i] = (float) wd->AvgTemp_;
    SD[i] = (float) wd->SatDef_;
    Rain[i] = (float) wd->Precip_;
    RelHumid[i] = (float) wd->RelHum_;
  }

  // save food/depth of each container from previous year
  // as initial food/depth of each container next year

  for( int i = 1; i <= NumberOfContainers; ++i ) {
    ContEnv[0][i].Depth = ContEnv[YrLen][i].Depth;
  }

  for( int i = 1; i <= NumberOfContainers; ++i ) {
    ContEnv[0][i].Food = ContEnv[YrLen][i].Food;
    ContDesc[i].InitialEggs = 0;
  }

//======================================================
//Adjust Source Reduction
//Treatment schedules must be set yearly.  However, a
//residual effect may persist for the following year.
//Allow for continous treatments in a multi-year simulation.
//======================================================

  if( CurSimYear == EndSimYear ) { // TODO - Why doesn't this check if CurSimYear > EndSimYear, this effectively negates controls for the last year

    //multiyear simulation is over, clear treatments

    SR = false;
    ClearSchedule( SRSchedule );

    ClearSchedule( SMSchedule );
    if( SMPop[YrLen] <= 0 ) {
      SM = false;
      for( int i = 1; i <= YrLen; ++i ) {
        SMPop[i] = 0.0;
      }
    }
    else {
      SMPop[0] = SMPop[YrLen];
    }

    ED = false;
    ClearSchedule( EDSchedule );

    OE = false;
    ClearSchedule( OESchedule );

    LI = false;
    ClearSchedule( LISchedule );

    for( int i = 1; i <= NumberOfContainers; ++i ) {
      //remove previous years treatment
      for( int j = 1; j <= YrLen; ++j ) {
        LISurv[j][i] = 1;
      }
      //transfer next years residual to current year
      //remove following year
      for( int j = 366; j <= 480; ++j ) {
        LISurv[j - YrLen][i] = LISurv[j][i];
        LISurv[j][i] = 1;
      }
    }

    SS = false;
    SSDensityFlag = false;
    ClearSchedule( SSSchedule );

    RS= false;
    ClearSchedule( RSSchedule);

    for( int i = 1; i <= YrLen; ++i ) {
      RSSurv[i] = 1;
    }
    //transfer next years residual to current year
    //remove following year'
    for( int i = 366; i <= 480; ++i ) {
      RSSurv[i - YrLen] = RSSurv[i];
      RSSurv[i] = 1;
    }

    AnyControls = false;
  }

  if( CurSimYear < EndSimYear ) {
    CurSimYear = CurSimYear + 1;
    if( CurSimYear = EndSimYear ) {
      //CurSimYear = 1;
    }
  }
  else {
    //CALL Menu.PreSimulation(restart%)
    //IF restart% THEN GOTO Start.Program
  }

  WaterDepthTemp();

  goto lblNextYear;
}


void csport::BioReadFile(void)
{
  EggsP25 = (float) Location_.Biology_->Egg->Development->RO25;
  EggsDHa = (float) Location_.Biology_->Egg->Development->DHA;
  EggsDH = (float) Location_.Biology_->Egg->Development->DHH;
  EggsTh2 = (float) Location_.Biology_->Egg->Development->THALF;

  LarvP25 = (float) Location_.Biology_->Larvae->Development->RO25;
  LarvDHa = (float) Location_.Biology_->Larvae->Development->DHA;
  LarvDH = (float) Location_.Biology_->Larvae->Development->DHH;
  LarvTh2 = (float) Location_.Biology_->Larvae->Development->THALF;
  
  PupaeP25 = (float) Location_.Biology_->Pupae->Development->RO25;
  PupaeDHa = (float) Location_.Biology_->Pupae->Development->DHA;
  PupaeDH = (float) Location_.Biology_->Pupae->Development->DHH;
  PupaeTh2 = (float) Location_.Biology_->Pupae->Development->THALF;

  AdultP25 = (float) Location_.Biology_->Adult->Development->RO25;
  AdultDHa = (float) Location_.Biology_->Adult->Development->DHA;
  AdultDH = (float) Location_.Biology_->Adult->Development->DHH;
  AdultTh2 = (float) Location_.Biology_->Adult->Development->THALF;

  egghsdth = (float) Location_.Biology_->Egg->SaturationDeficit->HighThreshold;
  egglsdth = (float) Location_.Biology_->Egg->SaturationDeficit->LowThreshold;
  egghsdsu = (float) Location_.Biology_->Egg->SaturationDeficit->HighSurvival;
  egglsdsu = (float) Location_.Biology_->Egg->SaturationDeficit->LowSurvival;

  eggtemp1 = (float) Location_.Biology_->Egg->Temperature->LowThreshold;
  eggtemp2 = (float) Location_.Biology_->Egg->Temperature->LowLethalThreshold;
  eggtemp3 = (float) Location_.Biology_->Egg->Temperature->HighThreshold;
  eggtemp4 = (float) Location_.Biology_->Egg->Temperature->HighLethalThreshold;
  
  adtemp1 = (float) Location_.Biology_->Adult->Temperature->LowLethalThreshold;
  adtemp2 = (float) Location_.Biology_->Adult->Temperature->LowThreshold;
  adtemp3 = (float) Location_.Biology_->Adult->Temperature->HighThreshold;
  adtemp4 = (float) Location_.Biology_->Adult->Temperature->HighLethalThreshold;

  adlsdth = (float) Location_.Biology_->Adult->SaturationDeficit->LowThreshold;
  adhsdth = (float) Location_.Biology_->Adult->SaturationDeficit->HighThreshold;
  adlsdsu = (float) Location_.Biology_->Adult->SaturationDeficit->LowSurvival;
  adhsdsu = (float) Location_.Biology_->Adult->SaturationDeficit->HighSurvival;

  PupWtSlope = (float) Location_.Biology_->Larvae->PupationWeight->Slope;
  PupWtConst = (float) Location_.Biology_->Larvae->PupationWeight->Intercept;
  PupMinWt = (float) Location_.Biology_->Larvae->PupationWeight->MinimumWeightForPupation;
  PupMinAge = (float) Location_.Biology_->Larvae->PupationWeight->MinimumAgeForPupation;

  larvpwtsu = (float) Location_.Biology_->Larvae->Fasting->NoFastingSurvival;
  larvnwtnfbsu = (float) Location_.Biology_->Larvae->Fasting->NoLipidReserveSurvival;
  larvnwtfbsu = (float) Location_.Biology_->Larvae->Fasting->LipidReserveSurvival;

  eggwetsu = (float) Location_.Biology_->Egg->SaturationDeficit->WetSurvival;
  eggdrysu = (float) Location_.Biology_->Egg->SaturationDeficit->HighSunExposureSurvival;

  LarvTemp1 = (float) Location_.Biology_->Larvae->Temperature->LowLethalSurvival;
  LarvTemp2 = (float) Location_.Biology_->Larvae->Temperature->LowThreshold;
  LarvTemp3 = (float) Location_.Biology_->Larvae->Temperature->HighLethalThreshold;
  LarvTemp4 = (float) Location_.Biology_->Larvae->Temperature->HighThreshold;

  LarvaeMaxCD = (float) Location_.Biology_->Larvae->MaximumDevelopment;

  eggdiapausetemp = (float) Location_.Biology_->Egg->MinimumHatchTemperature;
  PropHatchflood = (float) Location_.Biology_->Egg->FloodHatchRatio;

  initw = (float) Location_.Biology_->Larvae->WeightAtHatch;
  survadnom = (float) Location_.Biology_->Adult->NominalSurvival;
  LarvSurvNom = (float) Location_.Biology_->Larvae->NominalSurvival;

  PupTemp1 = (float) Location_.Biology_->Pupae->Temperature->LowLethalThreshold;
  PupTemp2 = (float) Location_.Biology_->Pupae->Temperature->LowThreshold;
  PupTemp3 = (float) Location_.Biology_->Pupae->Temperature->HighThreshold;
  PupTemp4 = (float) Location_.Biology_->Pupae->Temperature->HighLethalThreshold;
  PupSurvNom = (float) Location_.Biology_->Pupae->NominalSurvival;

  pupgeneticsu = (float) Location_.Biology_->Larvae->PupationSurvival;
  PropHatchSpont = (float) Location_.Biology_->Egg->SpontaneousHatchRatio;
  EggSurvNom = (float) Location_.Biology_->Egg->NominalSurvival;

  EmergenceSuccess = (float) Location_.Biology_->Pupae->EmergenceSurvival;
  PercentFemale = (float) Location_.Biology_->Pupae->FemaleEmergence;

  AdultDensLTH = 1;
  AdultDensHTH = 1;
  AdultDensLSU = 1;
  AdultDensHSU = 1;

  //InterFeeding = (float) Location_.Biology_->Adult->InterruptedFeedsPerMeal;
  InterFeeding = 1;
  FecundityCoef = (float) Location_.Biology_->Adult->FecundityFactor;
  ReturnOviRate = 0;

  OviTemperature = (float) Location_.Biology_->Adult->MinimumOvipositionTemperature;
  a = (float) Location_.Biology_->Larvae->Food->AssimilationRate;
  b = (float) Location_.Biology_->Larvae->Food->ExploitationRate;
  c = (float) Location_.Biology_->Larvae->Food->ExploitationRateIndependence;
  d1 = (float) Location_.Biology_->Larvae->Food->MetabolicWeightLossRate;
  d2 = (float) Location_.Biology_->Larvae->Food->MetabolicWeightLossExponent;

  DBloodLWt = (float) Location_.Biology_->Adult->DoubleBloodMeal->LowWeightLimit;
  DBloodUWt = (float) Location_.Biology_->Adult->DoubleBloodMeal->HighWeightLimit;
  DBloodLProp = (float) Location_.Biology_->Adult->DoubleBloodMeal->LowWeightRatio;
  DBloodUProp = (float) Location_.Biology_->Adult->DoubleBloodMeal->HighWeightRatio;

  CadFoodEquiv = (float) Location_.Biology_->Larvae->CadaverFoodRatio;
  PredLT = (float) Location_.Biology_->Egg->Predation->LowThreshold;
  PredHT = (float) Location_.Biology_->Egg->Predation->HighThreshold;
  PredSurLT = (float) Location_.Biology_->Egg->Predation->LowSurvival;
  PredSurHT = (float) Location_.Biology_->Egg->Predation->HighSurvival;

  r = 1.987f;
  DevRateLarv26 = DevelopmentRate( LarvP25, 299, LarvDHa, LarvDH, LarvTh2, r );
}


void csport::ClearEggArrays(void)
{
  /*  In CS 1.0 the age dimension of an egg array is MaxAgeEgg+1, which gives MaxAgeEggs      *
   *  positions and one extra position that serves as a counter.  Because of the "semantics"  *
   *  associated with this dimension (i.e. the numerical value of the dimension is also       *
   *  the age of the cohort at that position in the array) we have to emulate 1-indexing      *
   *  used with these arrays.  The dimension in C++ then is MaxAgeEggs+2, accounting for      *
   *  1-indexing as well as the counter position.                                             *
   *                                                                                          *
   * Likewise the level dimension value is the actual level (CS 1.0's discrete 2-cm egg       *
   * bands) of the cohort in the container. Again to emulate this in C++ we add 1 to the      *
   * value returned from CINT(), since for X levels we need an array of size X+1 to be able   *
   * to use 1-indexing                                                                        */


  int i;                    // level dimension
  int j = MaxAgeEggs + 2;   // age dimension


  i = CINT( (ContDesc[1].Height/2) + .2f ) + 1;
  C1Eggs = ReDim( i, j );
  C1MatureEggs = ReDim( i );
  C1CumDevEggs = ReDim( i, j );

  EggArrays[1] = C1Eggs;
  EggMatureArrays[1] = C1MatureEggs;
  EggDevArrays[1] = C1CumDevEggs;

  if( NumberOfContainers == 1 ) return;

  i = CINT( (ContDesc[2].Height/2) + .2f ) + 1;
  C2Eggs = ReDim( i, j );
  C2MatureEggs = ReDim( i );
  C2CumDevEggs = ReDim( i, j );

  EggArrays[2] = C2Eggs;
  EggMatureArrays[2] = C2MatureEggs;
  EggDevArrays[2] = C2CumDevEggs;

  if( NumberOfContainers == 2 ) return;

  i = CINT( (ContDesc[3].Height/2) + .2f ) + 1;
  C3Eggs = ReDim( i, j );
  C3MatureEggs = ReDim( i );
  C3CumDevEggs = ReDim( i, j );

  EggArrays[3] = C3Eggs;
  EggMatureArrays[3] = C3MatureEggs;
  EggDevArrays[3] = C3CumDevEggs;

  if( NumberOfContainers == 3 ) return;

  i = CINT( (ContDesc[4].Height/2) + .2f ) + 1;
  C4Eggs = ReDim( i, j );
  C4MatureEggs = ReDim( i );
  C4CumDevEggs = ReDim( i, j );

  EggArrays[4] = C4Eggs;
  EggMatureArrays[4] = C4MatureEggs;
  EggDevArrays[4] = C4CumDevEggs;

  if( NumberOfContainers == 4 ) return;
  
  i = CINT( (ContDesc[5].Height/2) + .2f ) + 1;
  C5Eggs = ReDim( i, j );
  C5MatureEggs = ReDim( i );
  C5CumDevEggs = ReDim( i, j );

  EggArrays[5] = C5Eggs;
  EggMatureArrays[5] = C5MatureEggs;
  EggDevArrays[5] = C5CumDevEggs;

  if( NumberOfContainers == 5 ) return;

  i = CINT( (ContDesc[6].Height/2) + .2f ) + 1;
  C6Eggs = ReDim( i, j );
  C6MatureEggs = ReDim( i );
  C6CumDevEggs = ReDim( i, j );

  EggArrays[6] = C6Eggs;
  EggMatureArrays[6] = C6MatureEggs;
  EggDevArrays[6] = C6CumDevEggs;

  if( NumberOfContainers == 6 ) return;
  
  i = CINT( (ContDesc[7].Height/2) + .2f ) + 1;
  C7Eggs = ReDim( i, j );
  C7MatureEggs = ReDim( i );
  C7CumDevEggs = ReDim( i, j );

  EggArrays[7] = C7Eggs;
  EggMatureArrays[7] = C7MatureEggs;
  EggDevArrays[7] = C7CumDevEggs;

  if( NumberOfContainers == 7 ) return;
  
  i = CINT( (ContDesc[8].Height/2) + .2f ) + 1;
  C8Eggs = ReDim( i, j );
  C8MatureEggs = ReDim( i );
  C8CumDevEggs = ReDim( i, j );

  EggArrays[8] = C8Eggs;
  EggMatureArrays[8] = C8MatureEggs;
  EggDevArrays[8] = C8CumDevEggs;

  if( NumberOfContainers == 8 ) return;
  
  i = CINT( (ContDesc[9].Height/2) + .2f ) + 1;
  C9Eggs = ReDim( i, j );
  C9MatureEggs = ReDim( i );
  C9CumDevEggs = ReDim( i, j );

  EggArrays[9] = C9Eggs;
  EggMatureArrays[9] = C9MatureEggs;
  EggDevArrays[9] = C9CumDevEggs;
}


float * csport::ReDim( int length )
{
  float * array = new float[length];
  for( int i = 0; i < length; i++ ) {
    array[i] = 0;
  }
  
  return array;
}


float ** csport::ReDim( int numRows, int numCols )
{
  float ** array = new float*[numRows];
  for( int i = 0; i < numRows; i++ ) {
    array[i] = new float[numCols];
    for( int j = 0; j < numCols; j++ ) {
      array[i][j] = 0;
    }
  }

  return array;
}


void csport::ContReadAll(void)
{
  NumberOfContainers = (int) Location_.Containers_.size();

  for( int i = 1; i <= NumberOfContainers; i++ ) {
    input::Container * container = Location_.Containers_[i-1];

    ContDesc[i].title = container->Name_;
    ContDesc[i].Length = (float) container->Length_;
    ContDesc[i].Wide = (float) container->Width_;
    ContDesc[i].Height = (float) container->Height_;
    ContDesc[i].Diameter = (float) container->Diameter_;
    ContDesc[i].Loss = (float) container->MonthlyTurnoverRate_;
    ContDesc[i].density = (float) container->Density_;
    ContDesc[i].Cover = container->IsCovered_;
    ContDesc[i].CoverRed = (float) container->CoverReduction_;
    ContDesc[i].Exposure = (float) container->SunExposure_;
    ContDesc[i].Cooling = (float) container->Cooling_;
    ContDesc[i].DrawDown = (float) container->Drawdown_;
    ContDesc[i].WaterShedRatio = (float) container->WatershedRatio_;
    ContDesc[i].InitFood = (float) container->InitFood_;
    ContDesc[i].Month1 = (float) container->FoodGainJan_;
    ContDesc[i].Month2 = (float) container->FoodGainFeb_;
    ContDesc[i].Month3 = (float) container->FoodGainMar_;
    ContDesc[i].Month4 = (float) container->FoodGainApr_;
    ContDesc[i].Month5 = (float) container->FoodGainMay_;
    ContDesc[i].Month6 = (float) container->FoodGainJun_;
    ContDesc[i].Month7 = (float) container->FoodGainJul_;
    ContDesc[i].Month8 = (float) container->FoodGainAug_;
    ContDesc[i].Month9 = (float) container->FoodGainSep_;
    ContDesc[i].Month10 = (float) container->FoodGainOct_;
    ContDesc[i].Month11 = (float) container->FoodGainNov_;
    ContDesc[i].Month12 = (float) container->FoodGainDec_;
    ContDesc[i].FoodDecayRate = (float) container->FoodDecayRate_;
    ContDesc[i].InitialEggs = (float) container->InitEggs_;

  // initial density setup
  ContDensity[i].Untreated = ContDesc[i].density;
  ContDensity[i].Treated = 0;
  ContDensity[i].Excluded = 0;
  }
}
  
  
void csport::ControlFileRead(void)
{
  SRTreatNum = 0;
  SRStartDay = 0;
  SRTreatInter = 0;
  for( int i = 1; i <= MaxNumCt; i++ ) {
    SRReductRate[i] = 0.0;
  }

  OETreatNum = 0;
  OEStartDay = 0;
  OETreatInter = 0;
  for( int i = 1; i <= MaxNumCt; i++ ) {
    OEReductRate[i] = 0.0;
    OERecoverRate[i] = 0.0;
  }

  SMTreatNum = 0;
  SMStartDay = 0;
  SMTreatInter = 0;
  SMNumber = 0;
  SMRate = 0;
  SMComp = 0;
  SMSurvRatio = 0;

  SSNumTrts = 0;
  SSStartDay = 0;
  SSInterval = 0;
  SSMosqDensity = 0;
  SSMortOut = 0;
  SSMortIn = 0;

  RSNumTrts = 0;
  RSStartDay = 0;
  RSInterval = 0;
  RSMaxMort = 0;
  RSDaysMax = 0;
  RSDaysRes = 0;
  RSPropSurfTrt = 0;
  RSPropHouseTrt = 0;

  for( int i = 1; i <= MaxNumCt; i++ ) {
    LICont[i].NumTrts = 0;
    LICont[i].Start = 0;
    LICont[i].Interval = 0;
    LICont[i].Proportion = 0;
    LICont[i].Lag = 0;
    LICont[i].Mort = 0;
    LICont[i].MaxEff = 0;
    LICont[i].DecEff = 0;
    LICont[i].DryActivity = 0;
  }

  for( int i = 1; i <= MaxNumCt; i++ ) {
    EDCont[i].NumTrts = 0;
    EDCont[i].StartDay = 0;
    EDCont[i].Interval = 0;
    EDCont[i].Reduction = 0;
  }

}


float csport::DevelopmentRate( float p25, float tempt, float dha, float dh, float th2, float r)
{
  float tempexpr1 = (dha / r) * (((float)1 / 298) - (1 / tempt));
  float tempexpr2 = (dh / r) * ((1 / th2) - (1 / tempt));

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

  float numerator = p25 * (tempt / 298) * exp(tempexpr1);
  float denominator = 1 + exp(tempexpr2);
  float DevelopmentRate = numerator / denominator * 24;

  return DevelopmentRate;
}


void csport::ReadDefaultParms(void)
{
  EulerSteps = (int) Location_.Biology_->Larvae->NumberEulerSteps;
  RndFood = Location_.Biology_->Larvae->Food->UseRandomFood;
  DengueOutput = true;

  // Run simulation for extent of available weather
  StartDate = Location_.Weather_->GetWeatherPeriod().begin().year();
  EndDate = Location_.Weather_->GetWeatherPeriod().end().year();

  //CurSimYear = Location_.StartYear_;
  //EndSimYear = Location_.EndYear_;
  // TODO - making this year agnostic, rather an indexed value
  CurSimYear = 1;
  EndSimYear = EndDate - StartDate + 1;



}


bool csport::Year1NoPop(void)
{
  return (Year == 1) && !PopFile;
}


void csport::WaterDepthTemp(void)
{
  // uses global variable Day, which gets referenced in water functions, clunky
  for( Day = 1; Day <= YrLen; Day++ ) {
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContDesc[i].WaterShedRatio == 0 ) {
        // manually filled every day
        ContEnv[Day][i].Depth = ContDesc[i].Height;
      }
      else {
        ContEnv[Day][i].Depth = CalcWaterDepth( i, ContEnv[Day -1][i].Depth, Rain[Day] );
      }
    }
  }

  for( Day = 1; Day <= YrLen; Day++ ) {
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].Depth <= 0 ) {
        // container empty, use today's air temps for container enviroment
        ContEnv[Day][i].TempMax = TemperatureMax[Day];
        ContEnv[Day][i].TempMin = TemperatureMin[Day];
        ContEnv[Day][i].TempAvg= TemperatureAvg[Day];
      }
      else {
        CalcWaterTemps( i, Day );
      }
    }
  }
}


void csport::WeaReadFile(void)
{
  // read first year of weather from Location_
  input::WeatherYear * wy = Location_.Weather_->GetWeatherForYear( StartDate );

  for( int i = 1; i <= YrLen; i++ ) {
    input::WeatherDay * wd = wy->GetDay(i);
    TemperatureMax[i] = (float) wd->MaxTemp_;
    TemperatureMin[i] = (float) wd->MinTemp_;
    TemperatureAvg[i] = (float) wd->AvgTemp_;
    SD[i] = (float) wd->SatDef_;
    Rain[i] = (float) wd->Precip_;
    RelHumid[i] = (float) wd->RelHum_;
  }
}


// emulate CS 1.0 CINT() which does banker's rounding
int csport::CINT( float value )
{
  float integer;
  float fraction;
  fraction = modf( value, &integer );

  // special case for banker's rounding
  if( 0.49 < abs(fraction) && abs(fraction) < 0.51 ) {
    int bitwiseAnd = ( (int) integer ) & 1;

    if( bitwiseAnd ) {
      // integer is odd, return nearest even number
      if( integer > 0 )
        return ((int)integer) + 1;
      else
        return ((int)integer) - 1;
    }
    else {
      // integer is even, return integer
      return ((int)integer);
    }
  }
  else {
    if( abs(fraction) > 0.5 ) {
      if( fraction > 0 )
		    return (int)ceil( value );
      else
        return (int)floor( value );
	  }
    else { 
      if( fraction > 0 )
		    return (int)floor( value );
      else
		    return (int)ceil( value );
	  }
  }
}


// emulate CS 1.0 Int()
int csport::INT( float value )
{
  return (int)floor(value);
}


//========
// CIML1.h
//========


void csport::MainLoop(void)
{
  CalcSeasonalFood();
  CalcLISurvival();

  // CS 1.0 calls ReDim() on these arrays to clear them to zero
  for( int i = 0; i < MaxNumCt+1; i++ ) {
    HatchLevel[i] = 0;
    DevRateEggs[i] = 0;
    DevRateLarv[i] = 0;
    DevRatePupae[i] = 0;
    EggInputLevel[i] = 0;
    SurvEggs[i] = 0;
    NewlyHatched[i] = 0;
    MaxLarvWt[i] = 0;
    NewPupae[i] = 0;
    PupaeWt[i] = 0;
    ReturnCtOvi[i] = 0;
    CumulativeFemales[i] = 0;   // added to track cumulative females
    //cadavers[i] = 0;          //CS 1.0 does not clear this - this adds extra food on first day of continuing years
  }

  for( int i = 0; i < YrLen+1; i++ ) {
    MalePop[i] = 0;
  }

  DengueOutDescription DengueData[YrLen+1];


#ifdef _DEBUG
  std::stringstream ss;
  ss << Year;
  std::string ssYear = ss.str();

  _locationLog = output::LocationLog( "CSP 1.0 - Year " + ssYear + " - Location" );
#endif


  for( Day = 1; Day <= YrLen; Day++ ) {


//==========================================
//Calculate development rates for each stage
//==========================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      DevRateEggs[i] = DevelopmentRate( EggsP25, ContEnv[Day][i].TempAvg + 273.15f, EggsDHa, EggsDH, EggsTh2, r );
      DevRateLarv[i] = DevelopmentRate( LarvP25, ContEnv[Day][i].TempAvg + 273.15f, LarvDHa, LarvDH, LarvTh2, r );

      if( ContEnv[Day][i].TempAvg <= 13.4f )
        et[i] = 0;
      else
        et[i] = (DevRateLarv[i] - .00146f) / (DevRateLarv26 - .00146f);

      DevRatePupae[i] = DevelopmentRate(PupaeP25, ContEnv[Day][i].TempAvg + 273.15f, PupaeDHa, PupaeDH, PupaeTh2, r);
    }

    float DevRateAdult = DevelopmentRate(AdultP25, TemperatureAvg[Day] + 273.15f, AdultDHa, AdultDH, AdultTh2, r);


//===================================
//Initialize the containers with eggs
//===================================


    if( Year1NoPop() && Day == 1 ) {

      for( int i = 1; i <= NumberOfContainers; i++ ) {
        EggInputLevel[i] = INT((ContEnv[1][i].Depth / 2)) + 1;
        if( EggInputLevel[i] > CINT((ContDesc[i].Height / 2) + .2f) )
          EggInputLevel[i] = CINT((ContDesc[i].Height / 2) + .2f);
      }

      C1MatureEggs[EggInputLevel[1]] = ContDesc[1].InitialEggs;

      if( NumberOfContainers > 1 )
        C2MatureEggs[EggInputLevel[2]] = ContDesc[2].InitialEggs;

      if( NumberOfContainers > 2 )
        C3MatureEggs[EggInputLevel[3]] = ContDesc[3].InitialEggs;
      
      if( NumberOfContainers > 3 )
        C4MatureEggs[EggInputLevel[4]] = ContDesc[4].InitialEggs;
      
      if( NumberOfContainers > 4 )
        C5MatureEggs[EggInputLevel[5]] = ContDesc[5].InitialEggs;
      
      if( NumberOfContainers > 5 )
        C6MatureEggs[EggInputLevel[6]] = ContDesc[6].InitialEggs;
      
      if( NumberOfContainers > 6 )
        C7MatureEggs[EggInputLevel[7]] = ContDesc[7].InitialEggs;
      
      if( NumberOfContainers > 7 )
        C8MatureEggs[EggInputLevel[8]] = ContDesc[8].InitialEggs;
      
      if( NumberOfContainers > 8 )
        C9MatureEggs[EggInputLevel[9]] = ContDesc[9].InitialEggs;
    }

//=======================================================
//Adjust container densities for( nominal losses and gains
//=======================================================


    if( (Day % 30) == 0 || Day == 1 ) {
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        float ContainerLoss = ContDensity[i].Untreated * ContDesc[i].Loss;
        float ContainerGain = ContDesc[i].density * ContDesc[i].Loss;
        ContDensity[i].Untreated = ContDensity[i].Untreated - ContainerLoss + ContainerGain;
      }
    }


//=======================================
//Subtract source reduction containers.
// These containers are regained from
// the above adjustment for( nominal gains
// and losses.
//=======================================


    if( SR && SRSchedule[Day] ){
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        ContDensity[i].Untreated = ContDensity[i].Untreated * (1 - SRReductRate[i]);
      }
    }


//======================================================
//Return or remove old oviposition exclusion containers.
//  Need to check even if( the OE% flag is FALSE - may
//  still be some excluded containers from a previous
//  year.
//======================================================


    if( (Day % 30) == 0 ) {
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        if( ContDensity[i].Excluded > 0 ) {                                 // todo this isn't zeroed initially
          float OEConverted = ContDensity[i].Excluded * OERecoverRate[i];
          float OELoss = ContDensity[i].Excluded * ContDesc[i].Loss;
          ContDensity[i].Untreated = ContDensity[i].Untreated + OEConverted;
          ContDensity[i].Excluded = ContDensity[i].Excluded - OEConverted - OELoss;

          // why only for values between 0 and 1? what about 6.55 containers or 4.9823?
          if( ContDensity[i].Excluded < 1 )
            ContDensity[i].Excluded = 0;
        }
      }
    }


//===========================================
//Adjust containers for oviposition exclusion
//===========================================


    if( OE && OESchedule[Day] ) {
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        float ContChange = ContDensity[i].Untreated * OEReductRate[i];
        ContDensity[i].Untreated = ContDensity[i].Untreated - ContChange;
        ContDensity[i].Excluded = ContDensity[i].Excluded + ContChange;
      }
    }


//===================================================
//Return or remove treated containers.
//  Need to check even if( the LI% flag is FALSE - may
//  still be some treated containers from a previous
//  year.
//===================================================


    // nominal monthly losses - lost to environment
    if( (Day % 30) == 0 ) {
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        if( ContDensity[i].Treated > 0 ) {
          float LILoss = ContDensity[i].Treated * ContDesc[i].Loss;
          ContDensity[i].Treated = ContDensity[i].Treated - LILoss;
          if( ContDensity[i].Treated < 1 )
            ContDensity[i].Treated = 0;
        }
      }
    }

    // container conversion - LI treatment effect over
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( (ContDensity[i].Treated) > 0 && (LISurv[Day][i] == 1) ) {
        ContDensity[i].Untreated = ContDensity[i].Untreated + ContDensity[i].Treated;
        ContDensity[i].Treated = 0;
      }
    }


//=========================================
//Adjust containers for( larvicidal activity
//=========================================


    if( LI ) {
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        if( (LISurv[Day][i] < 1) && (LISchedule[i][Day]) ) {
          float ContTreated = ContDensity[i].Untreated * LICont[i].Proportion;
          ContDensity[i].Untreated = ContDensity[i].Untreated - ContTreated;
          ContDensity[i].Treated = ContDensity[i].Treated + ContTreated;
        }
      }
    }


//==================================
//Egg survival vs saturation deficit
//==================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].Depth == 0 ) {
        if( ContDesc[i].Exposure > .85 ) {
          EggsSurvSdDlyCt[i] = eggdrysu;
        }
        else {
          if( SD[Day] <= egglsdth ) {
            EggsSurvSdDlyCt[i] = egglsdsu;
          }
          else if( SD[Day] >= egghsdth ) {
            EggsSurvSdDlyCt[i] = egghsdsu;
          }
          else {
            float eggsdslope = (egglsdsu - egghsdsu) / (egghsdth - egglsdth);
            EggsSurvSdDlyCt[i] = egglsdsu - ((SD[Day] - egglsdth) * eggsdslope);
          }
        }
      }
      else {
        EggsSurvSdDlyCt[i] = eggwetsu;
      }
    }


//===========================
//Egg survival vs temperature
//===========================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].TempMin <= eggtemp1 ) {
        EggsSurvTempDlyCt[i] = .05f;
      }
      else if( ContEnv[Day][i].TempMin >= eggtemp2 ) {
        EggsSurvTempDlyCt[i] = 1;
      }
      else {
        float eggltempslope = .95f / (eggtemp1 - eggtemp2);
        EggsSurvTempDlyCt[i] = 1 + ((eggtemp2 - ContEnv[Day][i].TempMin) * eggltempslope);
      }

      if( ContEnv[Day][i].TempMax >= eggtemp4 ) {
        EggsSurvTempDlyCt[i] = EggsSurvTempDlyCt[i] * .05f;
      }
      else if( ContEnv[Day][i].TempMax <= eggtemp3 ) {
        EggsSurvTempDlyCt[i] = EggsSurvTempDlyCt[i] * 1;
      }
      else {
        float egghtempslope = .95f / (eggtemp3 - eggtemp4);
        EggsSurvTempDlyCt[i] = EggsSurvTempDlyCt[i] * (1 + ((ContEnv[Day][i].TempMax - eggtemp3) * egghtempslope));
      }
    }


//=========================
//Egg survival vs predation
//=========================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].TempAvg <= PredLT ) {
        EggsSurvPredDlyCt[i] = PredSurLT;
      }
      else if( ContEnv[Day][i].TempAvg >= PredHT ) {
        EggsSurvPredDlyCt[i] = PredSurHT;
      }
      else {
        float Slope = (PredSurLT - PredSurHT) / (PredHT - PredLT);
        EggsSurvPredDlyCt[i] = PredSurLT - ((ContEnv[Day][i].TempAvg - PredLT) * Slope);
      }
    }


//=======================
//Cumulative Egg Survival
//=======================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      SurvEggs[i] = EggsSurvSdDlyCt[i] * EggsSurvTempDlyCt[i] * EggSurvNom * EggsSurvPredDlyCt[i];
    }


//=====================================
//Apply Egg Destruction to Egg Survival
//=====================================


    if( ED ) {
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        if( EDSchedule[i][Day] ) {
          SurvEggs[i] = SurvEggs[i] * (1 - EDCont[i].Reduction);
        }
      }
    }


//==========================================================
//Determine the max hatch level for eggs for the current day
//==========================================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      HatchLevel[i] = CINT((ContEnv[Day][i].Depth / 2) + .2f);          // TODO this can be zero... violates egg level semantics
      if( HatchLevel[i] > CINT((ContDesc[i].Height / 2) + .2f) )
        HatchLevel[i] = CINT((ContDesc[i].Height / 2) + .2f);
    }


//====
//Eggs
//====


    for( int level = 1; level <= CINT((ContDesc[1].Height / 2) + .2f); level++ ) {
      C1MatureEggs[level] = C1MatureEggs[level] * SurvEggs[1];
      if( C1Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C1Eggs[level][MaxAgeEggs + 1];
        for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
          if( Age == MaxAgeEggs ) {
            if( C1Eggs[level][Age] > 0 ) {
              NumberCohorts = NumberCohorts - 1;
              C1Eggs[level][MaxAgeEggs + 1] = C1Eggs[level][MaxAgeEggs + 1] - 1;
              if( C1CumDevEggs[level][Age] > .95 ) {
                if( ContEnv[Day][1].TempAvg < eggdiapausetemp ) {
                  C1MatureEggs[level] = C1MatureEggs[level] + (C1Eggs[level][Age] * SurvEggs[1]);
                }
                else {
                  if( level <= HatchLevel[1] ) {
                    // all eggs hatch
                    NewlyHatched[1] = NewlyHatched[1] + C1Eggs[level][Age] * SurvEggs[1];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C1MatureEggs[level] = C1MatureEggs[level] + ((1 - PropHatchSpont) * C1Eggs[level][Age] * SurvEggs[1]);
                    NewlyHatched[1] = NewlyHatched[1] + (PropHatchSpont * C1Eggs[level][Age] * SurvEggs[1]);
                  }
                }
              }
            }
          }
          else if( C1Eggs[level][Age] == 0 ) {
            // go to next age
          }
          else {
            NumberCohorts = NumberCohorts - 1;
            if( C1CumDevEggs[level][Age] <= .95 ) {
              C1Eggs[level][Age + 1] = C1Eggs[level][Age] * SurvEggs[1];
              C1CumDevEggs[level][Age + 1] = C1CumDevEggs[level][Age] + DevRateEggs[1];
              // check for zero population cohort
              if( C1Eggs[level][Age + 1] <= 0 ) {
                C1Eggs[level][MaxAgeEggs + 1] = C1Eggs[level][MaxAgeEggs + 1] - 1;
                C1Eggs[level][Age + 1] = 0;
                C1CumDevEggs[level][Age + 1] = 0;
              }
            }
            else {
              C1Eggs[level][MaxAgeEggs + 1] = C1Eggs[level][MaxAgeEggs + 1] - 1;
              if( ContEnv[Day][1].TempAvg < eggdiapausetemp ) {
                C1MatureEggs[level] = C1MatureEggs[level] + (C1Eggs[level][Age] * SurvEggs[1]);
              }
              else {
                if( level <= HatchLevel[1] ) {
                  NewlyHatched[1] = NewlyHatched[1] + C1Eggs[level][Age] * SurvEggs[1];
                }
                else {
                  // proportion hatch spontaneously, rest become mature eggs
                  C1MatureEggs[level] = C1MatureEggs[level] + ((1 - PropHatchSpont) * C1Eggs[level][Age] * SurvEggs[1]);
                  NewlyHatched[1] = NewlyHatched[1] + (PropHatchSpont * C1Eggs[level][Age] * SurvEggs[1]);
                }
              }
            }
          }
          C1Eggs[level][Age] = 0;
          C1CumDevEggs[level][Age] = 0;
          if( NumberCohorts <= 0 ) {
          	break;
          }
        } // age
      }
    } // level
    if( NumberOfContainers > 1 ) {
      for( int level = 1; level <= CINT((ContDesc[2].Height / 2) + .2f); level++ ) {
        C2MatureEggs[level] = C2MatureEggs[level] * SurvEggs[2];
        if( C2Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C2Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C2Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C2Eggs[level][MaxAgeEggs + 1] = C2Eggs[level][MaxAgeEggs + 1] - 1;
                if( C2CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][2].TempAvg < eggdiapausetemp ) {
                    C2MatureEggs[level] = C2MatureEggs[level] + (C2Eggs[level][Age] * SurvEggs[2]);
                  }
                  else {
                    if( level <= HatchLevel[2] ) {
                      // all eggs hatch
                      NewlyHatched[2] = NewlyHatched[2] + C2Eggs[level][Age] * SurvEggs[2];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C2MatureEggs[level] = C2MatureEggs[level] + ((1 - PropHatchSpont) * C2Eggs[level][Age] * SurvEggs[2]);
                      NewlyHatched[2] = NewlyHatched[2] + (PropHatchSpont * C2Eggs[level][Age] * SurvEggs[2]);
                    }
                  }
                }
              }
            }
            else if( C2Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C2CumDevEggs[level][Age] <= .95 ) {
                C2Eggs[level][Age + 1] = C2Eggs[level][Age] * SurvEggs[2];
                C2CumDevEggs[level][Age + 1] = C2CumDevEggs[level][Age] + DevRateEggs[2];
                // check for zero population cohort
                if( C2Eggs[level][Age + 1] <= 0 ) {
                  C2Eggs[level][MaxAgeEggs + 1] = C2Eggs[level][MaxAgeEggs + 1] - 1;
                  C2Eggs[level][Age + 1] = 0;
                  C2CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C2Eggs[level][MaxAgeEggs + 1] = C2Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][2].TempAvg < eggdiapausetemp ) {
                  C2MatureEggs[level] = C2MatureEggs[level] + (C2Eggs[level][Age] * SurvEggs[2]);
                }
                else {
                  if( level <= HatchLevel[2] ) {
                    // all eggs hatch
                    NewlyHatched[2] = NewlyHatched[2] + C2Eggs[level][Age] * SurvEggs[2];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C2MatureEggs[level] = C2MatureEggs[level] + ((1 - PropHatchSpont) * C2Eggs[level][Age] * SurvEggs[2]);
                    NewlyHatched[2] = NewlyHatched[2] + (PropHatchSpont * C2Eggs[level][Age] * SurvEggs[2]);
                  }
                }
              }
            }
            C2Eggs[level][Age] = 0;
            C2CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 2 ) {
      for( int level = 1; level <= CINT((ContDesc[3].Height / 2) + .2f); level++ ) {
        C3MatureEggs[level] = C3MatureEggs[level] * SurvEggs[3];
        if( C3Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C3Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C3Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C3Eggs[level][MaxAgeEggs + 1] = C3Eggs[level][MaxAgeEggs + 1] - 1;
                if( C3CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][3].TempAvg < eggdiapausetemp ) {
                    C3MatureEggs[level] = C3MatureEggs[level] + (C3Eggs[level][Age] * SurvEggs[3]);
                  }
                  else {
                    if( level <= HatchLevel[3] ) {
                      // all eggs hatch
                      NewlyHatched[3] = NewlyHatched[3] + C3Eggs[level][Age] * SurvEggs[3];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C3MatureEggs[level] = C3MatureEggs[level] + ((1 - PropHatchSpont) * C3Eggs[level][Age] * SurvEggs[3]);
                      NewlyHatched[3] = NewlyHatched[3] + (PropHatchSpont * C3Eggs[level][Age] * SurvEggs[3]);
                    }
                  }
                }
              }
            }
            else if( C3Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C3CumDevEggs[level][Age] <= .95 ) {
                C3Eggs[level][Age + 1] = C3Eggs[level][Age] * SurvEggs[3];
                C3CumDevEggs[level][Age + 1] = C3CumDevEggs[level][Age] + DevRateEggs[3];
                // check for zero population cohort
                if( C3Eggs[level][Age + 1] <= 0 ) {
                  C3Eggs[level][MaxAgeEggs + 1] = C3Eggs[level][MaxAgeEggs + 1] - 1;
                  C3Eggs[level][Age + 1] = 0;
                  C3CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C3Eggs[level][MaxAgeEggs + 1] = C3Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][3].TempAvg < eggdiapausetemp ) {
                  C3MatureEggs[level] = C3MatureEggs[level] + (C3Eggs[level][Age] * SurvEggs[3]);
                }
                else {
                  if( level <= HatchLevel[3] ) {
                    // all eggs hatch
                    NewlyHatched[3] = NewlyHatched[3] + C3Eggs[level][Age] * SurvEggs[3];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C3MatureEggs[level] = C3MatureEggs[level] + ((1 - PropHatchSpont) * C3Eggs[level][Age] * SurvEggs[3]);
                    NewlyHatched[3] = NewlyHatched[3] + (PropHatchSpont * C3Eggs[level][Age] * SurvEggs[3]);
                  }
                }
              }
            }
            C3Eggs[level][Age] = 0;
            C3CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 3 ) {
      for( int level = 1; level <= CINT((ContDesc[4].Height / 2) + .2f); level++ ) {
        C4MatureEggs[level] = C4MatureEggs[level] * SurvEggs[4];
        if( C4Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C4Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C4Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C4Eggs[level][MaxAgeEggs + 1] = C4Eggs[level][MaxAgeEggs + 1] - 1;
                if( C4CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][4].TempAvg < eggdiapausetemp ) {
                    C4MatureEggs[level] = C4MatureEggs[level] + (C4Eggs[level][Age] * SurvEggs[4]);
                  }
                  else {
                    if( level <= HatchLevel[4] ) {
                      // all eggs hatch
                      NewlyHatched[4] = NewlyHatched[4] + C4Eggs[level][Age] * SurvEggs[4];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C4MatureEggs[level] = C4MatureEggs[level] + ((1 - PropHatchSpont) * C4Eggs[level][Age] * SurvEggs[4]);
                      NewlyHatched[4] = NewlyHatched[4] + (PropHatchSpont * C4Eggs[level][Age] * SurvEggs[4]);
                    }
                  }
                }
              }
            }
            else if( C4Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C4CumDevEggs[level][Age] <= .95 ) {
                C4Eggs[level][Age + 1] = C4Eggs[level][Age] * SurvEggs[4];
                C4CumDevEggs[level][Age + 1] = C4CumDevEggs[level][Age] + DevRateEggs[4];
                // check for zero population cohort
                if( C4Eggs[level][Age + 1] <= 0 ) {
                  C4Eggs[level][MaxAgeEggs + 1] = C4Eggs[level][MaxAgeEggs + 1] - 1;
                  C4Eggs[level][Age + 1] = 0;
                  C4CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C4Eggs[level][MaxAgeEggs + 1] = C4Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][4].TempAvg < eggdiapausetemp ) {
                  C4MatureEggs[level] = C4MatureEggs[level] + (C4Eggs[level][Age] * SurvEggs[4]);
                }
                else {
                  if( level <= HatchLevel[4] ) {
                    // all eggs hatch
                    NewlyHatched[4] = NewlyHatched[4] + C4Eggs[level][Age] * SurvEggs[4];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C4MatureEggs[level] = C4MatureEggs[level] + ((1 - PropHatchSpont) * C4Eggs[level][Age] * SurvEggs[4]);
                    NewlyHatched[4] = NewlyHatched[4] + (PropHatchSpont * C4Eggs[level][Age] * SurvEggs[4]);
                  }
                }
              }
            }
            C4Eggs[level][Age] = 0;
            C4CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 4 ) {
      for( int level = 1; level <= CINT((ContDesc[5].Height / 2) + .2f); level++ ) {
        C5MatureEggs[level] = C5MatureEggs[level] * SurvEggs[5];
        if( C5Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C5Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C5Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C5Eggs[level][MaxAgeEggs + 1] = C5Eggs[level][MaxAgeEggs + 1] - 1;
                if( C5CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][5].TempAvg < eggdiapausetemp ) {
                    C5MatureEggs[level] = C5MatureEggs[level] + (C5Eggs[level][Age] * SurvEggs[5]);
                  }
                  else {
                    if( level <= HatchLevel[5] ) {
                      // all eggs hatch
                      NewlyHatched[5] = NewlyHatched[5] + C5Eggs[level][Age] * SurvEggs[5];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C5MatureEggs[level] = C5MatureEggs[level] + ((1 - PropHatchSpont) * C5Eggs[level][Age] * SurvEggs[5]);
                      NewlyHatched[5] = NewlyHatched[5] + (PropHatchSpont * C5Eggs[level][Age] * SurvEggs[5]);
                    }
                  }
                }
              }
            }
            else if( C5Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C5CumDevEggs[level][Age] <= .95 ) {
                C5Eggs[level][Age + 1] = C5Eggs[level][Age] * SurvEggs[5];
                C5CumDevEggs[level][Age + 1] = C5CumDevEggs[level][Age] + DevRateEggs[5];
                // check for zero population cohort
                if( C5Eggs[level][Age + 1] <= 0 ) {
                  C5Eggs[level][MaxAgeEggs + 1] = C5Eggs[level][MaxAgeEggs + 1] - 1;
                  C5Eggs[level][Age + 1] = 0;
                  C5CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C5Eggs[level][MaxAgeEggs + 1] = C5Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][5].TempAvg < eggdiapausetemp ) {
                  C5MatureEggs[level] = C5MatureEggs[level] + (C5Eggs[level][Age] * SurvEggs[5]);
                }
                else {
                  if( level <= HatchLevel[5] ) {
                    // all eggs hatch
                    NewlyHatched[5] = NewlyHatched[5] + C5Eggs[level][Age] * SurvEggs[5];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C5MatureEggs[level] = C5MatureEggs[level] + ((1 - PropHatchSpont) * C5Eggs[level][Age] * SurvEggs[5]);
                    NewlyHatched[5] = NewlyHatched[5] + (PropHatchSpont * C5Eggs[level][Age] * SurvEggs[5]);
                  }
                }
              }
            }
            C5Eggs[level][Age] = 0;
            C5CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 5 ) {
      for( int level = 1; level <= CINT((ContDesc[6].Height / 2) + .2f); level++ ) {
        C6MatureEggs[level] = C6MatureEggs[level] * SurvEggs[6];
        if( C6Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C6Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C6Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C6Eggs[level][MaxAgeEggs + 1] = C6Eggs[level][MaxAgeEggs + 1] - 1;
                if( C6CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][6].TempAvg < eggdiapausetemp ) {
                    C6MatureEggs[level] = C6MatureEggs[level] + (C6Eggs[level][Age] * SurvEggs[6]);
                  }
                  else {
                    if( level <= HatchLevel[6] ) {
                      // all eggs hatch
                      NewlyHatched[6] = NewlyHatched[6] + C6Eggs[level][Age] * SurvEggs[6];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C6MatureEggs[level] = C6MatureEggs[level] + ((1 - PropHatchSpont) * C6Eggs[level][Age] * SurvEggs[6]);
                      NewlyHatched[6] = NewlyHatched[6] + (PropHatchSpont * C6Eggs[level][Age] * SurvEggs[6]);
                    }
                  }
                }
              }
            }
            else if( C6Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C6CumDevEggs[level][Age] <= .95 ) {
                C6Eggs[level][Age + 1] = C6Eggs[level][Age] * SurvEggs[6];
                C6CumDevEggs[level][Age + 1] = C6CumDevEggs[level][Age] + DevRateEggs[6];
                // check for zero population cohort
                if( C6Eggs[level][Age + 1] <= 0 ) {
                  C6Eggs[level][MaxAgeEggs + 1] = C6Eggs[level][MaxAgeEggs + 1] - 1;
                  C6Eggs[level][Age + 1] = 0;
                  C6CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C6Eggs[level][MaxAgeEggs + 1] = C6Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][6].TempAvg < eggdiapausetemp ) {
                  C6MatureEggs[level] = C6MatureEggs[level] + (C6Eggs[level][Age] * SurvEggs[6]);
                }
                else {
                  if( level <= HatchLevel[6] ) {
                    // all eggs hatch
                    NewlyHatched[6] = NewlyHatched[6] + C6Eggs[level][Age] * SurvEggs[6];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C6MatureEggs[level] = C6MatureEggs[level] + ((1 - PropHatchSpont) * C6Eggs[level][Age] * SurvEggs[6]);
                    NewlyHatched[6] = NewlyHatched[6] + (PropHatchSpont * C6Eggs[level][Age] * SurvEggs[6]);
                  }
                }
              }
            }
            C6Eggs[level][Age] = 0;
            C6CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 6 ) {
      for( int level = 1; level <= CINT((ContDesc[7].Height / 2) + .2f); level++ ) {
        C7MatureEggs[level] = C7MatureEggs[level] * SurvEggs[7];
        if( C7Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C7Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C7Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C7Eggs[level][MaxAgeEggs + 1] = C7Eggs[level][MaxAgeEggs + 1] - 1;
                if( C7CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][7].TempAvg < eggdiapausetemp ) {
                    C7MatureEggs[level] = C7MatureEggs[level] + (C7Eggs[level][Age] * SurvEggs[7]);
                  }
                  else {
                    if( level <= HatchLevel[7] ) {
                      // all eggs hatch
                      NewlyHatched[7] = NewlyHatched[7] + C7Eggs[level][Age] * SurvEggs[7];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C7MatureEggs[level] = C7MatureEggs[level] + ((1 - PropHatchSpont) * C7Eggs[level][Age] * SurvEggs[7]);
                      NewlyHatched[7] = NewlyHatched[7] + (PropHatchSpont * C7Eggs[level][Age] * SurvEggs[7]);
                    }
                  }
                }
              }
            }
            else if( C7Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C7CumDevEggs[level][Age] <= .95 ) {
                C7Eggs[level][Age + 1] = C7Eggs[level][Age] * SurvEggs[7];
                C7CumDevEggs[level][Age + 1] = C7CumDevEggs[level][Age] + DevRateEggs[7];
                // check for zero population cohort
                if( C7Eggs[level][Age + 1] <= 0 ) {
                  C7Eggs[level][MaxAgeEggs + 1] = C7Eggs[level][MaxAgeEggs + 1] - 1;
                  C7Eggs[level][Age + 1] = 0;
                  C7CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C7Eggs[level][MaxAgeEggs + 1] = C7Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][7].TempAvg < eggdiapausetemp ) {
                  C7MatureEggs[level] = C7MatureEggs[level] + (C7Eggs[level][Age] * SurvEggs[7]);
                }
                else {
                  if( level <= HatchLevel[7] ) {
                    // all eggs hatch
                    NewlyHatched[7] = NewlyHatched[7] + C7Eggs[level][Age] * SurvEggs[7];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C7MatureEggs[level] = C7MatureEggs[level] + ((1 - PropHatchSpont) * C7Eggs[level][Age] * SurvEggs[7]);
                    NewlyHatched[7] = NewlyHatched[7] + (PropHatchSpont * C7Eggs[level][Age] * SurvEggs[7]);
                  }
                }
              }
            }
            C7Eggs[level][Age] = 0;
            C7CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 7 ) {
      for( int level = 1; level <= CINT((ContDesc[8].Height / 2) + .2f); level++ ) {
        C8MatureEggs[level] = C8MatureEggs[level] * SurvEggs[8];
        if( C8Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C8Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C8Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C8Eggs[level][MaxAgeEggs + 1] = C8Eggs[level][MaxAgeEggs + 1] - 1;
                if( C8CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][8].TempAvg < eggdiapausetemp ) {
                    C8MatureEggs[level] = C8MatureEggs[level] + (C8Eggs[level][Age] * SurvEggs[8]);
                  }
                  else {
                    if( level <= HatchLevel[8] ) {
                      // all eggs hatch
                      NewlyHatched[8] = NewlyHatched[8] + C8Eggs[level][Age] * SurvEggs[8];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C8MatureEggs[level] = C8MatureEggs[level] + ((1 - PropHatchSpont) * C8Eggs[level][Age] * SurvEggs[8]);
                      NewlyHatched[8] = NewlyHatched[8] + (PropHatchSpont * C8Eggs[level][Age] * SurvEggs[8]);
                    }
                  }
                }
              }
            }
            else if( C8Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C8CumDevEggs[level][Age] <= .95 ) {
                C8Eggs[level][Age + 1] = C8Eggs[level][Age] * SurvEggs[8];
                C8CumDevEggs[level][Age + 1] = C8CumDevEggs[level][Age] + DevRateEggs[8];
                // check for zero population cohort
                if( C8Eggs[level][Age + 1] <= 0 ) {
                  C8Eggs[level][MaxAgeEggs + 1] = C8Eggs[level][MaxAgeEggs + 1] - 1;
                  C8Eggs[level][Age + 1] = 0;
                  C8CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C8Eggs[level][MaxAgeEggs + 1] = C8Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][8].TempAvg < eggdiapausetemp ) {
                  C8MatureEggs[level] = C8MatureEggs[level] + (C8Eggs[level][Age] * SurvEggs[8]);
                }
                else {
                  if( level <= HatchLevel[8] ) {
                    // all eggs hatch
                    NewlyHatched[8] = NewlyHatched[8] + C8Eggs[level][Age] * SurvEggs[8];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C8MatureEggs[level] = C8MatureEggs[level] + ((1 - PropHatchSpont) * C8Eggs[level][Age] * SurvEggs[8]);
                    NewlyHatched[8] = NewlyHatched[8] + (PropHatchSpont * C8Eggs[level][Age] * SurvEggs[8]);
                  }
                }
              }
            }
            C8Eggs[level][Age] = 0;
            C8CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }
    if( NumberOfContainers > 8 ) {
      for( int level = 1; level <= CINT((ContDesc[9].Height / 2) + .2f); level++ ) {
        C9MatureEggs[level] = C9MatureEggs[level] * SurvEggs[9];
        if( C9Eggs[level][MaxAgeEggs + 1] > 0 ) {
          int NumberCohorts = (int) C9Eggs[level][MaxAgeEggs + 1];
          for( int Age = MaxAgeEggs; Age >= 1; Age-- ) {
            if( Age == MaxAgeEggs ) {
              if( C9Eggs[level][Age] > 0 ) {
                NumberCohorts = NumberCohorts - 1;
                C9Eggs[level][MaxAgeEggs + 1] = C9Eggs[level][MaxAgeEggs + 1] - 1;
                if( C9CumDevEggs[level][Age] > .95 ) {
                  if( ContEnv[Day][9].TempAvg < eggdiapausetemp ) {
                    C9MatureEggs[level] = C9MatureEggs[level] + (C9Eggs[level][Age] * SurvEggs[9]);
                  }
                  else {
                    if( level <= HatchLevel[9] ) {
                      // all eggs hatch
                      NewlyHatched[9] = NewlyHatched[9] + C9Eggs[level][Age] * SurvEggs[9];
                    }
                    else {
                      // proportion hatch spontaneously, rest become mature eggs
                      C9MatureEggs[level] = C9MatureEggs[level] + ((1 - PropHatchSpont) * C9Eggs[level][Age] * SurvEggs[9]);
                      NewlyHatched[9] = NewlyHatched[9] + (PropHatchSpont * C9Eggs[level][Age] * SurvEggs[9]);
                    }
                  }
                }
              }
            }
            else if( C9Eggs[level][Age] == 0 ) {
              // go to next age
            }
            else {
              NumberCohorts = NumberCohorts - 1;
              if( C9CumDevEggs[level][Age] <= .95 ) {
                C9Eggs[level][Age + 1] = C9Eggs[level][Age] * SurvEggs[9];
                C9CumDevEggs[level][Age + 1] = C9CumDevEggs[level][Age] + DevRateEggs[9];
                // check for zero population cohort
                if( C9Eggs[level][Age + 1] <= 0 ) {
                  C9Eggs[level][MaxAgeEggs + 1] = C9Eggs[level][MaxAgeEggs + 1] - 1;
                  C9Eggs[level][Age + 1] = 0;
                  C9CumDevEggs[level][Age + 1] = 0;
                }
              }
              else {
                C9Eggs[level][MaxAgeEggs + 1] = C9Eggs[level][MaxAgeEggs + 1] - 1;
                if( ContEnv[Day][9].TempAvg < eggdiapausetemp ) {
                  C9MatureEggs[level] = C9MatureEggs[level] + (C9Eggs[level][Age] * SurvEggs[9]);
                }
                else {
                  if( level <= HatchLevel[9] ) {
                    // all eggs hatch
                    NewlyHatched[9] = NewlyHatched[9] + C9Eggs[level][Age] * SurvEggs[9];
                  }
                  else {
                    // proportion hatch spontaneously, rest become mature eggs
                    C9MatureEggs[level] = C9MatureEggs[level] + ((1 - PropHatchSpont) * C9Eggs[level][Age] * SurvEggs[9]);
                    NewlyHatched[9] = NewlyHatched[9] + (PropHatchSpont * C9Eggs[level][Age] * SurvEggs[9]);
                  }
                }
              }
            }
            C9Eggs[level][Age] = 0;
            C9CumDevEggs[level][Age] = 0;
            if( NumberCohorts <= 0 ) {
            	break;
            }
          } // age
        }
      } // level
    }


//=================================
//New larvae based on water level
//=================================
    // Eggs that hatch into dry containers die


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].Depth == 0 ) {
        NewlyHatched[i] = 0;
      }
    }


//=========================================
//Determine the amount of food for the day.
//=========================================
  // Apply food decay to existing food and previous days cadaver contribution

    for( int i = 1; i <= NumberOfContainers; i++ ) {
      float NaturalDecay = ContEnv[Day - 1][i].Food * ContDesc[i].FoodDecayRate;
      float PrevFood = ContEnv[Day - 1][i].Food - NaturalDecay;
      if( PrevFood < 0 ) {
        PrevFood = 0;
      }
      ContEnv[Day][i].Food = ContEnv[Day][i].Food + cadavers[i] + PrevFood;
    }


//==============================
//Larval survival vs temperature
//==============================


    for( int i = 1; i <= NumberOfContainers; i++ ) {

      // survival from minimum temperatures
      if( ContEnv[Day][i].TempMin <= LarvTemp1 ) {
        LarvSurvTempDlyCt[i] = .05f;
      }
      else if( ContEnv[Day][i].TempMin >= LarvTemp2 ) {
        LarvSurvTempDlyCt[i] = 1.0f;
      }
      else {
        float LarSlope = (.05f - 1.0f) / (LarvTemp1 - LarvTemp2);
        LarvSurvTempDlyCt[i] = 1 - ((LarvTemp2 - ContEnv[Day][i].TempMin) * LarSlope);
      }

      // survival from maximum temperatures
      if( ContEnv[Day][i].TempMax >= LarvTemp4 ) {
        LarvSurvTempDlyCt[i] = LarvSurvTempDlyCt[i] * .05f;
      }
      else if( ContEnv[Day][i].TempMax <= LarvTemp3 ) {
        LarvSurvTempDlyCt[i] = LarvSurvTempDlyCt[i] * 1;
      }
      else {
        float LarSlope = (1 - .05f) / (LarvTemp3 - LarvTemp4);
        LarvSurvTempDlyCt[i] = LarvSurvTempDlyCt[i] * (1 + ((ContEnv[Day][i].TempMax - LarvTemp3) * LarSlope));
      }
    }


//==================================================================
//Larval Survival vs Insecticides
//Survival from insecticides needs to be adjusted for the actual
//container density and the ratio of treated to untreated containers.
//Adjust LISurv since this years treatment is lost on continue (no
//residual using this years values).
//This survival is applied in the larval life cycle loop and where
// newlyhatched are assinged to the larval array - Larvae(1,1)
//==================================================================

    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( LISurv[Day][i] < 1 ) {
        LISurv[Day][i] = 1 - ((1 - LISurv[Day][i]) * (ContDensity[i].Treated / (ContDensity[i].Treated + ContDensity[i].Untreated)));
      }
    }
    

//====================================
//Larval survival vs water depth
//if water depth=0 then survival =0.05
//====================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].Depth == 0 )
        LarvSurvTempDlyCt[i] = .05f;
    }


//============================================
//Determine new food values for each container
//Calculate change in weight for each cohort
//============================================


    // Zero array used to hold change in weight values
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      for( int Age = MaxAgeLarv; Age >= 1; Age-- ) {
        Larvae[Age][i].WtChange = 0;
      }
    }

    // Run Euler, adjust food and determine weight status of each cohort
    float ContFoodChange = 0;
    float FoodChange = 0;
    float WeightChange = 0;
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      for( int e = 1; e <= EulerSteps; e++ ) {
        for( int Age = MaxAgeLarv; Age >= 1; Age-- ) {
          if( Larvae[Age][i].Number > 0 ) {
            FoodChange = FoodEqn( Larvae[Age][i].Number, (Larvae[Age][i].Weight + Larvae[Age][i].WtChange), ContEnv[Day][i].Food, et[i]) * (2880 / (float)EulerSteps);
            WeightChange = WeightEqn((Larvae[Age][i].Weight + Larvae[Age][i].WtChange), ContEnv[Day][i].Food, et[i]) * (2880 / (float)EulerSteps);
            ContFoodChange = ContFoodChange + FoodChange;
            Larvae[Age][i].WtChange = Larvae[Age][i].WtChange + WeightChange;
          }
        }
        ContEnv[Day][i].Food = ContEnv[Day][i].Food + ContFoodChange;
        if( ContEnv[Day][i].Food < 0 )
          ContEnv[Day][i].Food = 0;
        ContFoodChange = 0;
      }
    }


//==================================================================
//Larval survival vs food availability
//Weight gain or loss adjustments must consider the previous fasting
//status of the larvae and the condition of the fatbody
//max.fb.wt() holds the weight of the fatbody prior to fasting
//fatbody() holds the current weight of the fatbody
//==================================================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      MaxLarvWt[i] = 0;                             // average wt of larval cohorts that are pupating, end value represents:
                                                    // sum Wt * N / sum N
      for( int Age = MaxAgeLarv; Age >= 1; Age-- ) {
        if( Larvae[Age][i].Number == 0 ) {
          // go to next age
        }
        else {
          // calculate pupation weight - temperature and CD dependent
          float WTerm = (PupWtSlope * abs(ContEnv[Day][i].TempAvg)) + PupWtConst;
          float Slope = (WTerm - PupMinWt) / (.95f - PupMinAge);
          float PupationWt = (WTerm + (Slope * Larvae[Age][i].CumDev));

          if( PupationWt < PupMinWt )
            PupationWt = PupMinWt;

          if( Larvae[Age][i].CumDev <= .95 || Larvae[Age][i].Weight < PupationWt ) {                    // not sufficiently developed and/or below pupation weight

            if( Larvae[Age][i].WtChange >= 0 ) {                                                        // today//s weight change was positive
              if( Larvae[Age][i].MaxFB == 0 ) {
                // no previous fasting - high end survival
              }
              else {
                Larvae[Age][i].FatBody = Larvae[Age][i].FatBody + Larvae[Age][i].WtChange;              // previous fasting, add weight gain to fatbody
                if( Larvae[Age][i].FatBody >= Larvae[Age][i].MaxFB ) {                                  // if fatbody been replenished...
                  Larvae[Age][i].FatBody = 0;                                                           // ...cohort finished fasting
                  Larvae[Age][i].MaxFB = 0;
                }
              }
              LarvSurvFood[Age][i] = larvpwtsu;
            }
            else {                                                                                      // today//s weight change was negative
              if( Larvae[Age][i].MaxFB == 0 ) {                                                          
                // no previous fasting
                float maxfb = Larvae[Age][i].Weight * (.059f * (log(Larvae[Age][i].Weight) + 6.9f) - .15f);
                Larvae[Age][i].MaxFB = maxfb;
                Larvae[Age][i].FatBody = maxfb + Larvae[Age][i].WtChange;
              }
              else {
                // previous fasting
                Larvae[Age][i].FatBody = Larvae[Age][i].FatBody + Larvae[Age][i].WtChange;
              }

              if( Larvae[Age][i].FatBody <= 0 ) {
                LarvSurvFood[Age][i] = larvnwtnfbsu;
              }
              else {
                LarvSurvFood[Age][i] = larvnwtfbsu;
              }
            }

            Larvae[Age + 1][i].MaxFB = Larvae[Age][i].MaxFB;
            Larvae[Age][i].MaxFB = 0;
            Larvae[Age + 1][i].FatBody = Larvae[Age][i].FatBody;
            Larvae[Age][i].FatBody = 0;

            Larvae[Age + 1][i].Number = Larvae[Age][i].Number * LarvSurvFood[Age][i] * LarvSurvTempDlyCt[i] * LarvSurvNom * LISurv[Day][i];
            Larvae[Age + 1][i].CumDev = Larvae[Age][i].CumDev + DevRateLarv[i];
            Larvae[Age + 1][i].Weight = Larvae[Age][i].Weight + Larvae[Age][i].WtChange;
            Larvae[Age + 1][i].WtChange = Larvae[Age][i].WtChange;
            LarvSurvFood[Age + 1][i] = LarvSurvFood[Age][i];

            if( Larvae[Age + 1][i].Weight < .003 || Larvae[Age + 1][i].CumDev > LarvaeMaxCD ) {
              Larvae[Age + 1][i].Weight = 0;
              Larvae[Age + 1][i].Number = 0;
              Larvae[Age + 1][i].CumDev = 0;
              Larvae[Age + 1][i].WtChange = 0;
              LarvSurvFood[Age + 1][i] = 0;
              LarvSurvFood[Age][i] = 0;       // for calculation of cadaver food
            }
          }
          else {
            NewPupae[i] = NewPupae[i] + Larvae[Age][i].Number * LarvSurvFood[Age][i] * LarvSurvTempDlyCt[i] * LarvSurvNom * LISurv[Day][i];
            MaxLarvWt[i] = MaxLarvWt[i] + (Larvae[Age][i].Weight * (Larvae[Age][i].Number * LarvSurvFood[Age][i] * LarvSurvTempDlyCt[i] * LarvSurvNom * LISurv[Day][i]));
          }
        }
        LarvCadWt[i] = LarvCadWt[i] + ((Larvae[Age][i].Number - (Larvae[Age][i].Number * LarvSurvFood[Age][i] * LarvSurvTempDlyCt[i] * LarvSurvNom * LISurv[Day][i])) * Larvae[Age][i].Weight);
        Larvae[Age][i].CumDev = 0;
        Larvae[Age][i].Number = 0;
        Larvae[Age][i].Weight = 0;
        Larvae[Age][i].WtChange = 0;
        LarvSurvFood[Age][i] = 0;
      }
      if( NewPupae[i] > 0 ) {
        MaxLarvWt[i] = MaxLarvWt[i] / NewPupae[i];
      }
      else {
        MaxLarvWt[i] = 0;
      }
    }
    


//===================================================
//Hatch eggs if flooded and at the proper temperature
//===================================================


    if( ContEnv[Day][1].TempAvg >= eggdiapausetemp ) {
      for( int level = HatchLevel[1]; level >= 1; level-- ) {                               // TODO - for an erroneous hatch level of 0, no eggs will hatch
        NewlyHatched[1] = NewlyHatched[1] + (C1MatureEggs[level] * PropHatchflood);
        C1MatureEggs[level] = C1MatureEggs[level] - (C1MatureEggs[level] * PropHatchflood);
      }
      if( NewlyHatched[1] > 0 ) {
        // apply larvicide treatment to new larvae
        Larvae[1][1].Number = NewlyHatched[1] * LISurv[Day][1];
        Larvae[1][1].CumDev = DevRateLarv[1];
        Larvae[1][1].Weight = initw;
      }
      else {
        Larvae[1][1].Number = 0;
        NewlyHatched[1] = 0;
        Larvae[1][1].CumDev = 0;
        Larvae[1][1].Weight = 0;
      }
      NewlyHatched[1] = 0;
    }
    if( NumberOfContainers > 1 ) {
      if( ContEnv[Day][2].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[2]; level >= 1; level-- ) {
          NewlyHatched[2] = NewlyHatched[2] + (C2MatureEggs[level] * PropHatchflood);
          C2MatureEggs[level] = C2MatureEggs[level] - (C2MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[2] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][2].Number = NewlyHatched[2] * LISurv[Day][2];
          Larvae[1][2].CumDev = DevRateLarv[2];
          Larvae[1][2].Weight = initw;
        }
        else {
          Larvae[1][2].Number = 0;
          Larvae[1][2].CumDev = 0;
          Larvae[1][2].Weight = 0;
        }
        NewlyHatched[2] = 0;
      }
    }
    if( NumberOfContainers > 2 ) {
      if( ContEnv[Day][3].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[3]; level >= 1; level-- ) {
          NewlyHatched[3] = NewlyHatched[3] + (C3MatureEggs[level] * PropHatchflood);
          C3MatureEggs[level] = C3MatureEggs[level] - (C3MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[3] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][3].Number = NewlyHatched[3] * LISurv[Day][3];
          Larvae[1][3].CumDev = DevRateLarv[3];
          Larvae[1][3].Weight = initw;
        }
        else {
          Larvae[1][3].Number = 0;
          Larvae[1][3].CumDev = 0;
          Larvae[1][3].Weight = 0;
        }
        NewlyHatched[3] = 0;
      }
    }
    if( NumberOfContainers > 3 ) {
      if( ContEnv[Day][4].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[4]; level >= 1; level-- ) {
          NewlyHatched[4] = NewlyHatched[4] + (C4MatureEggs[level] * PropHatchflood);
          C4MatureEggs[level] = C4MatureEggs[level] - (C4MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[4] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][4].Number = NewlyHatched[4] * LISurv[Day][4];
          Larvae[1][4].CumDev = DevRateLarv[4];
          Larvae[1][4].Weight = initw;
        }
        else {
          Larvae[1][4].Number = 0;
          Larvae[1][4].CumDev = 0;
          Larvae[1][4].Weight = 0;
        }
        NewlyHatched[4] = 0;
      }
    }
    if( NumberOfContainers > 4 ) {
      if( ContEnv[Day][5].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[5]; level >= 1; level-- ) {
          NewlyHatched[5] = NewlyHatched[5] + (C5MatureEggs[level] * PropHatchflood);
          C5MatureEggs[level] = C5MatureEggs[level] - (C5MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[5] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][5].Number = NewlyHatched[5] * LISurv[Day][5];
          Larvae[1][5].CumDev = DevRateLarv[5];
          Larvae[1][5].Weight = initw;
        }
        else {
          Larvae[1][5].Number = 0;
          Larvae[1][5].CumDev = 0;
          Larvae[1][5].Weight = 0;
        }
        NewlyHatched[5] = 0;
      }
    }
    if( NumberOfContainers > 5 ) {
      if( ContEnv[Day][6].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[6]; level >= 1; level-- ) {
          NewlyHatched[6] = NewlyHatched[6] + (C6MatureEggs[level] * PropHatchflood);
          C6MatureEggs[level] = C6MatureEggs[level] - (C6MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[6] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][6].Number = NewlyHatched[6] * LISurv[Day][6];
          Larvae[1][6].CumDev = DevRateLarv[6];
          Larvae[1][6].Weight = initw;
        }
        else {
          Larvae[1][6].Number = 0;
          Larvae[1][6].CumDev = 0;
          Larvae[1][6].Weight = 0;
        }
        NewlyHatched[6] = 0;
      }
    }
    if( NumberOfContainers > 6 ) {
      if( ContEnv[Day][7].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[7]; level >= 1; level-- ) {
          NewlyHatched[7] = NewlyHatched[7] + (C7MatureEggs[level] * PropHatchflood);
          C7MatureEggs[level] = C7MatureEggs[level] - (C7MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[7] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][7].Number = NewlyHatched[7] * LISurv[Day][7];
          Larvae[1][7].CumDev = DevRateLarv[7];
          Larvae[1][7].Weight = initw;
        }
        else {
          Larvae[1][7].Number = 0;
          Larvae[1][7].CumDev = 0;
          Larvae[1][7].Weight = 0;
        }
        NewlyHatched[7] = 0;
      }
    }
    if( NumberOfContainers > 7 ) {
      if( ContEnv[Day][8].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[8]; level >= 1; level-- ) {
          NewlyHatched[8] = NewlyHatched[8] + (C8MatureEggs[level] * PropHatchflood);
          C8MatureEggs[level] = C8MatureEggs[level] - (C8MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[8] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][8].Number = NewlyHatched[8] * LISurv[Day][8];
          Larvae[1][8].CumDev = DevRateLarv[8];
          Larvae[1][8].Weight = initw;
        }
        else {
          Larvae[1][8].Number = 0;
          Larvae[1][8].CumDev = 0;
          Larvae[1][8].Weight = 0;
        }
        NewlyHatched[8] = 0;
      }
    }
    if( NumberOfContainers > 8 ) {
      if( ContEnv[Day][9].TempAvg >= eggdiapausetemp ) {
        for( int level = HatchLevel[9]; level >= 1; level-- ) {
          NewlyHatched[9] = NewlyHatched[9] + (C9MatureEggs[level] * PropHatchflood);
          C9MatureEggs[level] = C9MatureEggs[level] - (C9MatureEggs[level] * PropHatchflood);
        }
        if( NewlyHatched[9] > 0 ) {
          // apply larvicide treatment to new larvae
          Larvae[1][9].Number = NewlyHatched[9] * LISurv[Day][9];
          Larvae[1][9].CumDev = DevRateLarv[9];
          Larvae[1][9].Weight = initw;
        }
        else {
          Larvae[1][9].Number = 0;
          Larvae[1][9].CumDev = 0;
          Larvae[1][9].Weight = 0;
        }
        NewlyHatched[9] = 0;
      }
    }


//=============================
//Pupal survival vs temperature
//=============================


    for( int i = 1; i <= NumberOfContainers; i++ ) {

      if( ContEnv[Day][i].TempMin <= PupTemp1 ) {
        PupSurvTempDlyCt[i] = .05f;
      }
      else if( ContEnv[Day][i].TempMin >= PupTemp2 ) {
        PupSurvTempDlyCt[i] = 1;
      }
      else {
        float PupSlope = (.05f - 1) / (PupTemp1 - PupTemp2);
        PupSurvTempDlyCt[i] = 1 - ((PupTemp2 - ContEnv[Day][i].TempMin) * PupSlope);
      }

      if( ContEnv[Day][i].TempMax >= PupTemp4 ) {
        PupSurvTempDlyCt[i] = PupSurvTempDlyCt[i] * 0;
      }
      else if( ContEnv[Day][i].TempMax <= LarvTemp3 ) {
        PupSurvTempDlyCt[i] = PupSurvTempDlyCt[i] * 1;
      }
      else {
        float PupSlope = (1 - .05f) / (PupTemp3 - PupTemp4);
        PupSurvTempDlyCt[i] = PupSurvTempDlyCt[i] * (1 + ((ContEnv[Day][i].TempMax - PupTemp3) * PupSlope));
      }
    }


//===============================================
//Apply genetic death to new pupae.
//Calulate wt of dead pupae for food contribution
//===============================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      PupCadWt[i] = (NewPupae[i] - (NewPupae[i] * pupgeneticsu)) * MaxLarvWt[i];
      NewPupae[i] = NewPupae[i] * pupgeneticsu;
    }


//=====
//PUPAE
//=====

    
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      float oldPupCadWt = PupCadWt[i];
      AdultsNewDlyCt[i] = 0;
      PupaeWt[i] = 0;                                   // weighted avg wt for the new adult cohort
                                                        // End value represents: sum Wt * N / sum N
      for( int Age = MaxAgePupae; Age >= 1; Age-- ) {
        if( Pupae[Age][i].Number == 0 ) {

        }
        else {
          if( Pupae[Age][i].CumDev <= .95 ) {
            Pupae[Age + 1][i].Number = Pupae[Age][i].Number * PupSurvTempDlyCt[i] * PupSurvNom;
            Pupae[Age + 1][i].CumDev = Pupae[Age][i].CumDev + DevRatePupae[i];
            Pupae[Age + 1][i].Weight = Pupae[Age][i].Weight;
          }
          else {
            AdultsNewDlyCt[i] = AdultsNewDlyCt[i] + (Pupae[Age][i].Number * PupSurvTempDlyCt[i] * PupSurvNom * EmergenceSuccess);
            PupaeWt[i] = PupaeWt[i] + (Pupae[Age][i].Weight * (Pupae[Age][i].Number * PupSurvTempDlyCt[i] * PupSurvNom * EmergenceSuccess));
          }
        }
        PupCadWt[i] = PupCadWt[i] + ((Pupae[Age][i].Number - (Pupae[Age][i].Number * PupSurvTempDlyCt[i] * PupSurvNom * EmergenceSuccess)) * Pupae[Age][i].Weight);
        Pupae[Age][i].Number = 0;
        Pupae[Age][i].CumDev = 0;
        Pupae[Age][i].Weight = 0;
      }
      Pupae[1][i].Number = NewPupae[i];
      Pupae[1][i].CumDev = DevRatePupae[i];
      Pupae[1][i].Weight = MaxLarvWt[i];
      if( AdultsNewDlyCt[i] > 0 ) {
        PupaeWt[i] = PupaeWt[i] / AdultsNewDlyCt[i];
      }
      else {
        PupaeWt[i] = 0;
      }
    }


//============================================
//Select female mosquitoes
//Convert adults/container to adults/ha
//Calculate adult weight:
//  sum Wt * N * ContDenity / sum N * ContDens
//============================================


    // select females
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      AdultsNewDlyCt[i] = AdultsNewDlyCt[i] * PercentFemale;
    }

    // calculate females per hectare
    // calculate avg dly adult weight
    NewAdultsHa[Day] = 0;
    float AdultWtDlyAvg = 0;

    for( int i = 1; i <= NumberOfContainers; i++ ) {
      AdultWtDlyAvg = AdultWtDlyAvg + (PupaeWt[i] * (AdultsNewDlyCt[i] * ContDensity[i].Untreated) + (AdultsNewDlyCt[i] * ContDensity[i].Treated));
      NewAdultsHa[Day] = NewAdultsHa[Day] + (AdultsNewDlyCt[i] * ContDensity[i].Untreated) + (AdultsNewDlyCt[i] * ContDensity[i].Treated);
    }
    if( NewAdultsHa[Day] > 0 ) {
      AdultWtDlyAvg = AdultWtDlyAvg / NewAdultsHa[Day];
    }
    else {
      AdultWtDlyAvg = 0;
    }

    // Adjust array for moving avg of adult weights
    if( AdultWtDlyAvg > 0 ) {
      // add to and advance moving average array
      for( int i = 5; i >= 2; i-- ) {
        if( AdultWtAvgs[i - 1] > 0 )
          AdultWtAvgs[i] = AdultWtAvgs[i - 1];
      }
      AdultWtAvgs[1] = AdultWtDlyAvg;
    }

    // calculate AdultWt based on 5 day moving average
    AdultWt = 0;
    float Count = 0;

    for( int i = 1; i <= 5; i++ ) {
      AdultWt = AdultWt + AdultWtAvgs[i];
      if( AdultWtAvgs[i] > 0 ) {
        Count = Count + 1;
      }
    }
    if( Count > 0 ) {
      AdultWt = AdultWt / Count;
    }
    else {
      AdultWt = 0;
    }

    // check for mosquitoes returning to the same container for oviposition.
    // Adjust array for moving avng of number of adults per container
    //   adjustment is made even when ReturnOviRate=0 because it may be
    //    selected in the following year.  A log of previous numbers will
    //    already be present.
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      for( int j = 5; j >= 2; j-- ) {
        AdultsNewDlyCtMAvg[j][i] = AdultsNewDlyCtMAvg[j - 1][i];
      }
      AdultsNewDlyCtMAvg[1][i] = AdultsNewDlyCt[i] * (ContDensity[i].Untreated + ContDensity[i].Treated);
    }
    if( ReturnOviRate > 0 ) {
      // calculate number of females/ct based on moving average
      // REDIM AdultsNewDlyCtAvg(1 TO NumberOfContainers%)
      float AdultsNewDlyCtAvg[MaxNumCt + 1];
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        AdultsNewDlyCtAvg[i] = 0;
      }
      float TotTemp = 0;
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        for( int j = 1; j <= 5; j++ ) {
          AdultsNewDlyCtAvg[i] = AdultsNewDlyCtAvg[i] + AdultsNewDlyCtMAvg[j][i];
        }
        AdultsNewDlyCtAvg[i] = AdultsNewDlyCtAvg[i] / 5;
        TotTemp = TotTemp + AdultsNewDlyCtAvg[i];
      }

      // normalize weight of faithful oviposition
      // REDIM ReturnCtOvi(1 TO NumberOfContainers%)
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        ReturnCtOvi[i] = 0;
      }
      if( TotTemp > 0 ) {
        for( int i = 1; i <= NumberOfContainers; i++ ) {
          ReturnCtOvi[i] = AdultsNewDlyCtAvg[i] / TotTemp;
        }
      }
    }


//=======================================================
//Convert dry NewAdultWeight to Wet-Female NewAdultWeight
//Larvae - Pupae are dry weight values.
//=======================================================


    AdultWt = AdultWt * 1.655f;


//=============================
//Adult survival vs temperature
//=============================


    if( TemperatureMin[Day] <= adtemp1 ) {
      AdultSurvTemp[Day] = .05f;
    }
    else if( TemperatureMin[Day] >= adtemp2 ) {
      AdultSurvTemp[Day] = 1;
    }
    else { 
      float adltempslope = (.05f - 1) / (adtemp1 - adtemp2);
      AdultSurvTemp[Day] = 1 - ((adtemp2 - (TemperatureMin[Day])) * adltempslope);
    }

    if( TemperatureMax[Day] >= adtemp4 ) {
      AdultSurvTemp[Day] = AdultSurvTemp[Day] * .05f;
    }
    else if( TemperatureMax[Day] <= adtemp3 ) {
      AdultSurvTemp[Day] = AdultSurvTemp[Day] * 1;
    }
    else {
      float adhtempslope = (1 - .05f) / (adtemp3 - adtemp4);
      AdultSurvTemp[Day] = AdultSurvTemp[Day] * (1 + ((TemperatureMax[Day] - adtemp3) * adhtempslope));
    }


//====================================
//Adult survival vs saturation deficit
//====================================


    if( SD[Day] <= adlsdth ) {
      AdultSurvSD[Day] = adlsdsu;
    }
    else if( SD[Day] >= adhsdth ) {
      AdultSurvSD[Day] = adhsdsu;
    }
    else {
      float survadslope = (adlsdsu - adhsdsu) / (adhsdth - adlsdth);
      AdultSurvSD[Day] = adlsdsu - ((SD[Day] - adlsdth) * survadslope);
    }


//==============================
//Adult survival vs host density
//==============================


    float TotHostDensity = (HumanDensity * HumanAvail) + (MammalDensity * MammalAvail);
    float BitingDensity;

    if( TotHostDensity == 0 ) {
      BitingDensity = 0;
    }
    else {
      BitingDensity = ((NewBiters + OldBiters) * InterFeeding) / TotHostDensity;
    }

    // No density feedback for dengue output (don't know human density from other model)
    if( DengueOutput ) {
      AdultSurvDens[Day] = 1;
    }
    else {
      if( BitingDensity <= AdultDensLTH ) {
        AdultSurvDens[Day] = AdultDensLSU;
      }
      else if( BitingDensity >= AdultDensHTH ) {
        AdultSurvDens[Day] = AdultDensHSU;
      }
      else {
        float Slope = (AdultDensLSU - AdultDensHSU) / (AdultDensHTH - AdultDensLTH);
        AdultSurvDens[Day] = AdultDensLSU - ((BitingDensity - AdultDensLTH) * Slope);
      }
    }
    
    AdultSurvival[Day] = survadnom * AdultSurvTemp[Day] * AdultSurvDens[Day] * AdultSurvSD[Day];


//========================
//Adults - Preoviposition
//Adults on a per ha basis
//========================

    NewEggLayers = 0;
    for( int Age = MaxAgePreOviAdults; Age >= 1; Age-- ) {
      if( PreOviAdults[Age] == 0 ) {
        // go to next age
      }
      else {
        if( CumDevPreOviAdults[Age] < 1 || TemperatureAvg[Day] <= OviTemperature ) {
          PreOviAdults[Age + 1] = PreOviAdults[Age] * AdultSurvival[Day];
          CumDevPreOviAdults[Age + 1] = CumDevPreOviAdults[Age] + DevRateAdult;
        }
        else {
          NewEggLayers = NewEggLayers + PreOviAdults[Age] * AdultSurvival[Day];
        }
      }
      PreOviAdults[Age] = 0;
      CumDevPreOviAdults[Age] = 0;
    } // age
    PreOviAdults[1] = NewAdultsHa[Day];
    CumDevPreOviAdults[1] = DevRateAdult;


//==========================================
//Apply space spray to preoviposition adults
//==========================================


    if( SS ) {
      if( SSDensityFlag  && (TotOviAdults[Day - 1] + TotPreOviAdults[Day - 1]) > SSMosqDensity ) {
        SSSchedule[Day] = true;
        for( int Age = MaxAgePreOviAdults; Age >= 1; Age -- ) {
          float IndoorSurviving = PreOviAdults[Age] * (1 - SSMortIn) * (1 - OutdoorAdults);
          float OutdoorSurviving = PreOviAdults[Age] * (1 - SSMortOut) * OutdoorAdults;
          PreOviAdults[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
      else if( SSSchedule[Day] ) {
        for( int Age = MaxAgePreOviAdults; Age >= 1; Age -- ) {
          float IndoorSurviving = PreOviAdults[Age] * (1 - SSMortIn) * (1 - OutdoorAdults);
          float OutdoorSurviving = PreOviAdults[Age] * (1 - SSMortOut) * OutdoorAdults;
          PreOviAdults[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
    }


//=============================================
//Apply residual spray to preoviposition adults
//=============================================


    if( RSSurv[Day] < 1 ) {
      for( int Age = MaxAgePreOviAdults; Age >= 1; Age -- ) {
        float IndoorSurviving = PreOviAdults[Age] * (1 - OutdoorAdults) * RSPropSurfTrt * RSPropHouseTrt * RSSurv[Day];
        float OutdoorSurviving = PreOviAdults[Age] * OutdoorAdults;
        PreOviAdults[Age] = IndoorSurviving + OutdoorSurviving;
      }
    }


//==============
//Adults
//Ovipositioning
//==============


    for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
      if( OviAdults[Age] == 0 ) {
        // go to next age
      }
      else {
        if( CumDevOviAdults[Age] < .58 || TemperatureAvg[Day] <= OviTemperature ) {
          OviAdults[Age + 1] = OviAdults[Age] * AdultSurvival[Day];
          CumDevOviAdults[Age + 1] = CumDevOviAdults[Age] + DevRateAdult;
        }
        else {
          EggLayers = EggLayers + OviAdults[Age] * AdultSurvival[Day];
        }
      }
      OviAdults[Age] = 0;
      CumDevOviAdults[Age] = 0;
    } // age

    OviAdults[1] = NewEggLayers + EggLayers;
    CumDevOviAdults[1] = DevRateAdult;


//=======================================
//Apply space spray to oviposition adults
//=======================================


    if( SS ) {
      if( SSDensityFlag && (TotOviAdults[Day - 1] + TotPreOviAdults[Day - 1]) > SSMosqDensity ) {
        SSSchedule[Day] = true;
        for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
          float IndoorSurviving = OviAdults[Age] * (1 - SSMortIn) * (1 - OutdoorAdults);
          float OutdoorSurviving = OviAdults[Age] * (1 - SSMortOut) * OutdoorAdults;
          OviAdults[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
      else if( SSSchedule[Day] == true ) {
        for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
          float IndoorSurviving = OviAdults[Age] * (1 - SSMortIn) * (1 - OutdoorAdults);
          float OutdoorSurviving = OviAdults[Age] * (1 - SSMortOut) * OutdoorAdults;
          OviAdults[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
    }


//==========================================
//Apply residual spray to Oviposition adults
//==========================================


    if( RSSurv[Day] < 1 ) {
      for( int Age = MaxAgeOviAdults; Age <= 1; Age-- ) {
        OviAdults[Age] = OviAdults[Age] * (1 - OutdoorAdults) * RSPropSurfTrt * RSPropHouseTrt * RSSurv[Day];
      }
    }


//======================
//Adult Age Distribution
//Pre and Ovipositioning
//======================


    for( int Age = MaxAgeOviAdults - 1; Age >= 1; Age-- ) {
      MosqDistr.Number[Age + 1] = MosqDistr.Number[Age] * AdultSurvival[Day];
    }
    MosqDistr.Number[1] = NewAdultsHa[Day];


//=====================================
//Apply space spray to age distribution
//=====================================


    if( SS ) {
      if( SSDensityFlag && (TotOviAdults[Day - 1] + TotPreOviAdults[Day - 1]) > SSMosqDensity ) {
        SSSchedule[Day] = true;
        for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
          float IndoorSurviving = MosqDistr.Number[Age] * (1 - SSMortIn) * (1 - OutdoorAdults);
          float OutdoorSurviving = MosqDistr.Number[Age] * (1 - SSMortOut) * OutdoorAdults;
          MosqDistr.Number[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
      else if( SSSchedule[Day] ) {
        for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
          float IndoorSurviving = MosqDistr.Number[Age] * (1 - SSMortIn) * (1 - OutdoorAdults);
          float OutdoorSurviving = MosqDistr.Number[Age] * (1 - SSMortOut) * OutdoorAdults;
          MosqDistr.Number[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
    }


//==========================================
//Apply residual spray to age distribution
//==========================================

    if( RSSurv[Day] < 1 ) {
      for( int Age = MaxAgeOviAdults; Age <= 1; Age-- ) {
        MosqDistr.Number[Age] = MosqDistr.Number[Age] * (1 - OutdoorAdults) * RSPropSurfTrt * RSPropHouseTrt * RSSurv[Day];
      }
    }


//==============================
//Calculate biters and bite rate
//NewBiters from days 2 and 3
//OldBiters from days 1 and 2
//==============================

    BitesHost[Day] = BitingDensity;
    if( TotHostDensity == 0 ) {
      BitesHuman[Day] = 0;
      BitesMammal[Day] = 0;
    }
    else {
      BitesHuman[Day] = BitesHost[Day] * ((HumanDensity * HumanAvail) / TotHostDensity);
      BitesMammal[Day] = BitesHost[Day] * ((MammalDensity * MammalAvail) / TotHostDensity);
    }

    // the proportion of double blood meals is a function of female wet wt.
    float DMealProp;
    if( AdultWt <= DBloodLWt ) {
      DMealProp = DBloodUProp;
    }
    else if( AdultWt >= DBloodUWt ) {
      DMealProp = DBloodLProp;
    }
    else {
      float Slope = (DBloodUProp - DBloodLProp) / (DBloodUWt - DBloodLWt);
      DMealProp = DBloodUProp - ((AdultWt - DBloodLWt) * Slope);
    }

    NewBiters = PreOviAdults[2] + (PreOviAdults[3] * DMealProp);
    OldBiters = OviAdults[1] + (OviAdults[2] * DMealProp);


//========================================================================
//Calculate wild type males - needed for sterile male releases.
//survivals and treatments have already been applied to the female arrays.
//========================================================================


    for( int Age = 1; Age <= MaxAgePreOviAdults; Age++ ) {
      MalePop[Day] = MalePop[Day] + ((PreOviAdults[Age] / PercentFemale) - PreOviAdults[Age]);
    }
    for( int  Age = 1; Age <= MaxAgeOviAdults; Age++ ) {
      MalePop[Day] = MalePop[Day] + ((OviAdults[Age] / PercentFemale) - OviAdults[Age]);
    }


//============================
//Advance/update sterile males
//============================


    SMPop[Day] = SMPop[Day - 1] * AdultSurvival[Day] * SMSurvRatio;
    if( SM && SMSchedule[Day] ) {
      SMPop[Day] = SMPop[Day] + SMNumber;
    }


//===========================================================
//Calculate container preference
//based on the normalized product of: log(vol+1) * No. per Ha
//===========================================================


    float NormTotal = 0;
    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( ContEnv[Day][i].Depth > 0 ) {
        ContPref[i] = log(ContVolume[i] + 1) * (ContDensity[i].Untreated + ContDensity[i].Treated);
      }
      else {
        ContPref[i] = 0;
      }
      NormTotal = NormTotal + ContPref[i];
    }

    if( NormTotal == 0 ) {
      // containers may be dry - treat as if all are full
      for( int i = 1; i <= NumberOfContainers; i++ ) {
        ContPref[i] = log(ContVolume[i] + 1) * (ContDensity[i].Untreated + ContDensity[i].Treated);
        NormTotal = NormTotal + ContPref[i];
      }
    }

    for( int i = 1; i <= NumberOfContainers; i++ ) {
      if( NormTotal == 0 ) {
        // there are no untreated and treated containers
        ContPref[i] = 0;
      }
      else {
        ContPref[i] = ContPref[i] / NormTotal;
      }
    }


//=============================================
//Determine level of input for new eggs
//Calculate female fecundity
//Convert new eggs from per ha to per container
//Add new eggs.
//=============================================


    for( int i = 1; i <= NumberOfContainers; i++ ) {
      EggInputLevel[i] = INT(ContEnv[Day][i].Depth / 2) + 1;
      if( EggInputLevel[i] > CINT((ContDesc[i].Height / 2) + .2f) )
        EggInputLevel[i] = CINT((ContDesc[i].Height / 2) + .2f);
    }


//==========================================
//Calculate sterile male effect on fecundity
//==========================================


    float SterileFactor;
    if( (SMPop[Day] * SMComp) + MalePop[Day] <= 0 ) {
      SterileFactor = 1;
    }
    else {
      SterileFactor = 1 - ((SMPop[Day] * SMComp * SMRate) / ((SMPop[Day] * SMComp) + MalePop[Day]));
    }


//============================================
//Calculate new eggs given the daily fecundity
//============================================


    newdailyeggs[Day] = (NewEggLayers * FecundityCoef * AdultWt * SterileFactor) + (EggLayers * FecundityCoef * AdultWt * SterileFactor);
    if( newdailyeggs[Day] > 0 ) {
      DlyFecundity[Day] = FecundityCoef * AdultWt;
    }
    else {
      DlyFecundity[Day] = 0;
    }


//================================================================
//Distribute eggs among the containers
// First distribution based on ovipositional container fidelity
// Second distribution based on volume and frequency of containers
//================================================================


    if( ContDensity[1].Untreated + ContDensity[1].Treated <= 0 ) {
      // no available containers
      EggsNewDlyCt[1] = 0;
    }
    else {
      EggsNewDlyCt[1] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[1] / (ContDensity[1].Untreated + ContDensity[1].Treated);
      EggsNewDlyCt[1] = EggsNewDlyCt[1] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[1] / (ContDensity[1].Untreated + ContDensity[1].Treated));
      if( EggInputLevel[1] == CINT((ContDesc[1].Height / 2) + .2f) ) {
        // Max container height - put eggs in last level
        C1Eggs[EggInputLevel[1]][1] = EggsNewDlyCt[1];
        if( C1Eggs[EggInputLevel[1]][1] > 0 ) {
          C1Eggs[EggInputLevel[1]][MaxAgeEggs + 1] = C1Eggs[EggInputLevel[1]][MaxAgeEggs + 1] + 1;
        }
      }
      else {
        // Divide eggs among level and level+1
        C1Eggs[EggInputLevel[1]][1] = .5f * EggsNewDlyCt[1];
        if( C1Eggs[EggInputLevel[1]][1] > 0 ) {
          C1Eggs[EggInputLevel[1]][MaxAgeEggs + 1] = C1Eggs[EggInputLevel[1]][MaxAgeEggs + 1] + 1;
        }
        C1Eggs[EggInputLevel[1] + 1][1] = .5f * EggsNewDlyCt[1];
        if( C1Eggs[EggInputLevel[1] + 1][1] > 0 ) {
          C1Eggs[EggInputLevel[1] + 1][MaxAgeEggs + 1] = C1Eggs[EggInputLevel[1] + 1][MaxAgeEggs + 1] + 1;
        }
      }
    }

    if( NumberOfContainers > 1 ) {
      if( ContDensity[2].Untreated + ContDensity[2].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[2] = 0;
      }
      else {
        EggsNewDlyCt[2] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[2] / (ContDensity[2].Untreated + ContDensity[2].Treated);
        EggsNewDlyCt[2] = EggsNewDlyCt[2] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[2] / (ContDensity[2].Untreated + ContDensity[2].Treated));
        if( EggInputLevel[2] == CINT((ContDesc[2].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C2Eggs[EggInputLevel[2]][1] = EggsNewDlyCt[2];
          if( C2Eggs[EggInputLevel[2]][1] > 0 ) {
            C2Eggs[EggInputLevel[2]][MaxAgeEggs + 1] = C2Eggs[EggInputLevel[2]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C2Eggs[EggInputLevel[2]][1] = .5f * EggsNewDlyCt[2];
          if( C2Eggs[EggInputLevel[2]][1] > 0 ) {
            C2Eggs[EggInputLevel[2]][MaxAgeEggs + 1] = C2Eggs[EggInputLevel[2]][MaxAgeEggs + 1] + 1;
          }
          C2Eggs[EggInputLevel[2] + 1][1] = .5f * EggsNewDlyCt[2];
          if( C2Eggs[EggInputLevel[2] + 1][1] > 0 ) {
            C2Eggs[EggInputLevel[2] + 1][MaxAgeEggs + 1] = C2Eggs[EggInputLevel[2] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 2 ) {
      if( ContDensity[3].Untreated + ContDensity[3].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[3] = 0;
      }
      else {
        EggsNewDlyCt[3] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[3] / (ContDensity[3].Untreated + ContDensity[3].Treated);
        EggsNewDlyCt[3] = EggsNewDlyCt[3] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[3] / (ContDensity[3].Untreated + ContDensity[3].Treated));
        if( EggInputLevel[3] == CINT((ContDesc[3].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C3Eggs[EggInputLevel[3]][1] = EggsNewDlyCt[3];
          if( C3Eggs[EggInputLevel[3]][1] > 0 ) {
            C3Eggs[EggInputLevel[3]][MaxAgeEggs + 1] = C3Eggs[EggInputLevel[3]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C3Eggs[EggInputLevel[3]][1] = .5f * EggsNewDlyCt[3];
          if( C3Eggs[EggInputLevel[3]][1] > 0 ) {
            C3Eggs[EggInputLevel[3]][MaxAgeEggs + 1] = C3Eggs[EggInputLevel[3]][MaxAgeEggs + 1] + 1;
          }
          C3Eggs[EggInputLevel[3] + 1][1] = .5f * EggsNewDlyCt[3];
          if( C3Eggs[EggInputLevel[3] + 1][1] > 0 ) {
            C3Eggs[EggInputLevel[3] + 1][MaxAgeEggs + 1] = C3Eggs[EggInputLevel[3] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 3 ) {
      if( ContDensity[4].Untreated + ContDensity[4].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[4] = 0;
      }
      else {
        EggsNewDlyCt[4] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[4] / (ContDensity[4].Untreated + ContDensity[4].Treated);
        EggsNewDlyCt[4] = EggsNewDlyCt[4] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[4] / (ContDensity[4].Untreated + ContDensity[4].Treated));
        if( EggInputLevel[4] == CINT((ContDesc[4].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C4Eggs[EggInputLevel[4]][1] = EggsNewDlyCt[4];
          if( C4Eggs[EggInputLevel[4]][1] > 0 ) {
            C4Eggs[EggInputLevel[4]][MaxAgeEggs + 1] = C4Eggs[EggInputLevel[4]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C4Eggs[EggInputLevel[4]][1] = .5f * EggsNewDlyCt[4];
          if( C4Eggs[EggInputLevel[4]][1] > 0 ) {
            C4Eggs[EggInputLevel[4]][MaxAgeEggs + 1] = C4Eggs[EggInputLevel[4]][MaxAgeEggs + 1] + 1;
          }
          C4Eggs[EggInputLevel[4] + 1][1] = .5f * EggsNewDlyCt[4];
          if( C4Eggs[EggInputLevel[4] + 1][1] > 0 ) {
            C4Eggs[EggInputLevel[4] + 1][MaxAgeEggs + 1] = C4Eggs[EggInputLevel[4] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 4 ) {
      if( ContDensity[5].Untreated + ContDensity[5].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[5] = 0;
      }
      else {
        EggsNewDlyCt[5] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[5] / (ContDensity[5].Untreated + ContDensity[5].Treated);
        EggsNewDlyCt[5] = EggsNewDlyCt[5] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[5] / (ContDensity[5].Untreated + ContDensity[5].Treated));
        if( EggInputLevel[5] == CINT((ContDesc[5].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C5Eggs[EggInputLevel[5]][1] = EggsNewDlyCt[5];
          if( C5Eggs[EggInputLevel[5]][1] > 0 ) {
            C5Eggs[EggInputLevel[5]][MaxAgeEggs + 1] = C5Eggs[EggInputLevel[5]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C5Eggs[EggInputLevel[5]][1] = .5f * EggsNewDlyCt[5];
          if( C5Eggs[EggInputLevel[5]][1] > 0 ) {
            C5Eggs[EggInputLevel[5]][MaxAgeEggs + 1] = C5Eggs[EggInputLevel[5]][MaxAgeEggs + 1] + 1;
          }
          C5Eggs[EggInputLevel[5] + 1][1] = .5f * EggsNewDlyCt[5];
          if( C5Eggs[EggInputLevel[5] + 1][1] > 0 ) {
            C5Eggs[EggInputLevel[5] + 1][MaxAgeEggs + 1] = C5Eggs[EggInputLevel[5] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 5 ) {
      if( ContDensity[6].Untreated + ContDensity[6].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[6] = 0;
      }
      else {
        EggsNewDlyCt[6] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[6] / (ContDensity[6].Untreated + ContDensity[6].Treated);
        EggsNewDlyCt[6] = EggsNewDlyCt[6] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[6] / (ContDensity[6].Untreated + ContDensity[6].Treated));
        if( EggInputLevel[6] == CINT((ContDesc[6].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C6Eggs[EggInputLevel[6]][1] = EggsNewDlyCt[6];
          if( C6Eggs[EggInputLevel[6]][1] > 0 ) {
            C6Eggs[EggInputLevel[6]][MaxAgeEggs + 1] = C6Eggs[EggInputLevel[6]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C6Eggs[EggInputLevel[6]][1] = .5f * EggsNewDlyCt[6];
          if( C6Eggs[EggInputLevel[6]][1] > 0 ) {
            C6Eggs[EggInputLevel[6]][MaxAgeEggs + 1] = C6Eggs[EggInputLevel[6]][MaxAgeEggs + 1] + 1;
          }
          C6Eggs[EggInputLevel[6] + 1][1] = .5f * EggsNewDlyCt[6];
          if( C6Eggs[EggInputLevel[6] + 1][1] > 0 ) {
            C6Eggs[EggInputLevel[6] + 1][MaxAgeEggs + 1] = C6Eggs[EggInputLevel[6] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 6 ) {
      if( ContDensity[7].Untreated + ContDensity[7].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[7] = 0;
      }
      else {
        EggsNewDlyCt[7] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[7] / (ContDensity[7].Untreated + ContDensity[7].Treated);
        EggsNewDlyCt[7] = EggsNewDlyCt[7] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[7] / (ContDensity[7].Untreated + ContDensity[7].Treated));
        if( EggInputLevel[7] == CINT((ContDesc[7].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C7Eggs[EggInputLevel[7]][1] = EggsNewDlyCt[7];
          if( C7Eggs[EggInputLevel[7]][1] > 0 ) {
            C7Eggs[EggInputLevel[7]][MaxAgeEggs + 1] = C7Eggs[EggInputLevel[7]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C7Eggs[EggInputLevel[7]][1] = .5f * EggsNewDlyCt[7];
          if( C7Eggs[EggInputLevel[7]][1] > 0 ) {
            C7Eggs[EggInputLevel[7]][MaxAgeEggs + 1] = C7Eggs[EggInputLevel[7]][MaxAgeEggs + 1] + 1;
          }
          C7Eggs[EggInputLevel[7] + 1][1] = .5f * EggsNewDlyCt[7];
          if( C7Eggs[EggInputLevel[7] + 1][1] > 0 ) {
            C7Eggs[EggInputLevel[7] + 1][MaxAgeEggs + 1] = C7Eggs[EggInputLevel[7] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 7 ) {
      if( ContDensity[8].Untreated + ContDensity[8].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[8] = 0;
      }
      else {
        EggsNewDlyCt[8] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[8] / (ContDensity[8].Untreated + ContDensity[8].Treated);
        EggsNewDlyCt[8] = EggsNewDlyCt[8] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[8] / (ContDensity[8].Untreated + ContDensity[8].Treated));
        if( EggInputLevel[8] == CINT((ContDesc[8].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C8Eggs[EggInputLevel[8]][1] = EggsNewDlyCt[8];
          if( C8Eggs[EggInputLevel[8]][1] > 0 ) {
            C8Eggs[EggInputLevel[8]][MaxAgeEggs + 1] = C8Eggs[EggInputLevel[8]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C8Eggs[EggInputLevel[8]][1] = .5f * EggsNewDlyCt[8];
          if( C8Eggs[EggInputLevel[8]][1] > 0 ) {
            C8Eggs[EggInputLevel[8]][MaxAgeEggs + 1] = C8Eggs[EggInputLevel[8]][MaxAgeEggs + 1] + 1;
          }
          C8Eggs[EggInputLevel[8] + 1][1] = .5f * EggsNewDlyCt[8];
          if( C8Eggs[EggInputLevel[8] + 1][1] > 0 ) {
            C8Eggs[EggInputLevel[8] + 1][MaxAgeEggs + 1] = C8Eggs[EggInputLevel[8] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    if( NumberOfContainers > 8 ) {
      if( ContDensity[9].Untreated + ContDensity[9].Treated <= 0 ) {
        // no available containers
        EggsNewDlyCt[9] = 0;
      }
      else {
        EggsNewDlyCt[9] = newdailyeggs[Day] * (1 - ReturnOviRate) * ContPref[9] / (ContDensity[9].Untreated + ContDensity[9].Treated);
        EggsNewDlyCt[9] = EggsNewDlyCt[9] + (newdailyeggs[Day] * ReturnOviRate * ReturnCtOvi[9] / (ContDensity[9].Untreated + ContDensity[9].Treated));
        if( EggInputLevel[9] == CINT((ContDesc[9].Height / 2) + .2f) ) {
          // Max container height - put eggs in last level
          C9Eggs[EggInputLevel[9]][1] = EggsNewDlyCt[9];
          if( C9Eggs[EggInputLevel[9]][1] > 0 ) {
            C9Eggs[EggInputLevel[9]][MaxAgeEggs + 1] = C9Eggs[EggInputLevel[9]][MaxAgeEggs + 1] + 1;
          }
        }
        else {
          // Divide eggs among level and level+1
          C9Eggs[EggInputLevel[9]][1] = .5f * EggsNewDlyCt[9];
          if( C9Eggs[EggInputLevel[9]][1] > 0 ) {
            C9Eggs[EggInputLevel[9]][MaxAgeEggs + 1] = C9Eggs[EggInputLevel[9]][MaxAgeEggs + 1] + 1;
          }
          C9Eggs[EggInputLevel[9] + 1][1] = .5f * EggsNewDlyCt[9];
          if( C9Eggs[EggInputLevel[9] + 1][1] > 0 ) {
            C9Eggs[EggInputLevel[9] + 1][MaxAgeEggs + 1] = C9Eggs[EggInputLevel[9] + 1][MaxAgeEggs + 1] + 1;
          }
        }
      }
    }

    CalcDailyTotals();

    for( int i = 1; i <= NumberOfContainers; i++ ) {
      NewlyHatched[i] = 0;
      NewPupae[i] = 0;
    }
    EggLayers = 0;
    NewEggLayers = 0;


    // spool daily data
#ifdef _DEBUG
    _locationLog << Day << TotPreOviAdults[Day] + TotOviAdults[Day] << NewAdultsHa[Day]
                 << BitesHuman[Day] << BitesMammal[Day] << BitesHost[Day] << DlyFecundity[Day]
                 << TemperatureMax[Day] << TemperatureMin[Day] << Rain[Day] << RelHumid[Day] << SD[Day] << output::Log::eor;
#endif


    //for( int i = 1; i <= NumberOfContainers; i++ ) {
    //  if( LogSettings_.DoContainerLog_ )
    //    containerLogs[i] << (float) Day << ContEnv[Day][i].Depth << ContEnv[Day][i].Food
    //                     << EggsEmbDlyCt[i] + EggsMatDlyCt[i] << LarvTotDlyCt[i] << PupTotDlyCt[i] << PupWtDlyAveCt[i]
    //                     << AdultsNewDlyCt[i] << CumulativeFemales[i] << EggsNewDlyCt[i] << FloatLog::eor;

    //}

    // write dengue output
    if( DengueOutput ) {
      DengueData[Day].NewDlyFemales = NewAdultsHa[Day];
      if( SSSchedule[Day] && RSSurv[Day] < 1 ) {
        DengueData[Day].OverallSurv = AdultSurvival[Day] * ((OutdoorAdults * (1 - SSMortOut)) + ((1 - OutdoorAdults) * (1 - SSMortIn) * (1 - RSPropSurfTrt * RSPropHouseTrt * RSSurv[Day])));
      }
      else if( RSSurv[Day] < 1 ) {
        DengueData[Day].OverallSurv = AdultSurvival[Day] * ((1 - OutdoorAdults) * (1 - RSPropSurfTrt * RSPropHouseTrt * RSSurv[Day]));
      }
      else if( SSSchedule[Day] ) {
        DengueData[Day].OverallSurv = AdultSurvival[Day] * ((OutdoorAdults * (1 - SSMortOut)) + ((1 - OutdoorAdults) * (1 - SSMortIn)));
      }
      else {
        DengueData[Day].OverallSurv = AdultSurvival[Day];
      }
      DengueData[Day].AvgDlyWeight = AdultWt;
      DengueData[Day].AdultDev = DevRateAdult;
    }

    // write adult mosquito age distribution


  } // end day


#ifdef _DEBUG
  // write logs
  _locationLog.WriteToDisk();
#endif

  //for( int i = 1; i <= YrLen; ++i ) {
  //  dengueOutputLog << DengueData[i].NewDlyFemales << DengueData[i].AvgDlyWeight << DengueData[i].OverallSurv << DengueData[i].AdultDev << Log<float>::eor;
  //}
  //dengueOutputLog.WriteToDisk()

}


//========
// CIML2.h
//========


void csport::CalcDailyTotals(void)
{
//========================================
//Calculate total eggs, pupae, ovi-adults,
//preovi-adults for the day
//========================================


  for( int i = 1; i <= MaxNumCt; i++ ) {
    EggsEmbDlyCt[i] = 0;
    EggsMatDlyCt[i] = 0;
  }

  for( int level = 1; level <= CINT((ContDesc[1].Height / 2) + .2f); level++ ) {
    EggsMatDlyCt[1] = EggsMatDlyCt[1] + C1MatureEggs[level];
    if( C1Eggs[level][MaxAgeEggs + 1] > 0 ) {
      int NumberCohorts = (int) C1Eggs[level][MaxAgeEggs + 1];
      for( int age = 1; age <= MaxAgeEggs; age++ ) {
        if( C1Eggs[level][age] > 0 ) {
          EggsEmbDlyCt[1] = EggsEmbDlyCt[1] + C1Eggs[level][age];
          NumberCohorts = NumberCohorts - 1;
        }
        if( NumberCohorts == 0 ) {
        	break;
        }
      }
    }
  }

  if( NumberOfContainers > 1 ) {
    for( int level = 1; level <= CINT((ContDesc[2].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[2] = EggsMatDlyCt[2] + C2MatureEggs[level];
      if( C2Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C2Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C2Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[2] = EggsEmbDlyCt[2] + C2Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 2 ) {
    for( int level = 1; level <= CINT((ContDesc[3].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[3] = EggsMatDlyCt[3] + C3MatureEggs[level];
      if( C3Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C3Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C3Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[3] = EggsEmbDlyCt[3] + C3Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 3 ) {
    for( int level = 1; level <= CINT((ContDesc[4].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[4] = EggsMatDlyCt[4] + C4MatureEggs[level];
      if( C4Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C4Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C4Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[4] = EggsEmbDlyCt[4] + C4Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 4 ) {
    for( int level = 1; level <= CINT((ContDesc[5].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[5] = EggsMatDlyCt[5] + C5MatureEggs[level];
      if( C5Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C5Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C5Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[5] = EggsEmbDlyCt[5] + C5Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 5 ) {
    for( int level = 1; level <= CINT((ContDesc[6].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[6] = EggsMatDlyCt[6] + C6MatureEggs[level];
      if( C6Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C6Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C6Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[6] = EggsEmbDlyCt[6] + C6Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 6 ) {
    for( int level = 1; level <= CINT((ContDesc[7].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[7] = EggsMatDlyCt[7] + C7MatureEggs[level];
      if( C7Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C7Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C7Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[7] = EggsEmbDlyCt[7] + C7Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 7 ) {
    for( int level = 1; level <= CINT((ContDesc[8].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[8] = EggsMatDlyCt[8] + C8MatureEggs[level];
      if( C8Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C8Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C8Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[8] = EggsEmbDlyCt[8] + C8Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  if( NumberOfContainers > 8 ) {
    for( int level = 1; level <= CINT((ContDesc[9].Height / 2) + .2f); level++ ) {
      EggsMatDlyCt[9] = EggsMatDlyCt[9] + C9MatureEggs[level];
      if( C9Eggs[level][MaxAgeEggs + 1] > 0 ) {
        int NumberCohorts = (int) C9Eggs[level][MaxAgeEggs + 1];
        for( int age = 1; age <= MaxAgeEggs; age++ ) {
          if( C9Eggs[level][age] > 0 ) {
            EggsEmbDlyCt[9] = EggsEmbDlyCt[9] + C9Eggs[level][age];
            NumberCohorts = NumberCohorts - 1;
          }
          if( NumberCohorts == 0 ) {
          	break;
          }
        }
      }
    }
  }

  for( int i = 1; i <= NumberOfContainers; i++ ) {
    LarvTotDlyCt[i] = 0;
    for( int age = 1; age <= MaxAgeLarv; age++ ) {
      LarvTotDlyCt[i] = LarvTotDlyCt[i] + Larvae[age][i].Number;
    }
  }

  for( int i = 1; i <= NumberOfContainers; i++ ) {
    PupTotDlyCt[i] = 0;
    for( int age = 1; age <= MaxAgePupae; age++ ) {
      PupTotDlyCt[i] = PupTotDlyCt[i] + Pupae[age][i].Number;
    }
  }

  for( int i = 1; i <= NumberOfContainers; i++ ) {
    PupWtDlyAveCt[i] = 0;
    int Count = 0;
    for( int age = 1; age <= MaxAgePupae; age++ ) {
      if( Pupae[age][i].Weight > 0 ) {
        Count = Count + 1;
        PupWtDlyAveCt[i] = PupWtDlyAveCt[i] + Pupae[age][i].Weight;
      }
    }
    if( Count > 0 ) {
      PupWtDlyAveCt[i] = PupWtDlyAveCt[i] / Count;
    }
  }

  // added to track cumulative new females
  for( int i = 1; i <= NumberOfContainers; i++ ) {
    CumulativeFemales[i] = CumulativeFemales[i] + AdultsNewDlyCt[i];
  }

  for( int age = 1; age <= MaxAgeOviAdults; age++ ) {
    TotOviAdults[Day] = TotOviAdults[Day] + OviAdults[age];
  }

  for( int age = 1; age <= MaxAgePreOviAdults; age++ ) {
    TotPreOviAdults[Day] = TotPreOviAdults[Day] + PreOviAdults[age];
  }



//===============================================
//Estimate cadaver contribution to available food
//===============================================


  for( int i = 1; i <= NumberOfContainers; i++ ) {
    cadavers[i] = (LarvCadWt[i] + PupCadWt[i]) * CadFoodEquiv;
    LarvCadWt[i] = 0;
    PupCadWt[i] = 0;
  }
}


void csport::CalcLISurvival(void)
{
  /* These survival calculations have a few problems.  First CS 1.0 considers the lag *
   * period to extend in time before the current day, scheduled for treatment. This   *
   * unituitive and wrong.
   *
   * When actually applying the survival due to a treatment, the survival is          *
   * multiplied onto an existing survival (possible from a previous overlapping       *
   * treatment).  However, this result is then compared to the current treatment's    *
   * survival, and if it is less than the current treatment's survival (which it      *
   * always will be with multiple interacting treatments), it is set to the current   *
   * current treatment's survival.                                                    *
   *                                                                                  */

  for( int i = 1; i <= NumberOfContainers; i++ ) {
    // applied survival is initially inverse to mortality
    // effect can be lost due to a dry container, where survival
    // then becomes 1.0, removing any treatment effect
    float LIMinSurv = 1 - LICont[i].Mort;

    for( int j = 1; j < YrLen; j++ ) {

      // check lag period for lost effect due to dry container
      if( LISchedule[i][j] == true ) {
        if( LICont[i].DryActivity == 1 ) {
          for( int k = j; k >= j - LICont[i].Lag; k-- ) {
            if( ContEnv[k][i].Depth <= 0 )
              LIMinSurv = 1.0f;
          }
        }

        // calculate survivals during the period of maximum effect
        for( int k = j; k <= j + LICont[i].MaxEff - 1; k++ ) {
          // check max effectiveness period for lost effect due to dry container
          if( ContEnv[k][i].Depth <= 0 && LICont[i].DryActivity == 1 ) {
            LIMinSurv = 1.0f;
          }

          LISurv[k][i] = LISurv[k][i] * LIMinSurv;
          if( LISurv[k][i] < LIMinSurv ) {
            // this comparison removes any possiblity to concurrent and cumulative treatment effects
            // the most recently applied treatment takes precent
            LISurv[k][i] = LIMinSurv;
          }
        }

        // calculate survivals during the period of declining effectiveness
        for( int k = j + LICont[i].MaxEff; k <= j + LICont[i].MaxEff + LICont[i].DecEff - 1; k++ ) {
          if( ContEnv[k][i].Depth <= 0 && LICont[i].DryActivity == 1 ) {
            LIMinSurv = 1;
          }
          float slope = (1 - LIMinSurv) / ((j + LICont[i].MaxEff + LICont[i].DecEff) - (j + LICont[i].MaxEff));
          LISurv[k][i] = LISurv[k][i] * (LIMinSurv + (k - (j + LICont[i].MaxEff)) * slope);
          if( LISurv[k][i] < LIMinSurv ) {
            LISurv[k][i] = LIMinSurv;
          }
        }
      }
      LIMinSurv = 1 - LICont[i].Mort;
    }
  }
}


void csport::CalcSeasonalFood(void)
{

  // reset all food values for the year for each container
  for( int j = 1; j <= MaxNumCt; j++ ) {
    for( int i = 1; i <= YrLen; i++ ) {
      ContEnv[i][j].Food = 0;
    }
  }

  // 1 day interval for stocastic food additions
  // 3 day interval for non stocastic food additions
  int StepSize;
  float RndFactor = 1;

  if( RndFood ) {
    StepSize = 1;
  }
  else {
    StepSize = 3;
  }

  for( int j = 1; j <= MaxNumCt; j++ ) {
    for( int i = 1; i <= 31; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 32; i <= 59; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 60; i <= 90; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 91; i <= 120; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 121; i <= 151; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 152; i <= 181; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 182; i <= 212; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 213; i <= 243; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 244; i <= 273; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 274; i <= 304; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 305; i <= 334; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
    for( int i = 335; i <= 365; i = i + StepSize ) {
      if( RndFood )
        RndFactor = (float) rand()/RAND_MAX * 2;
      ContEnv[i][j].Food = ContDesc[j].Month1 * StepSize * RndFactor;
    }
  }
}



//===========================================================================
//                        CONSUMPTION OF LARVAL FOOD
//===========================================================================
//
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
//===========================================================================


float csport::FoodEqn( float nt, float WT, float FT, float et )
{
  float foodConsumed = -nt * fT * pow(WT,b) * (1 - exp(-c * FT)) * et;

  return foodConsumed;
}



//===========================================================================
//                           LARVAL WEIGHT GAIN
//===========================================================================
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
//
//===========================================================================*/

float csport::WeightEqn( float WT, float FT, float et )
{
  float weightChange = a * fT * ( pow(WT,b) * (1 - exp(-c * FT)) - d1 * pow(WT,d2)) * et;

  return weightChange;
}


//=========
// CIMPR1.h
//=========


float csport::CalcWaterDepth( int iContainer, float YestDepth, float TodaysRain )
{
  float CurrentDepth;

  float WaterGain = TodaysRain * ContDesc[iContainer].WaterShedRatio;

  float CoverEffect;
  if( ContDesc[iContainer].Cover == 0 )
    CoverEffect = 1;
  else
    CoverEffect = 1 - ContDesc[iContainer].CoverRed;

  // Convert liter drawdown to cubic cm drawdown
  float HeightDrawDown;
  if( ContDesc[iContainer].DrawDown > 0 ) {
    if( ContDesc[iContainer].Diameter == 0 ) {
      HeightDrawDown = (ContDesc[iContainer].DrawDown * 1000) / (ContDesc[iContainer].Length * ContDesc[iContainer].Wide);
    }
    else {
      HeightDrawDown = (ContDesc[iContainer].DrawDown * 1000) / (3.141593f * pow(ContDesc[iContainer].Diameter/2, 2));
    }
  }
  else {
    HeightDrawDown = 0;
  }

  float Evaporation = .925636f + (.275191f * ContDesc[iContainer].Exposure) - (.009041f * RelHumid[Day]);
  
  float WaterOut = (Evaporation * CoverEffect) + HeightDrawDown;

  if( (YestDepth - WaterOut) < 0 )
    CurrentDepth = 0;
  else
    CurrentDepth = YestDepth - WaterOut;

  CurrentDepth = CurrentDepth + WaterGain;
  if( CurrentDepth > ContDesc[iContainer].Height )
    CurrentDepth = ContDesc[iContainer].Height;
  
  return CurrentDepth;
}


void csport::CalcWaterTemps( int iContainer, int iDay )
{
  int i = iContainer;

  int MoveAve = 1;

  if( ContVolume[i] > 500 )
    MoveAve = 4;
  if( 100 <= ContVolume[i] && ContVolume[i] <= 500 )
    MoveAve = 3;
  if( 5 <= ContVolume[i] && ContVolume[i] < 100 )
    MoveAve = 2;
  if( ContVolume[i] < 5 ) {
    ContEnv[Day][i].TempMax = (float) (15.033426 + (.266995f * TemperatureMin[Day]) + (.007053f * pow(TemperatureMax[Day],2)) + (7.685039f * pow(ContDesc[i].Exposure,2)));
    ContEnv[Day][i].TempMax = ContEnv[Day][i].TempMax * (1 - ContDesc[i].Cooling);
    ContEnv[Day][i].TempMin = 5.019385f - (1.363636f * ContDesc[i].Exposure) + (.807682f * TemperatureMin[Day]) + (.000982f * pow(TemperatureMax[Day],2));
    ContEnv[Day][i].TempAvg = (ContEnv[Day][i].TempMax + ContEnv[Day][i].TempMin) / 2;
    return;
  }


  // calculate maximum water temperature based on a variable moving average.
  float AveTemp = 0;
  if( (Day - MoveAve) < 0 ) {
    int TempDay = 366 - (MoveAve - Day);
    for( int j = TempDay; j <= YrLen; j++ ) {
      AveTemp = AveTemp + (float) (15.033426 + (.266995f * TemperatureMin[j]) + (.007053f * pow(TemperatureMax[j],2)) + (7.685039f * pow(ContDesc[i].Exposure,2)));
    }
    for( int j = 1; j <= Day; j++ ) {
      AveTemp = AveTemp + (float) (15.033426 + (.266995f * TemperatureMin[j]) + (.007053f * pow(TemperatureMax[j],2)) + (7.685039f * pow(ContDesc[i].Exposure,2)));
    }
  }
  else {
    for( int j = (Day - MoveAve) + 1; j <= Day; j++ ) {
      AveTemp = AveTemp + (float) (15.033426 + (.266995f * TemperatureMin[j]) + (.007053f * pow(TemperatureMax[j],2)) + (7.685039f * pow(ContDesc[i].Exposure,2)));
    }
  }

  ContEnv[Day][i].TempMax = AveTemp / MoveAve;
  ContEnv[Day][i].TempMax = ContEnv[Day][i].TempMax * (1 - ContDesc[i].Cooling);


  // calculate Minimum water temperature based on a variable moving average.
  AveTemp = 0;
  if( (Day - MoveAve) < 0 ) {
    int TempDay = 366 - (MoveAve - Day);
    for( int j = TempDay; j <= YrLen; j++ ) {
      AveTemp = AveTemp + (5.019385f - (1.363636f * ContDesc[i].Exposure) + (.807682f * TemperatureMin[j]) + (.000982f * pow(TemperatureMax[j],2)));
    }
    for( int j = 1; j <= Day; j++ ) {
      AveTemp = AveTemp + (5.019385f - (1.363636f * ContDesc[i].Exposure) + (.807682f * TemperatureMin[j]) + (.000982f * pow(TemperatureMax[j],2)));
    }
  }
  else {
    for( int j = (Day - MoveAve) + 1; j <= Day; j++ ) {
      AveTemp = AveTemp + (5.019385f - (1.363636f * ContDesc[i].Exposure) + (.807682f * TemperatureMin[j]) + (.000982f * pow(TemperatureMax[j],2)));
    }
  }

  ContEnv[Day][i].TempMin = AveTemp / MoveAve;

  // Make sure max temp >= min temp
  if( ContEnv[Day][i].TempMin > ContEnv[Day][i].TempMax )
    ContEnv[Day][i].TempMin = ContEnv[Day][i].TempMax;

  // Calculate Average water temperature based on a
  ContEnv[Day][i].TempAvg = (ContEnv[Day][i].TempMax + ContEnv[Day][i].TempMin) / 2;

}


void csport::MenuPreSimulation(void)
{
  CountContainers();
}


void csport::CountContainers(void)
{
  // init done by Location_ value now
  // count number of containers in use
  //NumberOfContainers = 0;
  //for( int i = 1; i <= MaxNumCt; i++ ) {
  //  if( ContDesc[i].title != "" ) {
  //    NumberOfContainers++;
  //  }
  //}

  // calculate each container's volume in liters
  for( int i = 1; i <= NumberOfContainers; i++ ) {
    if( ContDesc[i].Diameter == 0 ) {
      ContVolume[i] = (ContDesc[i].Length * ContDesc[i].Wide * ContDesc[i].Height) / 1000;
    }
    else {
      ContVolume[i] = (ContDesc[i].Height * 3.14159f * pow((ContDesc[i].Diameter/2), 2)) / 1000;
    }

  }
}


//=========
// CIMPR2.h
//=========


void csport::InitializeVariables(void)
{
  NewEggLayers = 0;
  EggLayers = 0;
  NewBiters = 0;
  OldBiters = 0;
  AdultWt = 0;
  PrintOnLongRun = 0;

  if( iAveStart == 0 && iAveStart == 0 ) {
    iAveStart = 1;
    iAveEnd = 365;
  }

  // init from Location_ now
  //NumberOfContainers = 0;

  // start with year 1
  Year = 1;
  PopFile = false;

  LBJDensity = 2.0f;
  LBJAttract = .1f;

  for( int i = 1; i <= MaxAgeOviAdults; i++ ) {
    MosqDistr.Number[i] = 0;
  }

  // parameters for larval weight function
  fT = .001f;

  // toggle controls off and manually clear schedules, CS 1.0 uses ReDim statements for same effect
  SR = false;
  SM = false;
  ED = false;
  OE = false;
  LI = false;
  SS = false;
  SSDensityFlag = false;
  RS = false;

  // clear shared schedules
  for( int i = 1; i <= YrLen; i++ ) {
    SRSchedule[i] = false;
    SMSchedule[i] = false;
    OESchedule[i] = false;
    SSSchedule[i] = false;
    RSSchedule[i] = false;
  }

  // clear per container schedules
  for( int i = 1; i <= MaxNumCt; i++ ) {
    for( int j = 1; j <= YrLen; j++ ) {
      EDSchedule[i][j] = false;
      LISchedule[i][j] = false;
    }
  }

  // clear location RS survivals and per container li survivals
  for( int i = 1; i <= 480; i++ ) {
    RSSurv[i] = 1.0f;
    for( int j = 1; j <= MaxNumCt; j++ ) {
      LISurv[i][j] = 1.0f;
    }
  }

  // kludge for REDIM ContEnv statement in CS 1.0 headers, must zero values
  // also day index starts at zero, violating one index, but CS 1.0 uses this
  // "previous" day for food intialization
  for( int i = 0; i <= YrLen; i++ ) {
    for( int j = 1; j <= MaxNumCt; j++ ) {
      ContEnv[i][j].Depth = 0;
      ContEnv[i][j].Food = 0;
      ContEnv[i][j].TempAvg = 0;
      ContEnv[i][j].TempMax = 0;
      ContEnv[i][j].TempMin = 0;
    }
  }
}


void csport::LocAssign(void)
{
  HumanDensity = 1;
  HumanAvail = 1;
  HumanGrowthRate = 1;
  MammalDensity = 0;
  MammalAvail = 0;
  MammalGrowthRate = 0;
  OutdoorAdults = (float) Location_.Biology_->Adult->ProportionOfAdultsRestingOutdoors;

  // read containers
  ContReadAll();
  
  // read weather
  WeaReadFile();
  
  // read biology
  BioReadFile();
}


csport::csport(const input::Location & loc)
: Location_(loc)
{
  C1Eggs = NULL;
  C1MatureEggs = NULL;
  C1CumDevEggs = NULL;
  C2Eggs = NULL;
  C2MatureEggs = NULL;
  C2CumDevEggs = NULL;
  C3Eggs = NULL;
  C3MatureEggs = NULL;
  C3CumDevEggs = NULL;
  C4Eggs = NULL;
  C4MatureEggs = NULL;
  C4CumDevEggs = NULL;
  C5Eggs = NULL;
  C5MatureEggs = NULL;
  C5CumDevEggs = NULL;
  C6Eggs = NULL;
  C6MatureEggs = NULL;
  C6CumDevEggs = NULL;
  C7Eggs = NULL;
  C7MatureEggs = NULL;
  C7CumDevEggs = NULL;
  C8Eggs = NULL;
  C8MatureEggs = NULL;
  C8CumDevEggs = NULL;
  C9Eggs = NULL;
  C9MatureEggs = NULL;
  C9CumDevEggs = NULL;


  for( int i = 0; i < MaxNumCt+1; i++ ) {
    EggsEmbDlyCt[i] = 0;
    EggsMatDlyCt[i] = 0;
    EggsNewDlyCt[i] = 0;

    EggsSurvTempDlyCt[i] = 0;
    EggsSurvSdDlyCt[i] = 0;
    EggsSurvPredDlyCt[i] = 0;

    SurvEggs[i] = 0;
    DevRateEggs[i] = 0;
    HatchLevel[i] = 0;
    EggInputLevel[i] = 0;

    LarvTotDlyCt[i] = 0;
    cadavers[i] = 0;
    LarvCadWt[i] = 0;
    LarvSurvTempDlyCt[i] = 0;

    DevRateLarv[i] = 0;
    NewlyHatched[i] = 0;
    MaxLarvWt[i] = 0;

    PupTotDlyCt[i] = 0;
    PupCadWt[i] = 0;
    PupSurvTempDlyCt[i] = 0;
    PupWtDlyAveCt[i] = 0;

    DevRatePupae[i] = 0;
    NewPupae[i] = 0;
    PupaeWt[i] = 0;

    AdultsNewDlyCt[i] = 0;
    ReturnCtOvi[i] = 0;
    CumulativeFemales[i] = 0;

    et[i] = 0;
    ContVolume[i] = 0;
    ContPref[i] = 0;

    ContDensity[i].Excluded = 0;
    ContDensity[i].Treated = 0;
    ContDensity[i].Untreated = 0;
    
    //LICont[i] = 0;
    //EDCont[i] = 0;
  }

  for( int i = 0; i < YrLen+1; i++ ) {
    newdailyeggs[i] = 0;

    DlyFecundity[i] = 0;

    NewAdultsHa[i] = 0;

    TotPreOviAdults[i] = 0;
    TotOviAdults[i] = 0;

    AdultSurvival[i] = 0;
    AdultSurvTemp[i] = 0;
    AdultSurvSD[i] = 0;
    AdultSurvDens[i] = 0;

    BitesHuman[i] = 0;
    BitesMammal[i] = 0;
    BitesHost[i] = 0;

    for( int j = 0; j < MaxNumCt+1; j++ ) {
      ContEnv[i][j].Depth = 0;
      ContEnv[i][j].Food = 0;
      ContEnv[i][j].TempAvg = 0;
      ContEnv[i][j].TempMax = 0;
      ContEnv[i][j].TempMin = 0;
    }
  }


  for( int i = 0; i < MaxAgePreOviAdults+1; i++ ) {
    PreOviAdults[i] = 0;
    CumDevPreOviAdults[i] = 0;
  }

  for( int i = 0; i < MaxAgeOviAdults+1; i++ ) {
    OviAdults[i] = 0;
    CumDevOviAdults[i] = 0;
  }

  for( int i = 0; i < 5+1; i++ ) {
    AdultWtAvgs[i] = 0;

    for( int j = 0; j < MaxNumCt+1; j++ ) {
      AdultsNewDlyCtMAvg[i][j] = 0;
    }
  }

  for( int i = 0; i < MaxAgeLarv+1; i++ ) {
    for( int j = 0; j < MaxNumCt+1; j++ ) {
      LarvSurvFood[i][j] = 0;
      Larvae[i][j].CumDev = 0;
      Larvae[i][j].FatBody = 0;
      Larvae[i][j].MaxFB = 0;
      Larvae[i][j].Number = 0;
      Larvae[i][j].Weight = 0;
      Larvae[i][j].WtChange = 0;
    }
  }

  for( int i = 0; i < MaxAgePupae+1; i++ ) {
    for( int j = 0; j < MaxNumCt+1; j++ ) {
      Pupae[i][j].CumDev = 0;
      Pupae[i][j].Number = 0;
      Pupae[i][j].Weight = 0;
    }
  }
}


csport::~csport(void)
{
  if( C1Eggs != NULL ) delete[] C1Eggs;
  if( C1MatureEggs != NULL ) delete C1MatureEggs;
  if( C1CumDevEggs != NULL ) delete[] C1CumDevEggs;
  if( C2Eggs != NULL ) delete[] C2Eggs;
  if( C2MatureEggs != NULL ) delete C2MatureEggs;
  if( C2CumDevEggs != NULL ) delete[] C2CumDevEggs;
  if( C3Eggs != NULL ) delete[] C3Eggs;
  if( C3MatureEggs != NULL ) delete C3MatureEggs;
  if( C3CumDevEggs != NULL ) delete[] C3CumDevEggs;
  if( C4Eggs != NULL ) delete[] C4Eggs;
  if( C4MatureEggs != NULL ) delete C4MatureEggs;
  if( C4CumDevEggs != NULL ) delete[] C4CumDevEggs;
  if( C5Eggs != NULL ) delete[] C5Eggs;
  if( C5MatureEggs != NULL ) delete C5MatureEggs;
  if( C5CumDevEggs != NULL ) delete[] C5CumDevEggs;
  if( C6Eggs != NULL ) delete[] C6Eggs;
  if( C6MatureEggs != NULL ) delete C6MatureEggs;
  if( C6CumDevEggs != NULL ) delete[] C6CumDevEggs;
  if( C7Eggs != NULL ) delete[] C7Eggs;
  if( C7MatureEggs != NULL ) delete C7MatureEggs;
  if( C7CumDevEggs != NULL ) delete[] C7CumDevEggs;
  if( C8Eggs != NULL ) delete[] C8Eggs;
  if( C8MatureEggs != NULL ) delete C8MatureEggs;
  if( C8CumDevEggs != NULL ) delete[] C8CumDevEggs;
  if( C9Eggs != NULL ) delete[] C9Eggs;
  if( C9MatureEggs != NULL ) delete C9MatureEggs;
  if( C9CumDevEggs != NULL ) delete[] C9CumDevEggs;
}


void csport::ClearSchedule( bool (&schedule)[YrLen+1] )
{
  for( int i = 1; i <= YrLen; ++i ) {
    schedule[i] = false;
  }
}


void csport::ClearSchedule( bool (&schedule)[MaxNumCt+1][YrLen+1] )
{
  for( int i = 1; i <= MaxNumCt; ++i ) {
    for( int j = 1; j <= YrLen; ++j ) {
      schedule[i][j] = false;
    }
  }

}


bool CheckBit( int indexBit, int value )
{
  if( value == 0 ) {
    // no set bits exists
    return false; 
  }

  else if( value > 0 ) {
    // 2's comp - MSB clear for positive number
    if( indexBit == 16 ) return false;
    else return true;

    // shift right until requested bit at LSB position
    int curBit = 1;
    while( curBit != indexBit ) {
      value = value / 2;
    }

    // use mod to see if LSB is set
    int remainder = value % 2;
    if( remainder == 1 ) return true;
    else return false;
  }

  else {
    // 2's comp - MSB set for negative number
    if( indexBit == 16 ) return true;
    else return false;

    // now continue with modular arithmetic


  }
}