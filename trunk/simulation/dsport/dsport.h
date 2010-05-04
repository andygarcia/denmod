#ifndef DSPORT_H
#define DSPORT_H

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "DensimClasses.h"
#include "PdsRng.h"
#include "../input/Location.h"
#include "../cimsim/Cohorts.h"
#include "../output/MosData.h"
#include "../output/DensimOutput.h"
#include "../output/Log.h"

#define EMULATE_PDS_RAND true

using sim::cs::PreOviAdultCohortCollection;
using sim::cs::OviAdultCohortCollection;



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

  static int CINT( float value );
  static int INT( float value );
  float RND( std::string callingMethod );
  float Factorial( int n );

  void CalculateEipFactors(void);

  void InitInfectives(void);
  float EIPEnzKin( float temp );
  
  void MosquitoLifeCycle(void);
  void NewMosquitoLifeCycle(void);

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

  const float GasCoef;

  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;
  boost::gregorian::date _currentDate;

  HumanPopulation * _humanPopulation;
  float HumHostDensity;

  std::vector<VirusDesc> Virus;       // Virus parameters

  int MANADurat;                      // Duration of MANA in days
  int MAEADurat;                      // Duration of MAEA in days
  int HetImmunDurat;                  // Duration of heterologous immun. - days

  float _averageAirTemperature;
  output::DailyMosData _dailyMosData;
  output::DailyMosData _yesterdayMosData;

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
  float BitesPerPerson;                             // feeds per person
  float MosqTotal;                            // Total daily mosquitoes
  std::vector<float> MosqInfvTotal;           // Total infective mosquitoes by type
  int NewDlyHumInoc;                          // potential no. of new infected humans
  std::vector<float> BitersInfdNewDB;         // Number of new double bloods from yesterday
  std::vector<float> BitersInfdOldDB;         // Number of old double bloods from yesterday

  PdsRng _pdsRng;

  float _minimumOvipositionTemperature;       // minimum air temperature allowing oviposition

  // new cohort code
  PreOviAdultCohortCollection _nulliparousAdults;
  OviAdultCohortCollection _parousAdults;

  PreOviAdultCohortCollection _ovipositingNulliparousAdults;
  OviAdultCohortCollection _ovipositingParousAdults;
};

};

};

#endif
