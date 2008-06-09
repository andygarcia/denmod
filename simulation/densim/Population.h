#ifndef SIM_DS_POPULATION_H
#define SIM_DS_POPULATION_H

#include <vector>


namespace sim {
namespace ds {

class Individual
{
// Constructor
public:
  Individual( int age );
  Individual( const Individual & individual );
  virtual ~Individual(void);

// Methods
public:
  void SetNewInfection( int serotype, int age );

  bool HasNoPreviousExposure( int serotype );

  bool HasHeterologousImmunity( int serotype, int duration );
  bool HasHomologousImmunity( int serotype );
  void SetHomologousImmunity( int serotype );

  bool HasMaternallyAcquiredImmunity( int serotype );
  void SetMaternallyAcquiredImmunity( int serotype );

  void PurgeMaternalAntibodies(void);

private:
  void SetSerotypeValue( int serotype, int value );
  int GetSerotypeValue( int serotype );

// Fields
public:
  int Age;
  int Dengue1;
  int Dengue2;
  int Dengue3;
  int Dengue4;
};

typedef std::vector<Individual> Population;


struct DescendingAgeSort
{
  bool operator()( Individual & a, Individual & b ) {
    return (a.Age > b.Age);
  }
};

};
};

#endif
