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
  void AdvanceSusceptibleNulliparous(void);
  void AdvanceSusceptibleParous(void);

  void HumanToMosquitoTransmission(void);
  void InoculateMosquitoes( int serotype );

  void MosquitoToHumanTransmission(void);
  void InoculateHumans( int serotype );
  
  void SaveDailyOutput(void);

  output::DensimOutput * GetDensimOutput(void);

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

  // biology
  double _minimumOvipositionTemperature;

  // MosquitoCollection is a primary collection of mosquitoes while

  // susceptible nulliparous cohorts
  MosquitoCollection _susceptibleNulliparous;
  double _susceptibleNulliparousBites;
  MosquitoReferenceCollection _susceptibleNulliparousFirstBiters
  MosquitoReferenceCollection _susceptibleNulliparousDoubleBiters;

  // susceptible parous cohorts
  MosquitoCollection _susceptibleParous;
  double _susceptibleParousBites;
  MosquitoReferenceCollection _susceptibleParousFirstBiters
  MosquitoReferenceCollection _susceptibleParousDoubleBiters;

  // susceptible nulliparous and parous ovipositing cohorts
  MosquitoCollection _susceptibleOvipositing;
  double GetSusceptibleOvipositingAverageWeight(void);

  // infected cohorts
  std::vector<MosquitoCollection> _infectedNulliparous;
  std::vector<MosquitoCollection> _infectedParous;

  // infectious cohorts
  std::vector<MosquitoCollection> _infectious;

  // mosquito collection methods
  double GetMosquitoCollectionCount( MosquitoCollection & collection );

  double GetNulliparousBiters( MosquitoCollection & collection );
  double GetParousBiters( MosquitoCollection & collection );

  // double blood meals
  double CalculateDoubleBloodMealProportion( double weight );

  double _bitesPerPerson;






  // verification members for densim refactor
  void OutputNewMosq(void);
  std::ofstream NewMosqLog;
  void OutputOldMosq(void);
  std::ofstream OldMosqLog;

  void OutputSusceptibleNulliparous(void);
  void OutputSusceptibleParous(void);
  std::ofstream _susceptibleNulliparousLog;
  std::ofstream _susceptibleParousLog;
};

};

};

#endif
