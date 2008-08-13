#include "StdAfx.h"
#include "Population.h"

using namespace sim::ds;



Individual::Individual( int age )
: Age(age)
{
  for( int i = 0; i <=4; ++i ) {
    Dengue[i] = 0;
  }
}



Individual::Individual( const Individual & individual )
{
  this->Age = individual.Age;
  for( int i = 0; i <=4; ++i ) {
    this->Dengue[i] = individual.Dengue[i];
  }
}



Individual::~Individual(void)
{}



bool
Individual::IsSeropositive( int serotype )
{
  // individual is seropositive if they have initialized or maternally acquired immunity
  // as well as having been innoculated, i.e. a non zero rank
  return Dengue[serotype] != 0;
}



void
Individual::InitializeImmunity( int serotype )
{
  Dengue[serotype] = -2;
}



bool
Individual::HasInitializedImmunity( int serotype )
{
  return Dengue[serotype] == -2;
}



void
Individual::InitializeMaternallyAcquiredImmunity( int serotype )
{
  Dengue[serotype] = -1;
}



bool 
Individual::HasMaternallyAcquiredImmunity( int serotype )
{
  return Dengue[serotype] == -1;
}



void
Individual::PurgeMaternalImmunity(void)
{
  for( int i = 1; i <=4; ++i ) {
    if( Dengue[i] == -1 ) {
      Dengue[i] = 0;
    }
  }
}



void
Individual::Infect( int serotype, int age )
{
  Dengue[serotype] = age;
}



bool
Individual::HasPreviousInfection( int serotype )
{
  return Dengue[serotype] > 0;
}



int
Individual::GetAgeOfInfection( int serotype )
{
  if( Dengue[serotype] > 0 ) {
    return Dengue[serotype];
  }
  else {
    throw;
  }
}



bool
Individual::HasHeterologousImmunity( int serotype, int duration )
{
  // check for previous infection from other serotypes
  for( int i = 1; i <=4; ++i ) {
    if( i == serotype ) {
      continue;
    }
    
    if( Dengue[i] > 0 ) {
      if( (Age - Dengue[i]) < duration ) {
        return true;
      }
    }
  }

  return false;
}



bool
Individual::HasHomologousImmunity( int serotype )
{
  return Dengue[serotype] > 0;
}



void
Individual::DoDeath(void)
{
  // record age at death
  Dengue[0] = Age;
  // flag as dead
  Age = -999;
}


int
Individual::GetAgeAtDeath(void)
{
  return Dengue[0];
}