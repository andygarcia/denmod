#ifndef SIM_DSPORT_MOSQUITOES_H
#define SIM_DSPORT_MOSQUITOES_H

#include <list>
#include <map>
#include "../cimsim/Cohorts.h"



namespace sim {
namespace dsport {

class AdultCohort
{
public:
  AdultCohort(void);
  AdultCohort( int age, double number, double development, double weight );
  AdultCohort( sim::cs::AdultCohort & ac );
  ~AdultCohort(void);

public:
  bool AdultCohort::operator==( const AdultCohort & rhs );

public:
  int Age;
  double Number;
  double Development;
  double Weight;

  bool SeekingBloodMeal;
  bool SeekingDoubleBloodMeal;

  bool Ovipositing;
  int DaysSinceOviposition;

  bool Infected;
  int Serotype;
  double Eip;
};

typedef std::list<AdultCohort> MosquitoCollection;
typedef std::list<AdultCohort*> MosquitoReferenceCollection;
typedef MosquitoCollection::iterator MosquitoIterator;
typedef MosquitoReferenceCollection::iterator MosquitoReferenceIterator;

};
};

#endif
