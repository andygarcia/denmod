#include "StdAfx.h"
#include "Simulation.h"
#include <numeric>

using namespace sim::cs;



Simulation::Simulation( input::Location * location, boost::gregorian::date startDate, boost::gregorian::date stopDate, bool usePop )
: _startDate(startDate),
  _stopDate(stopDate),
  _popData(NULL),
  _usePop(usePop)
{
  if( _usePop ) {
    // run for first year of simulation
    boost::gregorian::date popStartDate = boost::gregorian::date( _startDate.year(), 1, 1 );
    boost::gregorian::date popStopDate = boost::gregorian::date( _startDate.year(), 12, 31 );

    // disable controls for generating established population
    std::vector<input::Control*> disabledControls = std::vector<input::Control*>( location->Controls_ );
    location->Controls_.clear();

    // run simulation for year
    SimLocation * popSim = new SimLocation( location, popStartDate, popStopDate );
    popSim->RunSimulation();
    output::CimsimOutput * output = popSim->GetSimOutput();

    // save population
    _popData = output->GetPopData();
    delete output;

    // restore controls
    location->Controls_ = disabledControls;
  }

  SimLocation_ = new SimLocation( location, startDate, stopDate, _popData );
}



Simulation::~Simulation(void)
{
  delete SimLocation_;
  if( _popData ) {
    delete _popData;
  }
}



void
Simulation::Start(void)
{
  SimLocation_->RunSimulation();
}



sim::output::CimsimOutput *
Simulation::GetSimOutput(void)
{
  return SimLocation_->GetSimOutput();
}



FoodFitSimulation::FoodFitSimulation( input::Location * location, boost::gregorian::date surveyStartDate, boost::gregorian::date surveyStopDate )
: _location(location)
{
  // all food runs will use same location and random food, see case 151.
  //_location->Biology_->Larvae->Food->UseRandomFood = true;

  // all food runs will use same starting equillbrium population (controls have no effect)
  boost::gregorian::date popStartDate = boost::gregorian::date( surveyStartDate.year(), 1, 1 );
  boost::gregorian::date popStopDate = boost::gregorian::date( surveyStartDate.year(), 12, 31 );
  std::vector<input::Control*> disabledControls = std::vector<input::Control*>( location->Controls_ );
  SimLocation * popSim = new SimLocation( location, popStartDate, popStopDate );
  popSim->RunSimulation();
  output::CimsimOutput * output = popSim->GetSimOutput();
  _popData = output->GetPopData();
  delete output;
  location->Controls_ = disabledControls;

  // all food runs will run the same period of time (based on survey)
  _surveyStartDate = surveyStartDate;
  _surveyStopDate = surveyStopDate;
  _numberDaysSurveyed = (_surveyStopDate - _surveyStartDate).days() + 1;

  _startDate = boost::gregorian::date( surveyStartDate.year(), 1 ,1 );
  _stopDate = surveyStopDate;
}



FoodFitSimulation::~FoodFitSimulation(void)
{
  delete _popData;
}


// TODO use container id to pass info back to managed code
std::map<std::string,double>
FoodFitSimulation::DoIteration( int numberOfRuns )
{
  std::map<std::string,double> averageObservedPupaeByContainer;
  std::map<std::string,std::vector<double>> observedPupaeByContainer;

  for( int i = 0; i < numberOfRuns; ++i ) {
    // do run and save output
    SimLocation * foodRun = new SimLocation( _location, _startDate, _stopDate, _popData );
    foodRun->RunSimulation();
    output::CimsimOutput * output = foodRun->GetSimOutput();
    delete foodRun;

    for( std::vector<input::Container*>::const_iterator itCtnr = _location->Containers_.begin(); itCtnr != _location->Containers_.end(); ++itCtnr ) {
      std::vector<double> & dailyPupae = output->GetPupae( _surveyStartDate, _surveyStopDate, (*itCtnr)->Id_ );
      double avgSurveyPupae = std::accumulate( dailyPupae.begin(), dailyPupae.end(), 0.0 ) / _numberDaysSurveyed;

      observedPupaeByContainer[(*itCtnr)->Name_].push_back( avgSurveyPupae );
    }
    delete output;
  }

  for( std::map<std::string,std::vector<double>>::iterator itCtnr = observedPupaeByContainer.begin(); itCtnr != observedPupaeByContainer.end(); ++itCtnr ) {
    std::string name = itCtnr->first;
    std::vector<double> & observedPupae = itCtnr->second;
    double avgObserved = std::accumulate( observedPupae.begin(), observedPupae.end(), 0.0 ) / numberOfRuns;
    averageObservedPupaeByContainer[name] = avgObserved;
  }

  return averageObservedPupaeByContainer;
}
