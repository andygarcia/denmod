#ifndef DS_SIMLOCATION_H
#define DS_SIMLOCATION_H

#include <string>
#include <vector>
#include "Population.h"
#include "SimClasses.h"
#include "../input/Location.h"
#include "../input/Control.h"
#include "../output/DensimOutput.h"
#include "../output/MosData.h"
#include "../output/PopData.h"



namespace sim {
namespace ds {

class SimLocation
{
// Constructors
public:
  SimLocation( const input::Location * location, output::MosData * mosData );
  ~SimLocation(void);

// Methods
public:
  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date stopDate );

  output::DensimOutput * GetSimOutput(void);

private:
  output::DensimOutput::DailyLocationOutput & GetLocationOutputByIndex( int index );

public:
  void ReadWeather( int year );
  void ReadMos( int year );

  // methods correlate to subs/functions in DS 1.0, in order of appearance in source code
  // denmain() begins with module level code in DENMAIN.BAS
  void denmain(void);
  void InitializePopulation(void);
  void InitializeSeroprevalence(void);
  void AdjustEipByTiter(void);

  void CalculateDeaths(void);
  void CalculateBirths(void);
  void AgePopulation(void);

  void IntroduceInfection(void);
  void PurgeMaternal( int iOff );
  double EIPEnzKin( double temp );
  void MosqLifeCycle(void);
  void HumToMosqTrans(void);
  void CalcNewInocMosquitoes( int iType );
  double Factorial( int n );
  void MosqToHumTrans( int iOldAge );
  void CalcNewInocHumans( int iType, int iOldAge );
  void RankPop(void);
  void SeroRank( int iElement, int iRank );
  void CalcSeqInfs( int iVirType, int iPerAge, int iD1Inoc, int iD2Inoc, int iD3Inoc, int iD4Inoc );
  void AgeAtDeath( int iPerAge );
  void PurgeHFDeaths(void);
  void SpoolToDisk(void);

private:
  void ComparePopulation(void);
  void ComparePopulationAndSerotypes(void);
  static int CINT( double value );
  static int INT( double value );
  double RND(void);
  int DeterminePosition( int IAge );

// Fields
public:
  static const int MaxPopSize = 100000;
  static const int MaxAgeMosq = 50;
  static const int YrLen = 365;
  const double GasCoef;

private:
  const input::Location * Location_;
  output::MosData * MosData_;
  output::DensimOutput * Output_;
  
public:
  boost::gregorian::date BeginDate_;
  boost::gregorian::date EndDate_;

  int InitialPopSize;   //  TODO - default set at 10000

  SequentialInfectionValues DlySeqInfVals;      // daily infection

  AgeClass AgeClasses[18+1];       // population classes defined

  std::vector<int> Indiv;            // Age of each individual and age of infection
  std::vector<int> Deng1;            // age of inoculations - dengue 1
  std::vector<int> Deng2;            // age of inoculations - dengue 2
  std::vector<int> Deng3;            // age of inoculations - dengue 3
  std::vector<int> Deng4;            // age of inoculations - dengue 4

  Population Individuals;

  int InitialPopulationSize;                        // size of array at initialization
  int PopulationSize;                               // actual size of indiv() array
  int OldPopulationSize;                            // previous years value

  std::vector<int> AgeDistribution;                 // number of individuals currently in each age class
  std::vector<int> InitialAgeDistribution;          // initial age distribution
  std::vector<input::DemographicClass> PopProp;     // human population statistics

  std::vector<std::vector<double>> SerProp;         // seroprevalence by class and serotype
  std::vector<std::vector<int>> SerDistr;           // serology distribution
  std::vector<std::vector<int>> InitSerDistr;       // initial serology distribution
  std::vector<double> CumHFDeaths;                  // number of deaths for ages 0-15

  std::vector<input::VirusSerotype> Virus;          // Virus parameters
  int MANADurat;                                    // duration of MANA in days
  int MAEADurat;                                    // duration of MAEA in days
  int HetImmunDurat;                                // duration of heterologous immun. - days

  int Day;                                          // Simulation day
  int Year;                                         // Simulation year

  std::vector<std::vector<int>> Incub;              // number of humans with incubating virus by class/virus
  std::vector<std::vector<int>> Infective;          // number of infective humans by class/virus
  std::vector<std::vector<int>> HomImm;             // human homologous immunity by class/virus
  std::vector<std::vector<int>> HetImm;             // human heterologous immunity by class/virus

  std::vector<int> TotDlyIncub;               // 
  std::vector<int> TotDlyInfective;           // Total daily values by virus
  std::vector<int> TotDlyHomImm;              // 
  std::vector<int> TotDlyHetImm;              // 
  std::vector<int> NewDlyInfective;           // New infective cases on each day

  std::vector<MaternalTransmission> MatAnti;  // Number of MANA and MAEA



  int EndYear;              // end of simulation
  int SimYear;              // number of simulation years run

  double HumHostDensity;    // humans per ha

  std::vector<double> TemperatureMax;
  std::vector<double> TemperatureMin;
  std::vector<double> TemperatureAvg;
  std::vector<double> Rain;
  std::vector<double> RelHumid;
  std::vector<double> SD;

  std::vector<double> EIPFactor;
  double EIPTempAdjust;

  std::vector<int> TotalBirths;           // total number of births during simulation
  std::vector<int> TotalDeaths;           // total number of deaths during simulation

  std::vector<double> NewMosqSusc;         // susceptible new mosquitoes and ...
  std::vector<double> NewMosqSuscCD;       // ... their gonotrophic development

  std::vector<double> OldMosqSusc;         // susceptible old mosquitoes and ...
  std::vector<double> OldMosqSuscCD;       // ... their gonotrophic development

  std::vector<std::vector<double>> NewMosqInfd;         // infected new mosquitoes (New Infd Mosq - 1 and gono. cycle)
  std::vector<std::vector<double>> NewMosqInfdCD;       // ... their gonotrophic development and ...
  std::vector<std::vector<double>> NewMosqInfdEIP;      // ... their extrinsic incubation period

  std::vector<std::vector<double>> OldMosqInfd;         // infected old mosquitoes (Old infd mosq - 2 gono. cycle)
  std::vector<std::vector<double>> OldMosqInfdCD;       // ... their gonotrophic development and ...
  std::vector<std::vector<double>> OldMosqInfdEIP;      // ... their extrinsic incubation period

  std::vector<std::vector<double>> MosqInfv;            // infective mosquitoes and ...
  std::vector<std::vector<double>> MosqInfvCD;          // ... their gonotrophic Development

  output::YearlyMosData YearlyMosData_;

  // Probability of human to mosquito transmission, based on titer
  double HumToMosLTiter;           // low titer
  double HumToMosLInf;             // probability at or below low titer
  double HumToMosHTiter;           // high titer
  double HumToMosHInf;             // probability at or above low titer

  double MosqToHumProb;            // probability of mosquito to human transmission

  // Adjustment of EIP based on titer
  double EipLTiter;                // low titer
  double EipLFactor;               // factor at or below low titer
  double EipHTiter;                // high titer
  double EipHFactor;               // factor at or above high titer

  // EIP calculated daily rates
  std::vector<double> EIPDevRate;

  double StochTransNum;            // mosquito count threshold, below which simulation uses stochasticity

  double PropOnHum;                // proportion of biters feeding on humans
  double FdAttempts;               // proportion of biters being interrupted
  double PropDifHost;              // proportion of interrupted biters feeding on different host
  double PropOutdoor;              // proportion of mosquitoes resting outdoors (space/residual sprays)

  double EnzKinDR;                 // 
  double EnzKinEA;                 // Enzyme kinetics coefficients
  double EnzKinEI;                 // 
  double EnzKinTI;                 // 

  double DBloodLWt;                // 
  double DBloodUWt;                // Double blood meal parameters
  double DBloodUProp;              // 
  double DBloodLProp;              // 

  double BitersTotal;                          // Total biters (susc/infd/infv)
  double BitersNew;                            // New susceptible biters
  double BitersOld;                            // Old susceptible biters
  std::vector<double> BitersInfv;              // Infective biters
  std::vector<double> BitesPerPerson;          // feeds per person
  double MosqTotal;                            // Total daily mosquitoes
  std::vector<double> MosqInfvTotal;           // Total infective mosquitoes by type
  int NewDlyHumInoc;                           // potential no. of new infected humans
  std::vector<double> BitersInfdNewDB;         // Number of new double bloods from yesterday
  std::vector<double> BitersInfdOldDB;         // Number of old double bloods from yesterday

  std::vector<double> CumDeaths;               // cumulative deaths by class, holds fractional deaths
  std::vector<double> CumBirths;               // cumulative births by class, holds fractional deaths
};

};
};

#endif
