#ifndef POPULATION_H
#define POPULATION_H

#include <algorithm>
#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "SimConstants.h"



namespace ds {
namespace port {


class dsport;

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
  float Proportion;             // proportion of population in age class
  float YearlyDeathRate;        // yearly death rate per 1000 for age class
  float YearlyBirthRate;        // yearly birth rate per 1000 for age class

  float DailyDeathRate;
  float DailyBirthRate;
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
  typedef std::map<int,std::map<int,float>> ClassSpecificSeroprevalence;
  typedef std::map<int,std::map<int,float>> DailySequentialInfections;

// Constructors
public:
  HumanPopulation( dsport * dsport, Location * location );
  virtual ~HumanPopulation(void);

// Methods
public:
  int GetInitialPopulationSize(void);
  int GetPopulationSize(void);

  std::vector<int> GetInitialAgeDistribution(void);
  std::vector<float> GetInitialAgeProportions(void);
  std::vector<int> GetAgeDistribution(void);
  std::vector<float> GetAgeProportions(void);
  std::vector<int> GetBirthsByClass(void);
  std::vector<float> GetBirthPercentagesByClass(void);
  std::vector<int> GetDeathsByClass(void);
  std::vector<float> GetDeathPercentagesByClass(void);

  std::vector<std::vector<int>> GetInitialSeroDistribution(void);
  std::vector<std::vector<int>> GetSeroDistribution(void);
  ClassSpecificSeroprevalence GetClassSpecificSeroprevalence(void);

  void DoDailyDeaths(void);
  void DoDailyBirths(void);
  void AgePopulation(void);
  void PurgeMaternalAntibodies(void);

  void IntroduceInfectedHuman( int serotype );
  void InnoculateRandomHuman( int serotype );

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
  dsport * _dsp;
  void InitializeAgeClasses(void);
  void InitializeDemographics( std::vector<HumanDemo> & populationProportions );

  void InitializePopulation(void);
  void InitializeSeroprevalence(void);

// Members
private:
  std::map<int,AgeClass> _ageClasses;

  unsigned int _initialPopulationSize;
  unsigned int _populationSize;
  //HumanCollection _humans;
  HumansByClass _humans;

  std::vector<int> _initialAgeDistribution;
  std::vector<int> _ageDistribution;

  std::vector<float> _cumulativeDeaths;
  std::vector<float> _cumulativeBirths;
  std::vector<int> _totalDeaths;
  std::vector<int> _totalBirths;

  std::vector<std::vector<float>> _initialSeroprevalence;
  std::vector<std::vector<int>> _seroDistribution;
  std::vector<std::vector<int>> _initialSeroDistribution;

  ClassSpecificSeroprevalence _classSpecificSeroprevalence;

  std::vector<std::vector<int>> _incubating;
  std::vector<std::vector<int>> _infective;
  std::vector<std::vector<int>> _homologousImmunity;
  std::vector<std::vector<int>> _heterologousImmunity;

  std::vector<MaternalAntibodies> _maternalAntibodies;

  int _neutralizingDuration;
  int _enhancingDuration;

  int _thresholdAge;
  int _thresholdClass;

  int _heterologousImmunityDuration;

  std::vector<VirusDesc> & _virus;

  std::vector<int> _totalIncubating;
  std::vector<int> _newInfective;
  std::vector<int> _totalInfective;
  std::vector<int> _totalHomologousImmunity;
  std::vector<int> _totalHeterologousImmunity;

  std::vector<MAEAInfectionParms> _maternalSequentialParameters;
  std::vector<SequentialInfectionParms> _sequentialParameters;

  DailySequentialInfections _dailySequentialInfections;

  std::vector<float> _cumulativeHfDeaths;

  DebugOutput _dailyDebugOutput;
};

};
};

#endif
