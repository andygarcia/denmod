#ifndef DSPORT_SIMULATION_H
#define DSPORT_SIMULATION_H

#include "../input/Location.h"
#include "../output/DensimOutput.h"
#include "SimLocation.h"



namespace sim {
namespace dsport {
  
class Simulation
{
// Constructors
public:
  Simulation( const input::Location * location, sim::output::MosData * mosData );
  ~Simulation(void);

// Methods
public:
  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date endDate );

  sim::output::DensimOutput * GetSimOutput(void);

// Members
private:
  SimLocation * _simLocation;
};

};
};

#endif
