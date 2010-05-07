#include "StdAfx.h"
#include "Mosquitoes.h"

using namespace sim::dsport;


AdultCohort::AdultCohort(void)
: Age(0),
  Number(0.0),
  Development(0.0),
  Weight(0.0),
  Ovipositing(false),
  DaysSinceOviposition(0),
  Infected(false),
  Serotype(0),
  Eip(0)
{}



AdultCohort::AdultCohort( int age, double number, double development, double weight )
: Age(age),
  Number(number),
  Development(development),
  Weight(weight),
  Ovipositing(false),
  DaysSinceOviposition(0),
  Infected(false),
  Serotype(0),
  Eip(0)
{}



// TODO, the oviposition related information should also be pulled from the cimsim cohort
AdultCohort::AdultCohort( sim::cs::AdultCohort & ac )
: Age(ac.Age),
  Number(ac.Number),
  Development(ac.Development),
  Weight(ac.Weight),
  Ovipositing(false),
  DaysSinceOviposition(0),
  Infected(false),
  Serotype(0),
  Eip(0)
{}



AdultCohort::~AdultCohort(void)
{}
