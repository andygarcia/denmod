#ifndef SIMULATION_DENSIMCLASSES_H
#define SIMULATION_DENSIMCLASSES_H

#include "stdafx.h"


namespace sim {
namespace dsport {



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



class VirusDesc           // virus parameters
{
public:
  float Viremia;          // number of mosquito infectious doses
  int Incub;              // incubation period in days
  int Durat;              // duration of viremia in days
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
  float CalcDeathsArraySize;
  float CalcBirthsArraySize;
  float InitInfectivesArraySize;
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
  float BitesPerPerson;
  float MosqInocEstimate[4+1];
  float NewDlyMosqInoc[4+1];
  float NewInfd[4+1];
  float OldInfd[4+1];
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



enum Serotype
{
  D1 = 1,
  D2,
  D3,
  D4,
  Maternal
};

};
};

#endif
