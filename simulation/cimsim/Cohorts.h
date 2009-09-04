#ifndef CS_SIM_COHORTS_H
#define CS_SIM_COHORTS_H

#include <list>
#include <map>



namespace sim {
namespace cs {

class EggCohort
{
public:
  EggCohort(void)
  : Age(0),
    Number(0.0),
    Development(0.0)
  {}

  EggCohort( int age, double number, double development )
  : Age(age),
    Number(number),
    Development(development)
  {}

public:
  int Age;
  double Number;
  double Development;
};

typedef std::list<sim::cs::EggCohort> EggCohortCollection;
typedef EggCohortCollection::iterator EggIterator;



class EggBand
{
public:
  EggBand(void)
  : MatureEggs(0),
    EggCohorts(EggCohortCollection())
  {}

public:
  double MatureEggs;
  EggCohortCollection EggCohorts;
};

typedef std::map<int, sim::cs::EggBand> EggBandCollection;
typedef EggBandCollection::iterator EggBandIterator;



class LarvaeCohort
{
public:
  LarvaeCohort(void)
  : Age(0),
    Number(0),
    Development(0),
    Weight(0),
    WeightChange(0),
    FatBody(0),
    PreFastFatBody(0),
    SurvivalFood(0)
  {}

  LarvaeCohort( int age, double number, double development, double weight )
  : Age(age),
    Number(number),
    Development(development),
    Weight(weight),
    WeightChange(0),
    FatBody(0),
    PreFastFatBody(0),
    SurvivalFood(0)
  {}

public:
  int Age;
  double Number;
  double Development;

  double Weight;
  double WeightChange;

  double FatBody;
  double PreFastFatBody;

  double SurvivalFood;
};

typedef std::list<sim::cs::LarvaeCohort> LarvaeCohortCollection;
typedef LarvaeCohortCollection::iterator LarvaeIterator;



class PupaeCohort
{
public:
  PupaeCohort(void)
  : Age(0),
    Number(0.0),
    Development(0.0),
    Weight(0.0)
  {}

  PupaeCohort( int age, double number, double development, double weight )
  : Age(age),
    Number(number),
    Development(development),
    Weight(weight)
  {}

public:
  int Age;
  double Number;
  double Development;
  double Weight;
};

typedef std::list<sim::cs::PupaeCohort> PupaeCohortCollection;
typedef PupaeCohortCollection::iterator PupaeIterator;



class AdultCohort
{
public:
  AdultCohort(void)
  : Age(0),
    Number(0.0),
    Development(0.0),
    Weight(0.0),
    Ovipositing(false),
    OvipositionAge(0)
  {}

  AdultCohort( int age, double number, double development, double weight )
  : Age(age),
    Number(number),
    Development(development),
    Weight(weight),
    Ovipositing(false),
    OvipositionAge(0)
  {}

  ~AdultCohort(void) {}

public:
  int Age;
  double Number;
  double Development;
  double Weight;

  bool Ovipositing;
  int OvipositionAge;
};


class PreOviAdultCohort : public AdultCohort
{
public:
  PreOviAdultCohort(void)
  : AdultCohort()
  {}

  PreOviAdultCohort( int age, double number, double development, double weight )
  : AdultCohort( age, number, development, weight )
  {}
};



class OviAdultCohort : public AdultCohort
{
public:
  OviAdultCohort(void)
  : AdultCohort()
  {}

  OviAdultCohort( int age, double number, double development, double weight )
  : AdultCohort( age, number, development, weight )
  {}
};

typedef std::list<sim::cs::AdultCohort> AdultCohortCollection;

typedef std::list<sim::cs::PreOviAdultCohort> PreOviAdultCohortCollection;
typedef PreOviAdultCohortCollection::iterator PreOviAdultIterator;

typedef std::list<sim::cs::OviAdultCohort> OviAdultCohortCollection;
typedef OviAdultCohortCollection::iterator OviAdultIterator;

};
};

#endif
