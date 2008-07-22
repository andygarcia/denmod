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
  void denmain(void);

  void MainInitialization(void);
  void InitializePopulation(void);
  void InitializeSeroprevalence(void);
  void CalculateEipTiterAdjustment(void);

  void CalculateDeaths(void);
  void CalculateBirths(void);
  void AgePopulation(void);

  void IntroduceInfection(void);
  void PurgeMaternal(void);

  void CalculateEip(void);

  void AdvanceMosquitoes(void);

  void HumanToMosquitoTransmission(void);
  void InnoculateMosquitoes( int iType );

  void MosquitoToHumanTransmission(void);
  void InnoculateHumans( int iType );

  void RankPop(void);
  void SeroRank( int iElement, int iRank );
  void CalcSeqInfs( int iVirType, int iPerAge, int iD1Inoc, int iD2Inoc, int iD3Inoc, int iD4Inoc );
  void AgeAtDeath( int iPerAge );
  void PurgeHFDeaths(void);
  void SpoolToDisk(void);

private:
  void ComparePopulation(void);
  void ComparePopulationAndSerotypes(void);
  int DeterminePosition( int IAge );
  static int CINT( double value );
  static int INT( double value );
  double RND(void);
  double Factorial( int n );
  double EIPEnzKin( double temp );
  void ReadWeather( int year );
  void ReadMos( int year );

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

  // replace the above arrays with this one
  Population Individuals;

  std::vector<int> AgeDistribution;       // number of individuals currently in each age class
  std::vector<int> InitialAgeDistribution;   // initial age distribution

  std::vector<std::vector<int>> SerDistr;         // Num. sero-pos. individuals
  std::vector<std::vector<int>> InitSerDistr;     // Init. serolog. distribution
  std::vector<double> CumHFDeaths;    // number of deaths for ages 0-15

  std::vector<std::vector<double>> SerProp;          // Ref. - Seroprev. statistics
                                                    // Class by prop. with den1-den4

  std::vector<input::DemographicClass> PopProp;     // Reference - Human pop. statistics
  int PopulationSize;                      // Actual size of indiv() array

  std::vector<input::VirusSerotype> Virus;       // Virus parameters
  int MANADurat;                      // Duration of MANA in days
  int MAEADurat;                      // Duration of MAEA in days
  int HetImmunDurat;                  // Duration of heterologous immun. - days

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

  int InitPopulationSize;        // size of array at initialization
  int OldPopulationSize;         // previous years value

  int EndYear;              // end of simulation
  int SimYear;              // number of simulation years run

  double HumHostDensity;    // humans per ha

  std::vector<double> TemperatureMax;
  std::vector<double> TemperatureMin;
  std::vector<double> TemperatureAvg;
  std::vector<double> Rain;
  std::vector<double> RelHumid;
  std::vector<double> SD;

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
  std::vector<double> EIPFactor;

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

  // DENDYNAMIC.INC
  std::vector<double> CumulativeDeaths;               // cumulative deaths by class - holds fractional deaths
  std::vector<double> CumulativeBirths;               // cumulative births by class - holds fractional births 
};

};
};

#endif
