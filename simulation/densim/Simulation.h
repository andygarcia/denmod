#ifndef DS_SIMULATION_H
#define DS_SIMULATION_H

#include "../input/Location.h"
#include "../output/DensimData.h"
#include "SimLocation.h"



namespace sim {
namespace ds {
  
class Simulation
{
public:
  Simulation( const input::Location * location, sim::output::MosData * mosData );
  ~Simulation(void);

  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date endDate );

  sim::output::DensimData * GetSimOutput(void);

private:
  sim::ds::SimLocation * SimLocation_;
};

};
};

#endif
