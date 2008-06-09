#include "StdAfx.h"
#include "Population.h"

using namespace sim::ds;



Individual::Individual( int age )
: Age(age)
{
  Dengue1 = 0;
  Dengue2 = 0;
  Dengue3 = 0;
  Dengue4 = 0;
}



Individual::Individual( const Individual & individual )
{
  this->Age = individual.Age;
  this->Dengue1 = individual.Dengue1;
  this->Dengue2 = individual.Dengue2;
  this->Dengue3 = individual.Dengue3;
  this->Dengue4 = individual.Dengue4;
}



Individual::~Individual(void)
{}



void
Individual::SetNewInfection( int serotype, int age )
{
  SetSerotypeValue( serotype, age );
}



bool
Individual::HasNoPreviousExposure( int serotype )
{
  return GetSerotypeValue( serotype) == 0;
}



bool
Individual::HasHeterologousImmunity( int serotype, int duration )
{
  for( int i = 1; i <=4; ++i ) {
    // check for previous infection against other serotypes
    if( i == serotype ) {
      continue;
    }
    
    int seroVal = GetSerotypeValue( i );
    if( seroVal > 0 ) {
      // previous infection
      if( Age - seroVal < duration ) {
        return true;
      }
    }
  }

  return false;
}



bool
Individual::HasHomologousImmunity( int serotype )
{
  int seroVal = GetSerotypeValue( serotype );
  return GetSerotypeValue( serotype ) == -2;
}



void
Individual::SetHomologousImmunity( int serotype )
{
  SetSerotypeValue( serotype, -2 );
}



bool 
Individual::HasMaternallyAcquiredImmunity( int serotype )
{
  return GetSerotypeValue( serotype ) == -1;
}



void
Individual::SetMaternallyAcquiredImmunity( int serotype )
{
  SetSerotypeValue( serotype, -1 );
}



void
Individual::PurgeMaternalAntibodies(void)
{
  if( Dengue1 == -1 ) {
    Dengue1 = 0;
  }
  if( Dengue2 == -1 ) {
    Dengue2 = 0;
  }
  if( Dengue3 == -1 ) {
    Dengue3 = 0;
  }
  if( Dengue4 == -1 ) {
    Dengue4 = 0;
  }
}



void
Individual::SetSerotypeValue( int serotype, int value )
{
  switch( serotype ) {
    case 1: {
      Dengue1 = value;
      return;
    }
    case 2: {
      Dengue2 = value;
      return;
    }
    case 3: {
      Dengue3 = value;
      return;
    }
    case 4: {
      Dengue4 = value;
      return;
    }
    default: {
      // invalid serotype
      throw;
    }
  }
}



int
Individual::GetSerotypeValue( int serotype )
{
  switch( serotype ) {
    case 1: {
      return Dengue1;
    }
    case 2: {
      return Dengue2;
    }
    case 3: {
      return Dengue3;
    }
    case 4: {
      return Dengue4;
    }
    default: {
      // invalid serotype
      throw;
    }
  }
}