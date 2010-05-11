#ifndef SIM_DS_CLASSES_H
#define SIM_DS_CLASSES_H

#include "stdafx.h"


namespace sim {
namespace ds {



class SequentialInfectionValues
{
public:
  double F1T2;                // first 1 then 2 - number of individuals
  double F1T3;
  double F1T4;
  double F2T1;
  double F2T3;
  double F2T4;
  double F3T1;
  double F3T2;
  double F3T4;
  double F4T1;
  double F4T2;
  double F4T3;
  double FMT1;
  double FMT2;
  double FMT3;
  double FMT4;
};



class VirusDesc           // virus parameters
{
public:
  double Viremia;          // number of mosquito infectious doses
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
  double CalcDeathsArraySize;
  double CalcBirthsArraySize;
  double InitInfectivesArraySize;
  double DMealProp;
  double EggersNew;
  double BitersNew;
  double EggersOld;
  double BitersOld;
  double EIPTranNew[4+1];
  double BitersInfdNewDB[4+1];
  double EIPTranOld[4+1];
  double BitersInfdOldDB[4+1];
  double BitersInfd[4+1];
  double EggersInfv[4+1];
  double BitersInfv[4+1];
  double BitersTotal;
  double MosqTotal;
  double MosqInfvTotal[4+1];
  double BitesPerPerson;
  double MosqInocEstimate[4+1];
  double NewDlyMosqInoc[4+1];
  double NewInfd[4+1];
  double OldInfd[4+1];
  double HumInocEstimate[4+1];
  double NewDlyHumInoc[4+1];
};



class DiskSpooler
{
public:
  double Incubate1;                        // Number of humans incubating
  double Incubate2;                        // Number of humans incubating
  double Incubate3;                        // Number of humans incubating
  double Incubate4;                        // Number of humans incubating
  double Viremic1;                         // Number of humans infective
  double Viremic2;                         // Number of humans infective
  double Viremic3;                         // Number of humans infective
  double Viremic4;                         // Number of humans infective
  double MosqTotal;                        // Total daily mosquitoes
  double MosqInfvTotal[4+1];               // Total infective mosquitoes
  int InfvBites;                          // New potential inoculations
  double EIPDevRate[4+1];                  // Extrinsic incubation period rate - daily
  double NumHumans;                        // Number of humans
  double SerPos[23+1][4+1];                // Percent of indiv. in age class that are seropositive
  double NewHumCases[4+1];                 // Number of new human cases/day/serotype
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
