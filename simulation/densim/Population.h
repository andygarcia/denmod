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
  bool IsSeropositive( int serotype );

  void InitializeImmunity( int serotype );
  bool HasInitializedImmunity( int serotype );

  void InitializeMaternallyAcquiredImmunity( int serotype );
  bool HasMaternallyAcquiredImmunity( int serotype );
  void PurgeMaternalImmunity(void);

  bool HasHomologousImmunity( int serotype );

  void Infect( int serotype, int age );
  bool HasPreviousInfection( int serotype );
  int GetAgeOfInfection( int serotype );
  bool HasHeterologousImmunity( int serotype, int duration );

// Fields
public:
  int Age;
  int Dengue[5];  // -2 for initialized homologous immmunity
                  // -1 for maternally acquired immunity
                  //  0 for no previous exposure
                  // >0 inoculation day
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
