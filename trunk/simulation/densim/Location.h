#ifndef SIM_DS_LOCATION_H
#define SIM_DS_LOCATION_H

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Classes.h"
#include "PdsRng.h"
#include "Mosquitoes.h"
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include "../input/Location.h"
#include "../cimsim/Cohorts.h"
#include "../output/MosData.h"
#include "../output/DensimOutput.h"
#include "../output/Log.h"



namespace sim {
namespace ds {

int CINT( double value );
int INT( double value );

// Forward declarations
class HumanPopulation;

class Location
{
// Constructors
public:
  Location( const input::Location * location, sim::output::MosData * mosData, bool doDiskOutput = false );
  virtual ~Location(void);

// Methods
public:
  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date stopDate );
  void RunSimulation(void);
  output::DensimOutput * GetDensimOutput(void);

// Simulation methods
private:
  void IntroduceInfectives(void);
  double EIPEnzKin( double temp );
  
  void MosquitoLifeCycle(void);
  void AdvanceSusceptibleNulliparous(void);
  void AdvanceSusceptibleParous(void);
  void AdvanceInfectedNulliparous(void);
  void AdvanceInfectedParous(void);
  void AdvanceInfectives(void);

  void HumanToMosquitoTransmission(void);
  void InoculateMosquitoes( int serotype );
  void InfectMosquitoes( int serotype, double numInfections, MosquitoCollection & bitingCollection, std::vector<MosquitoCollection> & infectedCollection );

  void MosquitoToHumanTransmission(void);
  int InoculateHumans( int serotype );

  void SaveDailyOutput(void);

// Helper methods
public:
  double Factorial( int n );

private:
  void InitializeDiskLogs(void);

  void CalculateEipFactors(void);
  double CalculateDoubleBloodMealProportion( double weight );

  void SetNulliparousBloodMealStatus( AdultCohort & cohort );
  void SetParousBloodMealStatus( AdultCohort & cohort );

  double GetSusceptibleOvipositingAverageWeight(void);
  double GetTotalMosquitoes( MosquitoCollection & collection );
  double GetTotalMosquitoes( std::vector<MosquitoCollection> & collections );
  AdultCohort CombineCohorts( MosquitoCollection & collection, int age, double development );

// Members
public:
  const input::Location * _location;
  output::MosData * _mosData;
  output::DensimOutput * _densimOutput;

  bool _doDiskOutput;
  output::Log * _locationLog;

  const double GasCoef;

  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;
  boost::gregorian::date _currentDate;

  int _year;
  int _day;

  // human population and demographics
  HumanPopulation * _humanPopulation;
  double HumHostDensity;

  // daily human inoculations resulting from infective bites
  int _humanInoculations;
  std::vector<int> _humanInoculationsBySerotype;

  // virus parameters
  std::vector<VirusDesc> Virus;

  // weather and mosquito data from cimsim
  double _minimumOvipositionTemperature;
  double _averageAirTemperature;
  output::DailyMosData _dailyMosData;
  output::DailyMosData _yesterdayMosData;

  // eip rate and factors
  std::vector<double> _eipDevelopmentRate;
  std::vector<double> _eipAdjustmentFactor;

  // probability human to mosquito infection
  double HumToMosLTiter;
  double HumToMosLInf;
  double HumToMosHTiter;
  double HumToMosHInf;

  // probability mosquito to human infection
  double MosqToHumProb;

  // extrinsic incubation period adjustment factor parameters
  double EipLTiter;
  double EipLFactor;
  double EipHTiter;
  double EipHFactor;

  // inoculation estimates lower than this are processed stochastically
  double StochTransNum;

  // biting parameters
  double PropOnHum;
  double FdAttempts;
  double PropDifHost;

  // enzyme kinetics coefficients
  double EnzKinDR;
  double EnzKinEA;
  double EnzKinEI;
  double EnzKinTI;

  // double blood meal parameters
  double DBloodLWt;
  double DBloodUWt;
  double DBloodUProp;
  double DBloodLProp;

  // random number generator simulator to match PDS 7.1 libraries
  PdsRng _pdsRng;
  boost::variate_generator<boost::mt19937, boost::uniform_01<>> _rng;


  // susceptible cohorts
  MosquitoCollection _susceptibleNulliparous;
  MosquitoCollection _susceptibleNulliparousOvipositing;
  double _susceptibleNulliparousBites;
  MosquitoReferenceCollection _susceptibleNulliparousBiters;
  MosquitoReferenceCollection _susceptibleNulliparousDoubleBiters;

  MosquitoCollection _susceptibleParous;
  double _susceptibleParousBites;
  MosquitoReferenceCollection _susceptibleParousBiters;
  MosquitoReferenceCollection _susceptibleParousDoubleBiters;



  // infected cohorts
  double _bitesPerPerson;
  std::vector<MosquitoCollection> _infectedNulliparous;
  std::vector<MosquitoCollection> _infectedParous;
  std::vector<double> _infectedBites;
  std::vector<double> _infectedNulliparousBites;
  std::vector<double> _infectedNulliparousDoubleBites;
  std::vector<double> _infectedParousBites;
  std::vector<double> _infectedParousDoubleBites;

  std::vector<MosquitoCollection> _newlyInfectiveNulliparous;
  std::vector<MosquitoCollection> _newlyInfectiveParous;


  // infective cohorts
  std::vector<MosquitoCollection> _infectives;
  std::vector<MosquitoCollection> _infectiveOvipositing;
  std::vector<double> _infectiveBites;
  std::vector<MosquitoCollection> _infectiveBiters;
  std::vector<MosquitoCollection> _infectiveDoubleBiters;

  
  // bite and mosquito totals
  double _totalBites;
  double _totalMosquitoes;

  // total mosquitoes by status
  double _totalSusceptibleNulliparous;
  double _totalSusceptibleParous;
  double _totalInfectedNulliparous;
  double _totalInfectedParous;

  // infective mosquito count by serotype and total
  std::vector<double> _infectiveMosquitoesBySerotype;
  double _totalInfectiveMosquitoes;

};

};

};

#endif
