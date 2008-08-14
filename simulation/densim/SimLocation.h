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
  output::DensimOutput * GetSimOutput(void);

  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date stopDate );

  void denmain(void);

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
  void CalcSeqInfs( int iVirType, int & iPerAge, int iD1Inoc, int iD2Inoc, int iD3Inoc, int iD4Inoc );

  void NewRankPop(void);
  void NewSeroRank( Individual & individual, int ageClass );
  void NewCalcSeqInfs( Individual & individual, int serotype );

  void AgeAtDeath( int iPerAge );
  void PurgeHFDeaths(void);
  void SpoolToDisk(void);

private:
  int DayAgeToAgeClass( int age );
  int DayAgeToYearAge( int age );
  void ComparePopulation(void);
  void ComparePopulationAndSerotypes(void);
  int DeterminePosition( int IAge );
  static int CINT( double value );
  static int INT( double value );
  double RND(void);
  double Factorial( int n );
  double EIPEnzKin( double temp );

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

  int Day;                                        // Simulation day
  int Year;                                       // Simulation year
  int SimYear;                                    // number of simulation years run

  std::vector<int> Indiv;                         // Age of each individual and age of infection
  std::vector<int> Deng1;                         // age of inoculations - dengue 1
  std::vector<int> Deng2;                         // age of inoculations - dengue 2
  std::vector<int> Deng3;                         // age of inoculations - dengue 3
  std::vector<int> Deng4;                         // age of inoculations - dengue 4

  AgeClass AgeClasses[18+1];                      // population classes defined

  int InitialPopulationSize;                      // initial size of population, TODO - default set at 10000
  int PopulationSize;                             // current size of population
  double HumHostDensity;                          // humans per hectare
  Population Individuals;

  std::vector<input::DemographicClass> PopProp;   // population statistics
  std::vector<int> InitialAgeDistribution;        // initial number of individuals by class
  std::vector<int> AgeDistribution;               // number of individuals by class

  std::vector<std::vector<double>> SerProp;       // proportion of population sero positive, by serotype and class
  std::vector<std::vector<int>> InitSerDistr;     // initial number of sero positive individuals, by serotype and class
  std::vector<std::vector<int>> SeroDistribution; // number of sero positive individuals, by serotype and class
  std::vector<double> CumHFDeaths;                // number of deaths for ages 0-15

  std::vector<input::VirusSerotype> Virus;        // virus parameters

  int MANADurat;                                  // duration of MANA in days
  int MAEADurat;                                  // duration of MAEA in days
  int HetImmunDurat;                              // duration of heterologous immunity in days

  SequentialInfectionValues DlySeqInfVals;        // daily infection

  std::vector<std::vector<int>> Incub;            // number of humans with incubating virus by class/virus
  std::vector<std::vector<int>> Infective;        // number of infective humans by class/virus
  std::vector<std::vector<int>> HomImm;           // human homologous immunity by class/virus
  std::vector<std::vector<int>> HetImm;           // human heterologous immunity by class/virus

  std::vector<int> TotDlyIncub;                   // 
  std::vector<int> TotDlyInfective;               // Total daily values by virus
  std::vector<int> TotDlyHomImm;                  // 
  std::vector<int> TotDlyHetImm;                  // 
  std::vector<int> NewDlyInfective;               // new infective cases on each day

  std::vector<MaternalTransmission> MatAnti;      // number of MANA and MAEA

  std::vector<int> TotalBirths;                         // total number of births during simulation
  std::vector<int> TotalDeaths;                         // total number of deaths during simulation

  std::vector<double> NewMosqSusc;                      // susceptible new mosquitoes and ...
  std::vector<double> NewMosqSuscCD;                    // ... their gonotrophic development

  std::vector<double> OldMosqSusc;                      // susceptible old mosquitoes and ...
  std::vector<double> OldMosqSuscCD;                    // ... their gonotrophic development

  std::vector<std::vector<double>> NewMosqInfd;         // infected new mosquitoes (new Infd Mosq - 1 and gono. cycle)
  std::vector<std::vector<double>> NewMosqInfdCD;       // ... their gonotrophic development and ...
  std::vector<std::vector<double>> NewMosqInfdEIP;      // ... their extrinsic incubation period

  std::vector<std::vector<double>> OldMosqInfd;         // infected old mosquitoes (old infd mosq - 2 gono. cycle)
  std::vector<std::vector<double>> OldMosqInfdCD;       // ... their gonotrophic development and ...
  std::vector<std::vector<double>> OldMosqInfdEIP;      // ... their extrinsic incubation period

  std::vector<std::vector<double>> MosqInfv;            // infective mosquitoes and ...
  std::vector<std::vector<double>> MosqInfvCD;          // ... their gonotrophic development

  output::DailyMosData DailyMosData;                    // today's mos data from cimsim

  double HumToMosLTiter;                                // low titer point
  double HumToMosLInf;                                  // probability of human to mosquito transmission at or below low titer
  double HumToMosHTiter;                                // high titer
  double HumToMosHInf;                                  // probability of human to mosquito transmission at or above high titer

  double MosqToHumProb;                                 // probability of mosquito to human transmission

  double EipLTiter;                                     // low titer
  double EipLFactor;                                    // EIP adjustment factor at or below low titer
  double EipHTiter;                                     // high titer
  double EipHFactor;                                    // EIP adjustment factor at or above high titer
  std::vector<double> EIPFactor;                        // EIP adjustment factors by serotype
  double AverageAirTemperature;                         // daily average air temperature
  std::vector<double> EIPDevRate;                       // EIP daily development rate

  double StochTransNum;            // mosquito count threshold, below which simulation uses stochasticity

  double PropOnHum;                // proportion of biters feeding on humans
  double FdAttempts;               // proportion of biters being interrupted
  double PropDifHost;              // proportion of interrupted biters feeding on different host

  double EnzKinDR;                 // 
  double EnzKinEA;                 // Enzyme kinetics coefficients
  double EnzKinEI;                 // 
  double EnzKinTI;                 // 

  double DBloodLWt;                // 
  double DBloodUWt;                // Double blood meal parameters
  double DBloodUProp;              // 
  double DBloodLProp;              // 

  double BitersTotal;                          // total biters (susc/infd/infv)
  double BitersNew;                            // new susceptible biters
  double BitersOld;                            // old susceptible biters
  std::vector<double> BitersInfv;              // infective biters
  std::vector<double> BitesPerPerson;          // feeds per person
  double MosqTotal;                            // total daily mosquitoes
  std::vector<double> MosqInfvTotal;           // total infective mosquitoes by type
  int NewDlyHumInoc;                           // potential no. of new infected humans
  std::vector<double> BitersInfdNewDB;         // number of new double bloods from yesterday
  std::vector<double> BitersInfdOldDB;         // number of old double bloods from yesterday

  std::vector<double> CumulativeDeaths;        // cumulative deaths by class - holds fractional deaths
  std::vector<double> CumulativeBirths;        // cumulative births by class - holds fractional births 
};

};
};

#endif
