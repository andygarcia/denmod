#ifndef SIM_DS_HUMANS_H
#define SIM_DS_HUMANS_H

#include <algorithm>
#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include "../input/Location.h"



namespace sim {
namespace ds {

class Location;
class MAEAInfectionParms;
class SequentialInfectionParms;



class AgeClass
{
public:
  AgeClass(void)
  {}

  AgeClass( int firstDay, int lastDay )
  : FirstDay(firstDay),
    LastDay(lastDay)
  {}

public:
  int FirstDay;
  int LastDay;
  double Proportion;             // proportion of population in age class
  double YearlyDeathRate;        // yearly death rate per 1000 for age class
  double YearlyBirthRate;        // yearly birth rate per 1000 for age class

  double DailyDeathRate;
  double DailyBirthRate;
};



class Human
{
public:
  Human( int age );
  virtual ~Human(void);

public:
  int GetAge(void);
  void SetAge( int age );
  int GetSerotypeStatus( int serotype );
  void SetSerotypeStatus( int serotype, int status );

public:
  int Age;
  int Dengue[4+1];
};
typedef std::vector<Human> HumanCollection;
typedef std::vector<HumanCollection> HumansByClass;



class MaternalAntibodies
{
public:
  int MANA;               // maternally acquired neutralizing antibody
  int MAEA;               // maternally acquired enhancing antibody
};



class HumanPopulation
{
// Typedefs
public:
  typedef std::map<int,std::map<int,double>> ClassSpecificSeroprevalence;
  typedef std::map<int,std::map<int,double>> DailySequentialInfections;

// Constructors
public:
  HumanPopulation( const input::Location * location, boost::variate_generator<boost::mt19937, boost::uniform_01<>> & rng );
  virtual ~HumanPopulation(void);

// Methods
public:
  void Initialize(void);

  int GetInitialPopulationSize(void);
  int GetPopulationSize(void);

  std::vector<int> GetInitialAgeDistribution(void);
  std::vector<double> GetInitialAgeProportions(void);
  std::vector<int> GetAgeDistribution(void);
  std::vector<double> GetAgeProportions(void);
  std::vector<int> GetBirthsByClass(void);
  std::vector<double> GetBirthPercentagesByClass(void);
  std::vector<int> GetDeathsByClass(void);
  std::vector<double> GetDeathPercentagesByClass(void);

  std::vector<std::vector<int>> GetInitialSeroDistribution(void);
  std::vector<std::vector<int>> GetSeroDistribution(void);
  ClassSpecificSeroprevalence GetClassSpecificSeroprevalence(void);

  void DoDailyDeaths(void);
  void DoDailyBirths(void);
  void AgePopulation(void);
  void PurgeMaternalAntibodies(void);

  void IntroduceInfectedHuman( unsigned int serotype );
  void InoculateRandomHuman( unsigned int serotype );

  void RankPopulation(void);
  void RankSerology( HumanCollection::iterator itIndiv, int ageClass );
  void CheckSequentialInfection( int serotype, HumanCollection::iterator itIndiv );
  void TabulateHfDeath( int age );
  void PurgeHfDeaths(void);

  Human & SelectHuman(void);
  Human & SelectHumanByAgeClass( int ageClass );
  int GetAgeClassFromAge( int age );

  int GetIncubatingBySerotype( int serotype );
  int GetNewInfectiveBySerotype( int serotype );
  int GetInfectiveBySerotype( int serotype );

  DailySequentialInfections GetDailySequentialInfections(void);

private:
  Location * _location;
  void InitializeAgeClasses(void);
  void InitializeDemographics(void);

  void InitializePopulation(void);
  void InitializeSeroprevalence(void);

// Members
private:
  // parameters
  input::Demographics * _demographics;
  input::Virology * _virology;
  input::SequentialInfections * _sequentialInfections;

  // random number generator
  boost::variate_generator<boost::mt19937, boost::uniform_01<>> & _rng;

  // state
  std::map<int,AgeClass> _ageClasses;

  unsigned int _initialPopulationSize;
  unsigned int _populationSize;
  HumansByClass _humans;

  std::vector<int> _initialAgeDistribution;
  std::vector<int> _ageDistribution;

  std::vector<double> _cumulativeDeaths;
  std::vector<double> _cumulativeBirths;
  std::vector<int> _totalDeaths;
  std::vector<int> _totalBirths;

  std::vector<std::vector<double>> _initialSeroprevalence;
  std::vector<std::vector<int>> _seroDistribution;
  std::vector<std::vector<int>> _initialSeroDistribution;

  ClassSpecificSeroprevalence _classSpecificSeroprevalence;

  std::vector<std::vector<int>> _incubating;
  std::vector<std::vector<int>> _infective;
  std::vector<std::vector<int>> _homologousImmunity;
  std::vector<std::vector<int>> _heterologousImmunity;

  std::vector<MaternalAntibodies> _maternalAntibodies;

  int _heterologousImmunityDuration;

  int _neutralizingDuration;
  int _enhancingDuration;
  int _thresholdAge;
  int _thresholdClass;

  std::vector<int> _totalIncubating;
  std::vector<int> _newInfective;
  std::vector<int> _totalInfective;
  std::vector<int> _totalHomologousImmunity;
  std::vector<int> _totalHeterologousImmunity;

  DailySequentialInfections _dailySequentialInfections;

  std::vector<double> _cumulativeHfDeaths;
};

};
};

#endif
