#ifndef DS_SIMCLASSES_H
#define DS_SIMCLASSES_H

#include <string>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>



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



class AgeClass
{
public:
  int Rank;             // class - a value of 1 to 18
  int FDay;             // start age of class - in days
  int LDay;             // end age of class - in days - max. age = 30,000 days
};



class MaternalTransmission
{
public:
  int MANA;               // maternally acquired neutralizing antibody
  int MAEA;               // maternally acquired enhancing antibody
};

};
};

#endif
