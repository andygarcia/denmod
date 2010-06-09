#include "StdAfx.h"
#include "Mosquitoes.h"

using namespace sim::ds;


AdultCohort::AdultCohort(void)
: Age(0),
  Number(0.0),
  Development(0.0),
  Weight(0.0),
  Ovipositing(false),
  SeekingBloodMeal(false),
  SeekingDoubleBloodMeal(false),
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
  SeekingBloodMeal(false),
  SeekingDoubleBloodMeal(false),
  Infected(false),
  Serotype(0),
  Eip(0)
{}



AdultCohort::AdultCohort( sim::cs::AdultCohort & ac )
: Age(ac.Age),
  Number(ac.Number),
  Development(ac.Development),
  Weight(ac.Weight),
  Ovipositing(false),
  SeekingBloodMeal(false),
  SeekingDoubleBloodMeal(false),
  Infected(false),
  Serotype(0),
  Eip(0)
{}



AdultCohort::~AdultCohort(void)
{}



bool
AdultCohort::operator==( const AdultCohort & rhs )
{
  if( this == &rhs ) {
    // simple case where comparing same object
    return true;
  }

  if( this->Age == rhs.Age && 
      this->Number == rhs.Number &&
      this->Development == rhs.Development &&
      this->Weight == rhs.Weight &&
      this->Ovipositing == rhs.Ovipositing &&
      this->SeekingBloodMeal == rhs.SeekingBloodMeal &&
      this->SeekingDoubleBloodMeal == rhs.SeekingDoubleBloodMeal &&
      this->Infected == rhs.Infected &&
      this->Serotype == rhs.Serotype &&
      this->Eip == rhs.Eip )
  {
    // all members are equal, consider objects equal
    return true;
  }

  return false;
}
