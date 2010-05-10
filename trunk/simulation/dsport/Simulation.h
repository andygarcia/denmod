#ifndef SIM_DS_SIMULATION_H
#define SIM_DS_SIMULATION_H

#include "../input/Location.h"
#include "../output/DensimOutput.h"
#include "dsport.h"



namespace sim {
namespace ds {
  
class Simulation
{
// Constructors
public:
  Simulation( const input::Location * location, sim::output::MosData * mosData, bool doDiskOutput = false );
  ~Simulation(void);

// Methods
public:
  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date endDate );
  sim::output::DensimOutput * GetDensimOutput(void);

// Members
private:
  dsport * _dsport;

  bool _doDiskOutput;
};

};
};

#endif
