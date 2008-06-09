#include "StdAfx.h"
#include "Simulation.h"


using namespace sim::ds;



Simulation::Simulation( const input::Location * location, sim::output::MosData * mosData )
{
  SimLocation_ = new SimLocation( location, mosData );
}



Simulation::~Simulation(void)
{
  delete SimLocation_;
}



void
Simulation::Start(void)
{
  SimLocation_->Start();
}



void
Simulation::Start( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  SimLocation_->Start( startDate, endDate );
}



sim::output::DensimOutput *
Simulation::GetSimOutput(void)
{
  return SimLocation_->GetSimOutput();
}
