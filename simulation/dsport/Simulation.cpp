#include "StdAfx.h"
#include "Simulation.h"


using namespace sim::dsport;



Simulation::Simulation( const input::Location * location, sim::output::MosData * mosData )
: _dsport(new dsport(location, mosData))
{}



Simulation::~Simulation(void)
{
  delete _dsport;
}



void
Simulation::Start(void)
{
  _dsport->Start();
}



void
Simulation::Start( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  _dsport->Start( startDate, endDate );
}
