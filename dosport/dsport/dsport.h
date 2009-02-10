#ifndef DSPORT_H
#define DSPORT_H

#include <string>
#include <map>
#include <vector>
#include "../csinput/Weather.h"



namespace ds {

namespace sim {  


class Location;

class MAEAInfectionParms
{
public:
  float Prob;                  // probability of HF/SS
  float Mortality;             // associated mortality
};



class SequentialInfectionParms
{
public:
  int Min;                  // infection window - minimum months from primary infection
  int Max;                  // infection window - maximum months from primary infection
  float Prob;               // probability of HF
  float CutOff;             // at-risk cutoff age
  float Mortality;          // associated mortality
};



class SequentialInfectionValues
{
public:
  float F1T2;                // first 1 then 2 - number of individuals
  float F1T3;
  float F1T4;
  float F2T1;
  float F2T3;
  float F2T4;
  float F3T1;
  float F3T2;
  float F3T4;
  float F4T1;
  float F4T2;
  float F4T3;
  float FMT1;
  float FMT2;
  float FMT3;
  float FMT4;
};



// describes the age class structure
class AgeDesc
{
public:
  int Rank;             // class - a value of 1 to 18
  int FDay;             // start age of class - in days
  int LDay;             // end age of class - in days - max. age = 30,000 days
};



// describes human demographics
class HumanDemo
{
public:
  int Rank;               // age class
  float Prop;             // proportion of population in age class
  float DRate;            // yearly death rate per 1000 for age class
  float BRate;            // yearly birth rate per 1000 for age class
};



// Virus parameters
class VirusDesc
{
public:
  float Viremia;          // number of mosquito infectious doses
  int Incub;              // incubation period in days
  int Durat;              // duration of viremia in days
};



class VirusIntroductionProfile
{
public:
  int Trts;               // Number of infective introductions
  int SDay;               // Start infectious introductions on this day
  int Intv;               // Interval for introductions
  float Hums;             // Number of infective humans to introduce
  float Mosq;             // Number of infective mosquitoes to introduce
};



class MaternalTransmission
{
public:
  int MANA;               // maternally acquired neutralizing antibody
  int MAEA;               // maternally acquired enhancing antibody
};



class DiskSpooler
{
public:
  float Incubate1;                        // Number of humans incubating
  float Incubate2;                        // Number of humans incubating
  float Incubate3;                        // Number of humans incubating
  float Incubate4;                        // Number of humans incubating
  float Viremic1;                         // Number of humans infective
  float Viremic2;                         // Number of humans infective
  float Viremic3;                         // Number of humans infective
  float Viremic4;                         // Number of humans infective
  float MosqTotal;                        // Total daily mosquitoes
  float MosqInfvTotal[4+1];               // Total infective mosquitoes
  int InfvBites;                          // New potential inoculations
  float EIPDevRate[4+1];                  // Extrinsic incubation period rate - daily
  float NumHumans;                        // Number of humans
  float SerPos[23+1][4+1];                // Percent of indiv. in age class that are seropositive
  float NewHumCases[4+1];                 // Number of new human cases/day/serotype
  SequentialInfectionValues SeqInfVals;   // Daily sequential value statistics
};


typedef DiskSpooler DailyLocationOutput;
typedef std::map<int, DailyLocationOutput> LocationOutput;



class CimSimOutDescription
{
public:
  float NewDlyFemales;          // New dly adults/ha
  float AvgDlyWeight;           // moving average of adult weight
  float OverallSurv;            // survival from environment and controls - don't apply to NewDlyFemales
  float AdultDev;               // daily adult development
};



class LocationStructure
{
  std::string Region;
  std::string Country;
  std::string City;
  std::string Weather;
  std::string Demography;
  std::string CimEntomology;
  std::string Serology;
  std::string Virology;
  std::string Entomology;
  std::string CimPopulation;
  std::string Status;
};



class dsport
{
public:
  LocationOutput LocationOutput_;
public:
  dsport( ds::port::Location * location );
  void Start(void);

  DailyLocationOutput & GetLocationOutputByIndex( int index );

  void ReadWeather( int year );
  void ReadMos( int year );
      
  // methods correlate to subs/functions in DS 1.0, in order of appearance in source code
  // denmain() begins with module level code in DENMAIN.BAS
  void denmain(void);
  void DefineAgeClass(void);
  //void TextGraphParms();
  void ReadDefaultParms(void);
  //void LocReadData();
  void LocAssignData(void);
  void MainInitialization(void);
  void InitAgeClasses(void);
  static int CINT( float value );
  static int INT( float value );
  float RND(void);
  void InitSeroprevalence(void);
  void CalcDeaths( std::vector<float> & CDeaths );
  void CalcBirths( std::vector<float> & CBirths );
  void InitInfectives(void);
  int DeterminePosition( int IAge );
  void PurgeMaternal( int iOff );
  float EIPEnzKin( float temp );
  void MosqLifeCycle(void);
  void HumToMosqTrans(void);
  void CalcNewInocMosquitoes( int iType );
  float Factorial( int n );
  void MosqToHumTrans( int iOldAge );
  void CalcNewInocHumans( int iType, int iOldAge );
  void RankPop(void);
  void SeroRank( int iElement, int iRank );
  void CalcSeqInfs( int iVirType, int iPerAge, int iD1Inoc, int iD2Inoc, int iD3Inoc, int iD4Inoc );
  void AgeAtDeath( int iPerAge );
  void PurgeHFDeaths(void);
  void SpoolToDisk( int SpRecNum );
  void MenuPostSim(void);


public:
  // DENCOMM.INC
  static const int MaxPopSize = 20000;
  static const int MaxAgeMosq = 50;
  static const int YrLen = 365;
  const float GasCoef;
  
  //std::string WeaExt$ = ".DLY"
  //std::string EntInExt$ = ".BIO"
  //std::string DemInExt$ = ".AGE"
  //std::string SerInExt$ = ".APO"
  //std::string VirInExt$ = ".VIR"
  //std::string CimEntExt$ = ".MOS"
  //std::string DemOutExt$ = ".DEM"
  //std::string SerOutExt$ = ".SER"
  //std::string VirOutExt$ = ".INF"
  //std::string EntOutExt$ = ".MDA"
  //std::string CimPopExt$ = ".POP"
  //std::string LocFile$ = "DENLOCAT.DAT"
  //std::string SpoolFile$ = "DATA.SPO"
  
  int InitialPopSize;   //  TODO - default set at 10000

  //MAEAInfectionParms MAEAInfPrms[4+1];
  //SequentialInfectionParms SeqInfPrms[12+1];    // sequential infection params
  std::vector<MAEAInfectionParms> MAEAInfPrms;
  std::vector<SequentialInfectionParms> SeqInfPrms;
  SequentialInfectionValues DlySeqInfVals;      // daily infection

  std::vector<VirusIntroductionProfile> VirusIntro;

  AgeDesc AgeClass[18+1];       // population classes defined

  std::vector<int> Indiv;            // Age of each individual and age of infection
  std::vector<int> Deng1;            // age of inoculations - dengue 1
  std::vector<int> Deng2;            // age of inoculations - dengue 2
  std::vector<int> Deng3;            // age of inoculations - dengue 3
  std::vector<int> Deng4;            // age of inoculations - dengue 4
  std::vector<int> AgeDistr;         // Num. of indvs. in each age class
  std::vector<int> InitAgeDistr;     // Initial age distribution
  std::vector<std::vector<int>> SerDistr;         // Num. sero-pos. individuals
  std::vector<std::vector<int>> InitSerDistr;     // Init. serolog. distribution
  std::vector<float> CumHFDeaths;    // number of deaths for ages 0-15

  std::vector<std::vector<float>> SerProp;          // Ref. - Seroprev. statistics
                                                    // Class by prop. with den1-den4
  std::vector<HumanDemo> PopProp;     // Reference - Human pop. statistics
  int ArraySize;                      // Actual size of indiv() array
  std::vector<VirusDesc> Virus;       // Virus parameters
  int MANADurat;                      // Duration of MANA in days
  int MAEADurat;                      // Duration of MAEA in days
  int HetImmunDurat;                  // Duration of heterologous immun. - days
  //COMMON SHARED WeaFile$
  //COMMON SHARED WeaPath$
  //COMMON SHARED TempPath$
  //COMMON SHARED OutPath$
  //COMMON SHARED CimPopPath$
  //COMMON SHARED CimEntPath$
  //COMMON SHARED EntInFile$
  //COMMON SHARED DemInFile$                  'Human demographics input file
  //COMMON SHARED SerInFile$                  'Human serology input file
  //COMMON SHARED VirInFile$                  'Virology input file
  //COMMON SHARED CimEntFile$                 'Entomology input file
  //COMMON SHARED CimPopFile$                 'Saved population file from CimSim
  //COMMON SHARED Location$                   'Geographic location
  //COMMON SHARED LocNumber AS int            'record number of current location
  int Day;                                    // Simulation day
  int Year;                                   // Simulation year
  std::vector<std::vector<int>> Incub;                    // number of humans with incubating virus by class/virus
  std::vector<std::vector<int>> Infective;                // number of infective humans by class/virus
  std::vector<std::vector<int>> HomImm;                   // human homologous immunity by class/virus
  std::vector<std::vector<int>> HetImm;                    // human heterologous immunity by class/virus
  std::vector<int> TotDlyIncub;               // 
  std::vector<int> TotDlyInfective;           // Total daily values by virus
  std::vector<int> TotDlyHomImm;              // 
  std::vector<int> TotDlyHetImm;              // 
  std::vector<int> NewDlyInfective;           // New infective cases on each day
  std::vector<MaternalTransmission> MatAnti;  // Number of MANA and MAEA

  std::vector<std::vector<bool>> AddedInfections;             // Bit array for intro. schedule
  bool AddInfvFlag;                           // Flag for adding infection
  // COMMON SHARED InitInfvBiters AS INTEGER     // Infective biters to add
  // COMMON SHARED InitInfvHumans AS INTEGER     // Infective humans to add
  // COMMON SHARED InitInfvType AS INTEGER       // Serotype of infective bites
  // COMMON SHARED InitInfvTrts AS INTEGER       // Number of infectious introductions
  // COMMON SHARED InitInfvSDay AS INTEGER       // Day of intro. for infective biters
  // COMMON SHARED InitInfvInterval AS INTEGER   // Infectious intro. interval

  int InitArraySize;        // Size of array at initialization
  int OldArraySize;         // Previous years value
  int Stepping;             // Step or continuous run
  int Restart;              // Restart Flag
  int Continuation;         // Continue simulation
  int EndYear;              // End of simulation
  int SimYear;              // Number of simulation years run
  float HumHostDensity;     // Humans/ha
  float ClusterSize;        // Cluster size for humans

  std::vector<float> TemperatureMax;
  std::vector<float> TemperatureMin;
  std::vector<float> TemperatureAvg;
  std::vector<float> Rain;
  std::vector<float> RelHumid;
  std::vector<float> SD;

  float EIPTempAdjust;

  std::vector<int> TotBirths;
  std::vector<int> TotDeaths;

  std::vector<float> NewMosqSusc;         // Susc. new mosquitoes
  std::vector<float> NewMosqSuscCD;       // Gonotrophic development

  std::vector<float> OldMosqSusc;         // Susc. old mosquitoes
  std::vector<float> OldMosqSuscCD;       // Gonotrophic development

  std::vector<std::vector<float>> NewMosqInfd;         // New Infd Mosq - 1 and gono. cycle
  std::vector<std::vector<float>> NewMosqInfdCD;       // Gonotrophic dev.  CD>1
  std::vector<std::vector<float>> NewMosqInfdEIP;      // Extrinsic incubation period

  std::vector<std::vector<float>> OldMosqInfd;         // Old infd mosq - 2 gono. cycle
  std::vector<std::vector<float>> OldMosqInfdCD;       // Gonotrophic dev.  CD>.58
  std::vector<std::vector<float>> OldMosqInfdEIP;      // Extrinsic incubation period

  std::vector<std::vector<float>> MosqInfv;            // Infective mosquitoes
  std::vector<std::vector<float>> MosqInfvCD;          // Gonotrophic Development

  std::vector<CimSimOutDescription> CimSimData;

  float HumToMosLTiter;           // Low titer      Probability that a mosq.
  float HumToMosLInf;             //  prob.         becomes infected when biting
  float HumToMosHTiter;           // High titer     an infected host.
  float HumToMosHInf;             //  prob.

  float MosqToHumProb;            // Prob of Mosq to human transmission

  float EipLTiter;                // Low titer      Extrinsic incubation factor
  float EipLFactor;               //  factor
  float EipHTiter;                // High titer
  float EipHFactor;               //  factor
  std::vector<float> EIPDevRate;  // calculated EIP for the day

  float StochTransNum;            // numbers lower than this are proc. stochastically

  float PropOnHum;                // Prop. of biters feeding on humans
  float FdAttempts;               // Prop. of biters being interrupted
  float PropDifHost;              // Prop. of inter. biters feeding on dif. host
  float PropOutdoor;              // Prop. mosq. resting outdoors (space sprays)

  float EnzKinDR;                 // 
  float EnzKinEA;                 // Enzyme kinetics coefficients
  float EnzKinEI;                 // 
  float EnzKinTI;                 // 

  float DBloodLWt;                // 
  float DBloodUWt;                // Double blood meal parameters
  float DBloodUProp;              // 
  float DBloodLProp;              // 

  float BitersTotal;                          // Total biters (susc/infd/infv)
  float BitersNew;                            // New susceptible biters
  float BitersOld;                            // Old susceptible biters
  std::vector<float> BitersInfv;              // Infective biters
  std::vector<float> BitesPerPerson;          // feeds per person
  float MosqTotal;                            // Total daily mosquitoes
  std::vector<float> MosqInfvTotal;           // Total infective mosquitoes by type
  int NewDlyHumInoc;                          // potential no. of new infected humans
  std::vector<float> BitersInfdNewDB;         // Number of new double bloods from yesterday
  std::vector<float> BitersInfdOldDB;         // Number of old double bloods from yesterday

  // COMMON SHARED Demography$, Entomology$, Serology$, Virology$

  // DENDYNAMIC.INC
  std::vector<float> CumDeaths;               // Cum. death rate for a class
                                              // holds fractional deaths
  std::vector<float> CumBirths;               // Cum. birth rate for a class
                                              // holds fractional births

  std::map<int, std::vector<CimSimOutDescription>> CimsimDataByYear_;
  csinput::Weather * Weather_;
};

};

};

#endif
