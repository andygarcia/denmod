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
#include "../input/Location.h"
#include "../cimsim/Cohorts.h"
#include "../output/MosData.h"
#include "../output/DensimOutput.h"
#include "../output/Log.h"

#define EMULATE_PDS_RAND true



namespace sim {
namespace ds {

class Location;
class HumanPopulation;



class dsport
{
// Constructors
public:
  dsport( const input::Location * location, sim::output::MosData * mosData, bool doDiskOutput = false );
  virtual ~dsport(void);

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
  void InfectParous( int numParousInfections, int iSerotype );
  void InfectNulliparous( int numNulliparousInfections, int iSerotype );

  void MosquitoToHumanTransmission(void);
  void InoculateHumans( int serotype );

  void SaveDailyOutput(void);

// Helper methods
public:
  static int CINT( double value );
  static int INT( double value );
  double RND(void);
  double Factorial( int n );

private:
  void InitializeDiskLogs(void);

  void CalculateEipFactors(void);
  double CalculateDoubleBloodMealProportion( double weight );

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

  HumanPopulation * _humanPopulation;
  double HumHostDensity;

  std::vector<VirusDesc> Virus;       // Virus parameters

  int MANADurat;                      // Duration of MANA in days
  int MAEADurat;                      // Duration of MAEA in days
  int HetImmunDurat;                  // Duration of heterologous immun. - days

  double _averageAirTemperature;
  output::DailyMosData _dailyMosData;
  output::DailyMosData _yesterdayMosData;

  std::vector<double> _eipDevelopmentRate;
  std::vector<double> _eipAdjustmentFactor;

  double _minimumOvipositionTemperature;

  // probability human to mosquito infection
  double HumToMosLTiter;           // Low titer
  double HumToMosLInf;             //  prob.
  double HumToMosHTiter;           // High titer
  double HumToMosHInf;             //  prob.

  double MosqToHumProb;            // Prob of Mosq to human transmission


  // extrinsic incubation period adjustment factor parameters
  double EipLTiter;
  double EipLFactor;
  double EipHTiter;
  double EipHFactor;

  double StochTransNum;            // numbers lower than this are proc. stochastically

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

  int _newHumanInoculations;       // daily human inoculations resulting from infective bites


  // random number generator simulator to match PDS 7.1 libraries
  PdsRng _pdsRng;


  // susceptible cohorts
  MosquitoCollection _susceptibleNulliparous;
  double _susceptibleNulliparousBites;
  MosquitoReferenceCollection _susceptibleNulliparousBiters;
  MosquitoReferenceCollection _susceptibleNulliparousDoubleBiters;

  MosquitoCollection _susceptibleParous;
  double _susceptibleParousBites;
  MosquitoReferenceCollection _susceptibleParousBiters;
  MosquitoReferenceCollection _susceptibleParousDoubleBiters;

  MosquitoCollection _susceptibleOvipositing;


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

  // infective mosquito count by serotype and total
  std::vector<double> _infectiveMosquitoesBySerotype;
  double _totalInfectiveMosquitoes;

};

};

};

#endif
