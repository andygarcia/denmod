#include "StdAfx.h"
#include "Simulation.h"

using namespace sim::ds;



Simulation::Simulation( const input::Location * inputLocation, sim::output::MosData * mosData, bool doDiskOutput )
: _location(new Location(inputLocation, mosData, doDiskOutput)),
  _doDiskOutput(doDiskOutput)
{}



Simulation::~Simulation(void)
{
  delete _location;
}



void
Simulation::Start(void)
{
  _location->Start();
}



void
Simulation::Start( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  _location->Start( startDate, endDate );
}



sim::output::DensimOutput *
Simulation::GetDensimOutput(void)
{
  return _location->GetDensimOutput();
}
