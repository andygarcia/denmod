#ifndef CSPORT_H
#define CSPORT_H

#include "stdafx.h"
#include "../input/Location.h"
#include "../output/Log.h"
#include <string>

static const int YrLen = 365;
static const int MaxAgeEggs = 25;
static const int MaxAgeLarv = 100;
static const int MaxAgePupae = 25;
static const int MaxNumCt = 9;
static const int MaxAgePreOviAdults = 50;
static const int MaxAgeOviAdults = 50;

namespace sim {
namespace csp {

class csport
{
public:
  csport( const input::Location & loc );
  ~csport(void);

  class ContainerDescription
  {
  public:
    std::string title;          //Container name
    float density;              //Density/Ha
    float Height;               //Container height (cm)
    float Diameter;             //Container diameter (cm) - 0 if rectangular
    float Length;               //Container length (cm) - 0 if circular
    float Wide;                 //Container width (cm) - 0 if circular
    float Exposure;             //Exposure to sun (0-1)
    float WaterShedRatio;       //Water shed ratio
    float DrawDown;             //Manual drawdown - liters, 0 for none
    int Cover;                  //Cover - 1 for yes, 0 for no
    float CoverRed;             //Reduction in evap. loss from cover (0-1)
    float InitFood;             //Initial amount of food
    float FoodDecayRate;        //Decay rate of food
    float InitialEggs;          //initial number of eggs
    float Loss;                 //Rate at which containers are lost/month
    float Month1;               //Average daily additions of food by month
    float Month2;
    float Month3;
    float Month4;
    float Month5;
    float Month6;               
    float Month7;
    float Month8;
    float Month9;
    float Month10;
    float Month11;
    float Month12;
    float Cooling;              //Temperature reduction due to evap. cooling
  };

  class ContainerEnvironment
  {
  public:
    float Depth;
    float TempAvg;
    float TempMax;
    float TempMin;
    float Food;
  };

  class LarvalDescription
  {
  public:
    float Number;
    float CumDev;
    float Weight;
    float MaxFB;
    float FatBody;
    float WtChange;
  };

  class PupalDescription
  {
  public:
    float Number;
    float CumDev;
    float Weight;
  };

  class LarvicideControl
  {
  public:
    int NumTrts;
    int Start;
    int Interval;
    float Proportion;
    int Lag;
    float Mort;
    int MaxEff;
    int DecEff;
    int DryActivity;
  };

  class EggDestructionControl
  {
  public:
    int NumTrts;
    int StartDay;
    int Interval;
    float Reduction;
  };

  class ContainerDensity
  {
  public:
    float Untreated;
    float Treated;
    float Excluded;
  };

  class DengueOutDescription
  {
  public:
    float NewDlyFemales;      //New daily adults/ha
    float AvgDlyWeight;       //moving average of adult weight
    float OverallSurv;        //survival from environment and controls - do not apply to NewDlyFemales
    float AdultDev;           //adult development rate
  };

  class MosqAgeDescription
  {
  public:
    float Number[MaxAgeOviAdults+1];
  };

public:
  const input::Location & Location_;

  int iAveStart;
  int iAveEnd;

  float EggsEmbDlyCt[MaxNumCt+1];
  float EggsMatDlyCt[MaxNumCt+1];
  float EggsNewDlyCt[MaxNumCt+1];

  // MatureEggs arrays are indexed by [Level]
  // Eggs and CumDevEggs are indexed by [Level][Age]
  float** C1Eggs;
  float*  C1MatureEggs;
  float** C1CumDevEggs;
  float** C2Eggs;
  float*  C2MatureEggs;
  float** C2CumDevEggs;
  float** C3Eggs;
  float*  C3MatureEggs;
  float** C3CumDevEggs;
  float** C4Eggs;
  float*  C4MatureEggs;
  float** C4CumDevEggs;
  float** C5Eggs;
  float*  C5MatureEggs;
  float** C5CumDevEggs;
  float** C6Eggs;
  float*  C6MatureEggs;
  float** C6CumDevEggs;
  float** C7Eggs;
  float*  C7MatureEggs;
  float** C7CumDevEggs;
  float** C8Eggs;
  float*  C8MatureEggs;
  float** C8CumDevEggs;
  float** C9Eggs;
  float*  C9MatureEggs;
  float** C9CumDevEggs;

  // These allow iterative access to egg arrays versus named access (C1, C2, etc.)
  float ** EggArrays[MaxNumCt+1];
  float * EggMatureArrays[MaxNumCt+1];
  float ** EggDevArrays[MaxNumCt+1];


  float PropHatchflood;
  float PropHatchSpont;
  float newdailyeggs[YrLen+1];

  float egghsdth, egglsdth, egghsdsu, egglsdsu;
  float eggtemp1, eggtemp2, eggtemp3, eggtemp4;
  float eggwetsu, eggdrysu, eggdiapausetemp;
  float EggSurvNom, FecundityCoef;

  float EggsSurvTempDlyCt[MaxNumCt+1];
  float EggsSurvSdDlyCt[MaxNumCt+1];
  float EggsSurvPredDlyCt[MaxNumCt+1];

  float DlyFecundity[YrLen+1];
  float PredLT, PredHT, PredSurLT, PredSurHT;

  // no declaration found
  float SurvEggs[MaxNumCt+1];
  float DevRateEggs[MaxNumCt+1];
  int HatchLevel[MaxNumCt+1];
  int EggInputLevel[MaxNumCt+1];


  //======
  //LARVAE
  //======

  float LarvTotDlyCt[MaxNumCt+1];
  float LarvSurvNom;
  float cadavers[MaxNumCt+1];
  float CadFoodEquiv;
  float larvpwtsu, larvnwtnfbsu, larvnwtfbsu;
  float LarvCadWt[MaxNumCt+1];
  float LarvTemp1, LarvTemp2, LarvTemp3, LarvTemp4;
  float LarvSurvTempDlyCt[MaxNumCt+1];
  float LarvSurvFood[MaxAgeLarv+1][MaxNumCt+1];
  float LarvaeMaxCD;

  // no declaration found
  float DevRateLarv[MaxNumCt+1];
  float NewlyHatched[MaxNumCt+1];
  float MaxLarvWt[MaxNumCt+1];


  //=====
  //PUPAE
  //=====

  float PupTotDlyCt[MaxNumCt+1];
  float PupSurvNom, EmergenceSuccess;
  float PupWtSlope, PupWtConst, PupMinWt, PupMinAge;
  float PupCadWt[MaxNumCt+1];
  float pupgeneticsu;
  float PupTemp1, PupTemp2, PupTemp3, PupTemp4;
  float PupSurvTempDlyCt[MaxNumCt+1];
  float PupWtDlyAveCt[MaxNumCt+1];

  // no declaration found
  float DevRatePupae[MaxNumCt+1];
  float NewPupae[MaxNumCt+1];
  float PupaeWt[MaxNumCt+1];


  //=======================
  //ADULTS - PREOVIPOSITION
  //=======================


  float PreOviAdults[MaxAgePreOviAdults+1];
  float CumDevPreOviAdults[MaxAgePreOviAdults+1];
  float TotPreOviAdults[YrLen+1];

  float AdultsNewDlyCt[MaxNumCt+1];
  float NewEggLayers;
  float PercentFemale, InterFeeding;
  float AdultDensLTH, AdultDensHTH, AdultDensLSU, AdultDensHSU;
  float NewAdultsHa[YrLen+1];
  float NewBiters, OldBiters;


  //====================
  //ADULTS - OVIPOSITION
  //====================


  float OviAdults[MaxAgeOviAdults+1];
  float CumDevOviAdults[MaxAgeOviAdults+1];
  float TotOviAdults[YrLen+1];

  float AdultSurvival[YrLen+1];
  float AdultSurvTemp[YrLen+1];
  float AdultSurvSD[YrLen+1];
  float AdultSurvDens[YrLen+1];

  float survadnom;
  float adtemp1, adtemp2, adtemp3, adtemp4;
  float adlsdth, adhsdth, adlsdsu, adhsdsu;
  float OutdoorAdults;
  float OviTemperature, EggLayers;
  float ReturnOviRate;
  float ReturnCtOvi[MaxNumCt+1];

  float AdultWt;
  float AdultWtAvgs[5+1];                       // 1's indexing for histories as well
  float AdultsNewDlyCtMAvg[5+1][MaxNumCt+1];

  float CumulativeFemales[MaxNumCt+1];


  //==========================
  //DEVELOPMENT RATE VARIABLES
  //==========================

  float EggsP25, EggsDHa, EggsDH, EggsTh2;
  float LarvP25, LarvDHa, LarvDH, LarvTh2;
  float PupaeP25, PupaeDHa, PupaeDH, PupaeTh2;
  float AdultP25, AdultDHa, AdultDH, AdultTh2;
  float r, DevRateLarv26;


  //======================
  //LARVAL WEIGHT FUNCTION
  //======================

  float a, fT, b, c, d1, d2, initw;
  float et[MaxNumCt+1];


  //===================
  //TREATMENT VARIABLES
  //===================

  int AnyControls, ControlBeeps;

  bool SR;
  bool SRSchedule[YrLen+1];
  float SRReductRate[MaxNumCt+1];
  int SRTreatNum, SRStartDay, SRTreatInter;

  bool ED;
  bool EDSchedule[MaxNumCt+1][YrLen+1]; // each container has schedule

  bool OE;
  bool OESchedule[YrLen+1];
  float OEReductRate[MaxNumCt+1], OERecoverRate[MaxNumCt+1];
  int OETreatNum, OEStartDay, OETreatInter;

  bool LI;
  bool LISchedule[MaxNumCt+1][YrLen+1];
  float LISurv[480][MaxNumCt+1];

  bool SS;
  bool SSSchedule[YrLen+1];
  int SSNumTrts, SSStartDay, SSInterval;
  float SSMortOut, SSMortIn;
  bool SSDensityFlag;
  float SSMosqDensity;

  bool RS;
  int RSNumTrts, RSStartDay, RSInterval;
  bool RSSchedule[YrLen+1];
  float RSSurv[480];
  float RSMaxMort;
  int RSDaysMax, RSDaysRes;
  float RSPropSurfTrt, RSPropHouseTrt;

  bool SM;
  bool SMSchedule[YrLen+1];
  int SMTreatNum, SMStartDay, SMTreatInter;
  float SMNumber, SMRate, SMComp, SMSurvRatio;
  float SMPop[YrLen+1], MalePop[YrLen+1];



  //=============
  //MISCELLANEOUS
  //=============

  bool PopFile;

  int Year, Day;

  int StartDate;
  int EndDate;

  float TemperatureMax[YrLen+1];
  float TemperatureMin[YrLen+1];
  float TemperatureAvg[YrLen+1];
  float Rain[YrLen+1];
  float RelHumid[YrLen+1];
  float SD[YrLen+1];

  int NumberOfContainers;

  float HumanDensity, MammalDensity, HumanAvail, MammalAvail;
  float HumanGrowthRate, MammalGrowthRate;

  float ContVolume[MaxNumCt+1];
  float ContPref[MaxNumCt+1];
  float LBJDensity, LBJAttract;
  int EulerSteps;

  float BitesHuman[YrLen+1];
  float BitesMammal[YrLen+1];
  float BitesHost[YrLen+1];

  float DBloodLWt, DBloodUWt, DBloodLProp, DBloodUProp;

  bool RndFood, DengueOutput;
  int CurSimYear, EndSimYear;
  bool PrintOnLongRun;

  LarvalDescription Larvae[MaxAgeLarv+1][MaxNumCt+1];
  PupalDescription Pupae[MaxAgePupae+1][MaxNumCt+1];

  ContainerDescription ContDesc[MaxNumCt+1];
  ContainerEnvironment ContEnv[YrLen+1][MaxNumCt+1];
  ContainerDensity ContDensity[MaxNumCt+1];

  LarvicideControl LICont[MaxNumCt+1];
  EggDestructionControl EDCont[MaxNumCt+1];

  MosqAgeDescription MosqDistr;

public:
  void cimmain(void);

  void BioReadFile(void);
  void ClearEggArrays(void);
  void ContReadAll(void);
  void ControlFileRead(void);
  float DevelopmentRate( float p25, float tempt, float dha, float dh, float th2, float r);
  void ReadDefaultParms(void);
  void StartProgram(void);
  bool Year1NoPop(void);
  void WaterDepthTemp(void);
  void WeaReadFile(void);
  int CINT( float value );
  int INT( float value );
  float * ReDim( int length );
  float ** ReDim( int numRows, int numCols );
  void ClearSchedule( bool (&schedule)[YrLen+1] );
  void ClearSchedule( bool (&schedule)[MaxNumCt+1][YrLen+1] );

  void MainLoop(void);

  float FoodEqn( float nt, float WT, float FT, float et );
  float WeightEqn( float WT, float FT, float et );
  void CalcDailyTotals(void);
  void CalcLISurvival(void);
  void CalcSeasonalFood(void);

  float CalcWaterDepth( int iContainer, float YestDepth, float TodaysRain );
  void CalcWaterTemps( int iContainer, int iDay );
  void MenuPreSimulation(void);
  void CountContainers(void);

  void InitializeVariables(void);
  void LocAssign(void);

#ifdef _DEBUG
  output::LocationLog _locationLog;
  output::AdultSurvivalLog _adultSurvivalLog;
#endif
};

};
};

#endif
