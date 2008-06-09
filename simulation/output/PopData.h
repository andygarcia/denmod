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

  // eggs
  sim::cs::EggBandCollection EggCohorts;

  // larvae
  sim::cs::LarvaeCohortCollection LarvaeCohorts;
  double cadavers;
  double LarvCadWt;

  // pupae
  sim::cs::PupaeCohortCollection PupaeCohorts;
  double PupCadWt;

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
  typedef std::map<std::string,ContainerPopData*> ContainerPopDataCollection;

public:
  PopData(void);
  virtual ~PopData(void);

public:
  std::map<std::string,ContainerPopData*> Containers_;

  // adult cohorts
  sim::cs::PreOviAdultCohortCollection PreOviAdultCohorts;
  sim::cs::OviAdultCohortCollection OviAdultCohorts;
  std::vector<double> MosqAgeDistr;
};

};
};

#endif
