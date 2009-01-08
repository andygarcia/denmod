#ifndef OUTPUT_POPDATA_H
#define OUTPUT_POPDATA_H

#include <map>
#include <vector>
#include "../cimsim/SimClasses.h"
#include "../cimsim/Cohorts.h"



namespace sim {
namespace output {

class ContainerPopData
{
public:
  ContainerPopData(void) {}
  virtual ~ContainerPopData(void) {}

public:
  std::string Name;
  int Id;
  int CloneId;

  // eggs
  sim::cs::EggBandCollection EggCohorts;

  // larvae
  sim::cs::LarvaeCohortCollection LarvaeCohorts;
  double Cadavers;
  double LarvaeCadaverWeight;

  // pupae
  sim::cs::PupaeCohortCollection PupaeCohorts;
  double PupaeCadaverWeight;

  // environment
  double Depth;
  double Food;

  // densities
  double UntreatedDensity;
  double TreatedDensity;
  std::vector<sim::cs::ExcludedDensity> ExcludedDensities;
};



class PopData
{
public:
  typedef std::multimap<int,ContainerPopData*> ContainerPopDataCollection;

public:
  PopData(void);
  virtual ~PopData(void);

public:
  void AddContainerData( ContainerPopData * cpd );
  ContainerPopData * GetContainerData( int containerId ) const;
  ContainerPopData * GetClonedContainerData( int containerId, int cloneId ) const;

private:
  ContainerPopDataCollection _containers;

public:
  sim::cs::PreOviAdultCohortCollection PreOviAdultCohorts;
  sim::cs::OviAdultCohortCollection OviAdultCohorts;
  std::vector<double> MosqAgeDistr;
};

};
};

#endif
