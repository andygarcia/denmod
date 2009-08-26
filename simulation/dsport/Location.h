#ifndef DSPORT_LOCATION_H
#define DSPORT_LOCATION_H

#include "dsport.h"



namespace ds {

namespace port {

class Location
{
public:
  Location(void);
  virtual ~Location(void);

public:
  // DEFAULT.FIL (PDS)
  std::vector<VirusIntroductionProfile> VirusIntro;
  std::vector<SequentialInfectionParms> SeqInfPrms;
  std::vector<MAEAInfectionParms> MAEAInfPrms;

  // DEM file
  std::vector<HumanDemo> PopProp;
  float HumHostDensity;
  float ClusterSize;

  // VIR file
  std::vector<VirusDesc> Virus;
  float HumToMosLTiter;
  float HumToMosLInf;
  float HumToMosHTiter;
  float HumToMosHInf;
  float EipLTiter;
  float EipLFactor;
  float EipHTiter;
  float EipHFactor;
  float StochTransNum;
  float MosqToHumProb;
  float EnzKinDR;
  float EnzKinEA;
  float EnzKinEI;
  float EnzKinTI;

  // SER file
  std::vector<std::vector<float>> SerProp;
  int MANADurat;
  int MAEADurat;
  int HetImmunDurat;

  // BIO/ENT file
  float PropOnHum;
  float FdAttempts;
  float PropDifHost;
  float PropOutdoor;
  float DBloodLWt;
  float DBloodUWt;
  float DBloodUProp;
  float DBloodLProp;

  // MOS/ENT files
  std::map<int, std::vector<CimSimOutDescription>> CimsimDataByYear;

  // POP file
  std::vector<float> NewMosqSusc;
  std::vector<float> NewMosqSuscCD;

  std::vector<float> OldMosqSusc;
  std::vector<float> OldMosqSuscCD;

  // Weather
  csinput::Weather * Weather_;

  // HUMSINOQ.txt
  // by day and then by serotype
  std::vector<std::map<int,std::vector<int>>> HumanInoculationIndices;
  std::vector<std::vector<int>> StartingPopulation;
};

};

};

#endif
