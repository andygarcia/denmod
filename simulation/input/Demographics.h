#ifndef INPUT_DEMOGRAPHICS
#define INPUT_DEMOGRAPHICS

#include <vector>



namespace input {



class DemographicClass
{
public:
  DemographicClass(void);
  virtual ~DemographicClass(void);

public:
  int Rank;
  double Proportion;
  double DeathRate;
  double BirthRate;
};



class Demographics
{
public:
  Demographics(void);
  virtual ~Demographics(void);

public:
  std::vector<DemographicClass> DemographicData;
  int InitialPopulationSize;
  double HumanHostDensity;
};

};

#endif
