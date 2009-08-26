#ifndef DSPORT_H
#define DSPORT_H

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "PdsRng.h"
#include "../input/Weather.h"

#define EMULATE_PDS_RAND true



namespace ds {
namespace port {  


class Location;
class HumanPopulation;

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



class DebugOutput
{
public:
  // CalcDeaths()
  float CalcDeathsArraySize;

  // CalcBirths()
  float CalcBirthsArraySize;

  // InitInfectives()
  float InitInfectivesArraySize;

  // MosqLifeCycle()
  float DMealProp;

  float EggersNew;
  float BitersNew;

  float EggersOld;
  float BitersOld;

  float EIPTranNew[4+1];
  float BitersInfdNewDB[4+1];

  float EIPTranOld[4+1];
  float BitersInfdOldDB[4+1];

  float BitersInfd[4+1];

  float EggersInfv[4+1];
  float BitersInfv[4+1];

  float BitersTotal;

  float MosqTotal;
  float MosqInfvTotal[4+1];

  // HumToMosqTrans()
  float BitesPerPerson;

  // CalcNewInocMosquitoes()
  float MosqInocEstimate[4+1];
  float NewDlyMosqInoc[4+1];
  float NewInfd[4+1];
  float OldInfd[4+1];

  // MosqToHumTrans()
  // CalcNewInocHumans()
  float HumInocEstimate[4+1];
  float NewDlyHumInoc[4+1];
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

  DebugOutput _debugOutput;
};


typedef DiskSpooler DailyLocationOutput;
typedef std::vector<DailyLocationOutput> LocationOutput;



class CimSimOutDescription
{
public:
  float NewDlyFemales;          // New dly adults/ha
  float AvgDlyWeight;           // moving average of adult weight
  float OverallSurv;            // survival from environment and controls - don't apply to NewDlyFemales
  float AdultDev;               // daily adult development
};



enum Serotype
{
  D1 = 1,
  D2,
  D3,
  D4,
  Maternal
};



class dsport
{
// Constructors
public:
  dsport( ds::port::Location * location, bool doInfection, bool infectFirstYearOnly, bool useRdsSequences );
  virtual ~dsport(void);

// Methods
public:
  void Start(void);

  void ReadWeather( int year );
  void ReadMos( int year );
      
  void denmain(void);

  static int CINT( float value );
  static int INT( float value );
  float RND( std::string callingMethod );

  void InitializeHumanPopulation(void);
  void InitializeHumanSeroprevalence(void);
  void CalculateEipFactors(void);

  void InitInfectives(void);
  float EIPEnzKin( float temp );
  void MosqLifeCycle(void);
  void HumToMosqTrans(void);
  void CalcNewInocMosquitoes( int iType );
  float Factorial( int n );
  void MosqToHumTrans(void);
  void CalcNewInocHumans( int iType );
  void SpoolToDisk(void);
  void MenuPostSim(void);

  void WriteOutput(void);

public:
  const float GasCoef;
  LocationOutput LocationOutput_;
  
  HumanPopulation * _humanPopulation;

  std::vector<VirusIntroductionProfile> VirusIntro;
  std::vector<VirusDesc> Virus;       // Virus parameters

  int MANADurat;                      // Duration of MANA in days
  int MAEADurat;                      // Duration of MAEA in days
  int HetImmunDurat;                  // Duration of heterologous immun. - days

  int Day;                                    // Simulation day
  int Year;                                   // Simulation year

  std::vector<std::vector<bool>> AddedInfections;             // Bit array for intro. schedule
  bool AddInfvFlag;                           // Flag for adding infection

  int SimYear;              // Number of simulation years run
  int EndYear;              // End of simulation
  float HumHostDensity;     // Humans/ha
  float ClusterSize;        // Cluster size for humans

  std::vector<float> TemperatureMax;
  std::vector<float> TemperatureMin;
  std::vector<float> TemperatureAvg;
  std::vector<float> Rain;
  std::vector<float> RelHumid;
  std::vector<float> SD;

  std::vector<float> EIPFactor;

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

  // probability human to mosquito infection
  float HumToMosLTiter;           // Low titer
  float HumToMosLInf;             //  prob.
  float HumToMosHTiter;           // High titer
  float HumToMosHInf;             //  prob.

  float MosqToHumProb;            // Prob of Mosq to human transmission

  // extrinsic incubation factor
  float EipLTiter;                // low titer log
  float EipLFactor;               // low titer factor
  float EipHTiter;                // high titer log
  float EipHFactor;               // high titer factor
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

  std::map<int, std::vector<CimSimOutDescription>> CimsimDataByYear_;
  csinput::Weather * Weather_;

  void OutputMosquitoes(void);

  PdsRng _pdsRng;

  DebugOutput _dailyDebugOutput;
};

};

};

#endif
