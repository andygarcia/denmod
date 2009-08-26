#include "StdAfx.h"
#include "Simulation.h"


using namespace sim::dsport;



Simulation::Simulation( const input::Location * location, sim::output::MosData * mosData )
: _simLocation(new SimLocation(location, mosData))
{}



Simulation::~Simulation(void)
{
  delete _simLocation;
}



void
Simulation::Start(void)
{
  _simLocation->Start();
}



void
Simulation::Start( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  _simLocation->Start( startDate, endDate );
}



sim::output::DensimOutput *
Simulation::GetSimOutput(void)
{
  return _simLocation->GetSimOutput();
}
