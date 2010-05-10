#ifndef DSPORT_H
#define DSPORT_H

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
namespace dsport {

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
  void InitializeDiskLogs(void);

  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date stopDate );

  void denmain(void);

  static int CINT( double value );
  static int INT( double value );
  double RND( std::string callingMethod );
  double Factorial( int n );

  void CalculateEipFactors(void);

  void InitInfectives(void);
  double EIPEnzKin( double temp );
  
  void MosquitoLifeCycle(void);

  void NewMosquitoLifeCycle(void);
  double CalculateDoubleBloodMealProportion( double weight );
  void AdvanceSusceptibleNulliparous(void);
  void AdvanceSusceptibleParous(void);
  void AdvanceInfectedNulliparous(void);
  void AdvanceInfectedParous(void);
  void AdvanceInfectives(void);

  double GetSusceptibleOvipositingAverageWeight(void);

  void HumanToMosquitoTransmission(void);
  void InoculateMosquitoes( int serotype );
  void InfectParous( int numParousInfections, int iSerotype );
  void InfectNulliparous( int numNulliparousInfections, int iSerotype );

  void MosquitoToHumanTransmission(void);
  void InoculateHumans( int serotype );

  void SaveDailyOutput(void);

  output::DensimOutput * GetDensimOutput(void);

// Helpers
private:
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

  std::vector<double> EIPFactor;

  std::vector<double> NewMosqSusc;         // Susc. new mosquitoes
  std::vector<double> NewMosqSuscCD;       // Gonotrophic development

  std::vector<double> OldMosqSusc;         // Susc. old mosquitoes
  std::vector<double> OldMosqSuscCD;       // Gonotrophic development

  std::vector<std::vector<double>> NewMosqInfd;         // New Infd Mosq - 1 and gono. cycle
  std::vector<std::vector<double>> NewMosqInfdCD;       // Gonotrophic dev.  CD>1
  std::vector<std::vector<double>> NewMosqInfdEIP;      // Extrinsic incubation period

  std::vector<std::vector<double>> OldMosqInfd;         // Old infd mosq - 2 gono. cycle
  std::vector<std::vector<double>> OldMosqInfdCD;       // Gonotrophic dev.  CD>.58
  std::vector<std::vector<double>> OldMosqInfdEIP;      // Extrinsic incubation period

  std::vector<std::vector<double>> MosqInfv;            // Infective mosquitoes
  std::vector<std::vector<double>> MosqInfvCD;          // Gonotrophic Development

  double _minimumOvipositionTemperature;

  // probability human to mosquito infection
  double HumToMosLTiter;           // Low titer
  double HumToMosLInf;             //  prob.
  double HumToMosHTiter;           // High titer
  double HumToMosHInf;             //  prob.

  double MosqToHumProb;            // Prob of Mosq to human transmission

  // extrinsic incubation factor
  double EipLTiter;                // low titer log
  double EipLFactor;               // low titer factor
  double EipHTiter;                // high titer log
  double EipHFactor;               // high titer factor
  std::vector<double> EIPDevRate;  // calculated EIP for the day

  double StochTransNum;            // numbers lower than this are proc. stochastically

  double PropOnHum;                // Prop. of biters feeding on humans
  double FdAttempts;               // Prop. of biters being interrupted
  double PropDifHost;              // Prop. of inter. biters feeding on dif. host
  double PropOutdoor;              // Prop. mosq. resting outdoors (space sprays)

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
  double BitesPerPerson;                       // feeds per person
  double MosqTotal;                            // Total daily mosquitoes
  std::vector<double> MosqInfvTotal;           // Total infective mosquitoes by type
  int NewDlyHumInoc;                           // potential no. of new infected humans
  std::vector<double> BitersInfdNewDB;         // Number of new double bloods from yesterday
  std::vector<double> BitersInfdOldDB;         // Number of old double bloods from yesterday


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
  double _totalInfectiveMosquitoes;


  // verification members for densim refactor
  std::ofstream oldLog;
  void OutputNewMosqSusc(void);
  void OutputOldMosqSusc(void);
  void OutputNewMosqInfd(void);
  void OutputOldMosqInfd(void);
  void OutputMosqInfv(void);

  std::ofstream newLog;
  void OutputSusceptibleNulliparous(void);
  void OutputSusceptibleParous(void);
  void OutputInfectedNulliparous(void);
  void OutputInfectedParous(void);
  void OutputInfectives(void);
};

};

};

#endif
